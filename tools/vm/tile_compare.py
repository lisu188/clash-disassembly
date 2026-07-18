#!/usr/bin/env python3
"""Tile-by-tile world-map comparison: ORIGINAL clash95.exe (Win98/QEMU captures)
vs the recovered engine (clash95_bootstrap frame dumps).

Frame-for-frame alignment is impossible in the all-AI /A<n> mode (time-mixed
RNG per draw: units_004.c:1044-1070; camera auto-follows AI stacks:
units_001.c:893-903), so frames are sliced into 64x64 tile cells at ABSOLUTE
map coordinates and compared per-tile on the best matching sample pair.

Authoritative geometry (recovered source):
- Tiles 64x64 px, grid origin (32,16), 9 cols x 7 rows visible (7th row
  partial, 6 cols): draw loop src/units/00416850_00419120_units_005.c:668-707,
  click inverse src/world/00408030_0040A0A0_world_001.c:292-301.
  Cell of absolute tile: x = 32 + 64*(C - VIEW_LEFT), y = 16 + 64*(R -
  VIEW_TOP); C = horizontal col (tied to LEFT), R = vertical row (tied to TOP).
- Viewport recovery from the minimap panel (exact, no calibration):
  MiniMap_* in src/world/0040B0A0_0040D560_world_003.c:1352-1439 —
  ppt = 4 if W*H<=2500 else 2; panel left = 608-(ppt*W+14), top 16; a pure
  white (255,255,255) viewport-box OUTLINE at boxLeft = panelLeft+6+ppt*VL,
  boxTop = 22+ppt*VT, outer (ppt*9+2) x (ppt*7+2). Detected by exact-length
  white run + full outline verification.
- Fog: unexplored tiles are a solid black 64x64 fill (units_005.c:137-142);
  all-AI mode reveals the whole map (world_003.c:254-258), so black cells in
  only one engine are a divergence -> classified 'fog-black-mismatch'.

Subcommands:
  index     - validate frames + infer exact per-frame viewport -> CSV
  maskaudit - render one frame with masks + grid + tile labels
  score     - per-tile atlas comparison of two index sets -> reports
  exhibit   - masked full-frame + per-cell diff of two same-viewport frames
(selftest = `score` with two same-engine index sets; use --shift for the
negative control.)
"""
import argparse
import csv
import os
import sys

from PIL import Image, ImageDraw

TILE = 64
GRID_X0 = 32
GRID_Y0 = 16
VIEW_COLS = 9
VIEW_ROWS = 7
ROW6_COLS = 6  # 7th row draws only 6 columns (units_005.c:691-707)


# ---------------------------------------------------------------- geometry

def minimap_geometry(map_w, map_h):
    ppt = 4 if map_w * map_h <= 2500 else 2
    panel_w = ppt * map_w + 14
    panel_h = ppt * map_h + 14
    panel_left = 608 - panel_w
    panel_top = 16
    box_w = ppt * VIEW_COLS + 2
    box_h = ppt * VIEW_ROWS + 2
    return ppt, panel_left, panel_top, panel_w, panel_h, box_w, box_h


def detect_viewport(img, map_w, map_h):
    """Return (VL, VT) or (None, reason). Exact-outline detector."""
    ppt, pl, pt, pw, ph, bw, bh = minimap_geometry(map_w, map_h)
    px = img.load()
    W, H = img.size

    def white(x, y):
        if x < 0 or y < 0 or x >= W or y >= H:
            return False
        r, g, b = px[x, y][:3]
        return r == 255 and g == 255 and b == 255

    cands = []
    for y in range(pt, pt + ph - bh + 1):
        x = pl
        while x <= pl + pw - bw:
            if white(x, y):
                run = 0
                while white(x + run, y):
                    run += 1
                if run == bw and not white(x - 1, y):
                    cands.append((x, y))
                x += max(run, 1)
            else:
                x += 1
    verified = []
    for (x, y) in cands:
        ok = all(white(x + i, y + bh - 1) for i in range(bw))
        ok = ok and all(white(x, y + j) for j in range(bh))
        ok = ok and all(white(x + bw - 1, y + j) for j in range(bh))
        if ok:
            verified.append((x, y))
    if not verified:
        return None, 'no-outline'
    if len(verified) > 1:
        return None, 'multiple-outlines'
    x, y = verified[0]
    if (x - pl - 6) % ppt or (y - pt - 6) % ppt:
        return None, 'misaligned-outline'
    vl = (x - pl - 6) // ppt
    vt = (y - pt - 6) // ppt
    if not (0 <= vl <= map_w - VIEW_COLS and 0 <= vt <= map_h - VIEW_ROWS):
        return None, 'viewport-out-of-range'
    return (vl, vt), 'ok'


def build_masks(map_w, map_h, extra_mask=None, include_row6=False):
    """Return list of masked screen rects (x0,y0,x1,y1 inclusive)."""
    ppt, pl, pt, pw, ph, _, _ = minimap_geometry(map_w, map_h)
    masks = [
        (pl - 1, pt - 1, pl + pw, pt + ph),   # minimap panel +1px safety
        (407, 391, 639, 479),                 # action buttons + nameplate union
    ]
    if extra_mask:
        masks.append(extra_mask)
    return masks


def cell_rect(r, c):
    x0 = GRID_X0 + TILE * c
    y0 = GRID_Y0 + TILE * r
    return x0, y0, x0 + TILE - 1, y0 + TILE - 1


def rects_overlap(a, b):
    return not (a[2] < b[0] or b[2] < a[0] or a[3] < b[1] or b[3] < a[1])


def admissible_cells(masks, include_row6=False):
    """Viewport (r,c) cells fully unmasked."""
    out = []
    for r in range(VIEW_ROWS):
        ncols = VIEW_COLS if r < 6 else ROW6_COLS
        if r == 6 and not include_row6:
            continue
        for c in range(ncols):
            rect = cell_rect(r, c)
            if any(rects_overlap(rect, m) for m in masks):
                continue
            out.append((r, c))
    return out


# ---------------------------------------------------------------- metrics

def cell_image(img, r, c):
    x0, y0, x1, y1 = cell_rect(r, c)
    return img.crop((x0, y0, x1 + 1, y1 + 1))


def dac6(img):
    """Quantize to the VGA DAC's 6 bits/channel (values are multiples of 4 on
    real Win9x hardware; the SDL pipeline keeps full 8-bit palette entries).
    Comparing dac6(a) vs dac6(b) removes that systematic capture difference."""
    return img.point(lambda v: v & 0xFC)


def pair_metrics(a, b):
    """(mad, max_channel_diff, pct_pixels_differing).
    - maxd <= ~6 means identity modulo the VGA DAC's 6-bit rounding.
    - a small pct with large maxd is the sparse-pixel signature (isolated
      palette-entry divergences, e.g. the recovered engine's black speckles
      where the original draws a green ramp)."""
    from PIL import ImageChops
    d = ImageChops.difference(a, b)
    h = d.histogram()  # 3 channels x 256
    total = 0
    count = 0
    maxd = 0
    for ch in range(3):
        for v in range(256):
            cnt = h[ch * 256 + v]
            if cnt:
                total += v * cnt
                count += cnt
                if v > maxd:
                    maxd = v
    # pixel-level differing fraction (any channel > 16)
    gray = d.convert('L')  # cheap upper bound is fine for classification
    gh = gray.point(lambda v: 255 if v > 16 else 0).histogram()
    npx = a.size[0] * a.size[1]
    pct = gh[255] / npx if npx else 0.0
    return total / (count or 1), maxd, pct


def mad(a, b):
    return pair_metrics(a, b)[0]


def classify(best, maxd, pct, sa, sb, t):
    # The terrain textures are dithered noise: individual pixels differ by a
    # full palette step between the DirectDraw original (6-bit DAC) and the SDL
    # recovery (8-bit), so per-pixel maxd is large (~175) even on visually
    # identical tiles. MEAN abs diff is the robust identity metric -
    # empirically ~2-5 on matching grass/rock, >15 on real structural changes
    # (fog strips, units, different terrain).
    black_a = [is_black(s) for s, _ in sa]
    black_b = [is_black(s) for s, _ in sb]
    if any(black_a) != any(black_b):
        return 'fog-black-mismatch'
    def dyn(ss):
        if len(ss) < 2:
            return 0.0
        return max(mad(a, b) for i, (a, _) in enumerate(ss)
                   for (b, _) in [x for x in ss[i + 1:]])
    da, db = dyn(sa), dyn(sb)
    if best <= t['ident_mad']:
        if maxd <= t['maxd']:
            return 'identical-pixel'          # equal modulo 6-bit DAC rounding
        return 'identical-terrain'            # same terrain, dither/DAC variance
    if da > t['unit'] or db > t['unit']:
        return 'unit-occupied'
    return 'content-mismatch'


def luma_stats(im):
    g = im.convert('L')
    h = g.histogram()
    n = sum(h) or 1
    mean = sum(i * cnt for i, cnt in enumerate(h)) / n
    var = sum(cnt * (i - mean) ** 2 for i, cnt in enumerate(h)) / n
    return mean, var ** 0.5


def is_black(im):
    mean, std = luma_stats(im)
    return mean < 8 and std < 3


# ---------------------------------------------------------------- index

def cmd_index(args):
    extra = parse_rect(args.extra_mask) if args.extra_mask else None
    rows = []
    files = sorted(
        f for f in os.listdir(args.frames)
        if f.lower().endswith(('.png', '.bmp')))
    accepted = 0
    for f in files:
        path = os.path.join(args.frames, f)
        try:
            img = Image.open(path).convert('RGB')
        except Exception as e:  # noqa: BLE001 - report unreadable frames
            rows.append([path, args.engine, args.run_id, '', '', 'reject', f'unreadable:{e}'])
            continue
        if img.size != (640, 480):
            rows.append([path, args.engine, args.run_id, '', '', 'reject', f'size:{img.size}'])
            continue
        vp, why = detect_viewport(img, args.map_w, args.map_h)
        if vp is None:
            rows.append([path, args.engine, args.run_id, '', '', 'reject', why])
            continue
        rows.append([path, args.engine, args.run_id, vp[0], vp[1], 'ok', ''])
        accepted += 1
    with open(args.out, 'w', newline='') as fh:
        w = csv.writer(fh)
        w.writerow(['path', 'engine', 'run_id', 'vl', 'vt', 'status', 'reason'])
        w.writerows(rows)
    print(f'index: {accepted}/{len(files)} frames accepted -> {args.out}')
    for row in rows:
        tag = f'({row[3]},{row[4]})' if row[5] == 'ok' else row[6]
        print(f'  {os.path.basename(row[0])}: {row[5]} {tag}')


def parse_rect(s):
    p = [int(v) for v in s.split(',')]
    if len(p) != 4:
        raise SystemExit('rect must be x0,y0,x1,y1')
    return tuple(p)


# ---------------------------------------------------------------- maskaudit

def cmd_maskaudit(args):
    img = Image.open(args.frame).convert('RGB')
    extra = parse_rect(args.extra_mask) if args.extra_mask else None
    masks = build_masks(args.map_w, args.map_h, extra)
    cells = admissible_cells(masks, args.include_row6)
    d = ImageDraw.Draw(img, 'RGBA')
    for m in masks:
        d.rectangle(m, fill=(255, 0, 0, 90))
    for r in range(VIEW_ROWS):
        for c in range(VIEW_COLS if r < 6 else ROW6_COLS):
            rect = cell_rect(r, c)
            ok = (r, c) in cells
            d.rectangle(rect, outline=(0, 255, 0, 255) if ok else (255, 128, 0, 255))
            if ok and args.vl is not None:
                d.text((rect[0] + 3, rect[1] + 3),
                       f'{args.vt + r},{args.vl + c}', fill=(255, 255, 0, 255))
    img.save(args.out)
    print(f'maskaudit: {len(cells)} admissible cells -> {args.out}')


# ---------------------------------------------------------------- atlas

def load_index(paths):
    frames = []
    for p in paths:
        with open(p, newline='') as fh:
            for row in csv.DictReader(fh):
                if row['status'] == 'ok':
                    frames.append(row)
    return frames


def build_atlas(frames, masks, include_row6, k_cap, shift=(0, 0), keep_min_mad=1.0,
                normalize=False):
    """tile (R,C) -> list of (cell_image, frame_path). Applies optional
    viewport shift (negative control). Includes a snap audit per frame."""
    cells = admissible_cells(masks, include_row6)
    atlas = {}
    dropped = []
    for fr in frames:
        img = Image.open(fr['path']).convert('RGB')
        if normalize:
            img = dac6(img)
        vl = int(fr['vl']) + shift[0]
        vt = int(fr['vt']) + shift[1]
        # snap audit: this frame's cells vs existing same-engine samples
        votes_bad = 0
        votes = 0
        for (r, c) in cells[:8]:
            R, C = vt + r, vl + c
            if (R, C) not in atlas:
                continue
            sample = cell_image(img, r, c)
            m0 = min(mad(sample, s) for s, _ in atlas[(R, C)])
            best_shift = m0
            for dR, dC in ((1, 0), (-1, 0), (0, 1), (0, -1)):
                key = (R + dR, C + dC)
                if key in atlas:
                    ms = min(mad(sample, s) for s, _ in atlas[key])
                    best_shift = min(best_shift, ms)
            votes += 1
            if best_shift + 5 < m0:
                votes_bad += 1
            if votes >= 4:
                break
        if votes >= 2 and votes_bad * 2 > votes:
            dropped.append(fr['path'])
            continue
        for (r, c) in cells:
            R, C = vt + r, vl + c
            sample = cell_image(img, r, c)
            bucket = atlas.setdefault((R, C), [])
            if len(bucket) >= k_cap:
                continue
            if all(mad(sample, s) > keep_min_mad for s, _ in bucket) or not bucket:
                bucket.append((sample, os.path.basename(fr['path'])))
    return atlas, dropped


# ---------------------------------------------------------------- score

CLASS_COLORS = {
    'unobserved': (60, 60, 60),
    'orig-only': (60, 90, 200),
    'rec-only': (0, 190, 190),
    'identical-pixel': (40, 220, 40),
    'identical-terrain': (60, 170, 60),
    'unit-occupied': (240, 140, 30),
    'content-mismatch': (230, 40, 40),
    'fog-black-mismatch': (0, 0, 0),
}




def cmd_score(args):
    extra_a = parse_rect(args.extra_mask_a) if args.extra_mask_a else None
    extra_b = parse_rect(args.extra_mask_b) if args.extra_mask_b else None
    masks_a = build_masks(args.map_w, args.map_h, extra_a)
    masks_b = build_masks(args.map_w, args.map_h, extra_b)
    frames_a = load_index(args.index_a)
    frames_b = load_index(args.index_b)
    shift = tuple(int(v) for v in args.shift.split(',')) if args.shift else (0, 0)
    atlas_a, drop_a = build_atlas(frames_a, masks_a, args.include_row6, args.k_cap,
                                  normalize=args.dac_normalize)
    atlas_b, drop_b = build_atlas(frames_b, masks_b, args.include_row6, args.k_cap,
                                  shift=shift, normalize=args.dac_normalize)
    t = {'anim': args.t_anim, 'unit': args.t_unit,
         'maxd': args.t_maxd, 'ident_mad': args.t_ident_mad}
    os.makedirs(args.out_dir, exist_ok=True)

    both = sorted(set(atlas_a) & set(atlas_b))
    results = []
    for (R, C) in both:
        sa, sb = atlas_a[(R, C)], atlas_b[(R, C)]
        pairs = [(pair_metrics(a, b), fa, fb) for a, fa in sa for b, fb in sb]
        (best, maxd, pct), fa, fb = min(pairs, key=lambda x: x[0][0])
        cls = classify(best, maxd, pct, sa, sb, t)
        results.append({'R': R, 'C': C, 'class': cls, 'best_mad': round(best, 2),
                        'best_maxd': maxd, 'pct_diff': round(100 * pct, 1),
                        'n_a': len(sa), 'n_b': len(sb),
                        'best_a': fa, 'best_b': fb})

    with open(os.path.join(args.out_dir, 'tiles.csv'), 'w', newline='') as fh:
        w = csv.DictWriter(fh, fieldnames=['R', 'C', 'class', 'best_mad',
                                           'best_maxd', 'pct_diff', 'n_a', 'n_b',
                                           'best_a', 'best_b'])
        w.writeheader()
        w.writerows(results)

    # heatmap
    px = 6
    hm = Image.new('RGB', (args.map_w * px, args.map_h * px), CLASS_COLORS['unobserved'])
    d = ImageDraw.Draw(hm)
    for (R, C) in atlas_a:
        if (R, C) not in atlas_b:
            d.rectangle((C * px, R * px, C * px + px - 1, R * px + px - 1),
                        fill=CLASS_COLORS['orig-only'])
    for (R, C) in atlas_b:
        if (R, C) not in atlas_a:
            d.rectangle((C * px, R * px, C * px + px - 1, R * px + px - 1),
                        fill=CLASS_COLORS['rec-only'])
    for res in results:
        R, C = res['R'], res['C']
        col = CLASS_COLORS[res['class']]
        d.rectangle((C * px, R * px, C * px + px - 1, R * px + px - 1), fill=col)
        if res['class'] == 'fog-black-mismatch':
            d.rectangle((C * px, R * px, C * px + px - 1, R * px + px - 1),
                        outline=(255, 0, 0))
    hm.save(os.path.join(args.out_dir, 'heatmap.png'))

    # worst montage
    bad = [r for r in results if r['class'] in
           ('fog-black-mismatch', 'content-mismatch', 'unit-occupied')]
    bad.sort(key=lambda r: (r['class'] != 'fog-black-mismatch', -r['best_mad']))
    bad = bad[:24]
    if bad:
        mh = len(bad) * (TILE + 14)
        mont = Image.new('RGB', (3 * TILE + 40, mh), (25, 25, 25))
        md = ImageDraw.Draw(mont)
        y = 0
        for res in bad:
            sa = next(s for s, f in atlas_a[(res['R'], res['C'])] if f == res['best_a'])
            sb = next(s for s, f in atlas_b[(res['R'], res['C'])] if f == res['best_b'])
            diff = ImageChops_difference(sa, sb).point(lambda v: min(255, v * 4))
            mont.paste(sa, (0, y))
            mont.paste(sb, (TILE + 6, y))
            mont.paste(diff, (2 * TILE + 12, y))
            md.text((2, y + TILE + 1),
                    f"({res['R']},{res['C']}) {res['class']} mad={res['best_mad']}",
                    fill=(255, 255, 128))
            y += TILE + 14
        mont.save(os.path.join(args.out_dir, 'worst_montage.png'))

    # summary
    from collections import Counter
    counts = Counter(r['class'] for r in results)
    static = [r for r in results
              if r['class'] in ('identical-pixel', 'identical-terrain')]
    denom = [r for r in results if r['class'] != 'unit-occupied']
    lines = []
    lines.append('tile_compare score summary')
    lines.append(f'  index A: {args.index_a} ({len(frames_a)} frames, {len(drop_a)} snap-dropped)')
    lines.append(f'  index B: {args.index_b} ({len(frames_b)} frames, {len(drop_b)} snap-dropped)')
    lines.append(f'  shift (negative control): {shift}')
    lines.append(f'  dac-normalize (6-bit VGA quantization): {args.dac_normalize}')
    lines.append(f'  thresholds: {t}')
    lines.append(f'  tiles: A={len(atlas_a)} B={len(atlas_b)} both={len(both)} '
                 f'({100.0 * len(both) / (args.map_w * args.map_h):.1f}% of map)')
    for cls in CLASS_COLORS:
        if cls in counts:
            lines.append(f'  {cls}: {counts[cls]}')
    if denom:
        lines.append(f'  matched (identical+animated) / non-unit tiles: '
                     f'{len(static)}/{len(denom)} = {100.0 * len(static) / len(denom):.1f}%')
    lines.append('  known-acceptable differences: water/lava animation phase timing,'
                 ' transient AI units (unit-occupied bucket), per-run cursor mask,'
                 ' viewport rectangles excluded via minimap mask')
    text = '\n'.join(lines)
    with open(os.path.join(args.out_dir, 'summary.txt'), 'w') as fh:
        fh.write(text + '\n')
    print(text)
    if drop_a or drop_b:
        print(f'snap-dropped frames: A={drop_a} B={drop_b}')


def ImageChops_difference(a, b):
    from PIL import ImageChops
    return ImageChops.difference(a, b)


# ---------------------------------------------------------------- exhibit

def cmd_exhibit(args):
    a = Image.open(args.frame_a).convert('RGB')
    b = Image.open(args.frame_b).convert('RGB')
    va, ra = detect_viewport(a, args.map_w, args.map_h)
    vb, rb = detect_viewport(b, args.map_w, args.map_h)
    print(f'exhibit viewports: A={va} B={vb}')
    if va is None or vb is None or va != vb:
        print('WARNING: viewports differ or undetected - per-cell table limited to overlap')
    extra_a = parse_rect(args.extra_mask_a) if args.extra_mask_a else None
    masks = build_masks(args.map_w, args.map_h, extra_a)
    cells = admissible_cells(masks, False)
    rows = []
    for (r, c) in cells:
        ca, cb = cell_image(a, r, c), cell_image(b, r, c)
        m = mad(ca, cb)
        R = (va[1] if va else 0) + r
        C = (va[0] if va else 0) + c
        rows.append((R, C, r, c, round(m, 2)))
    with open(args.out_prefix + '_cells.csv', 'w', newline='') as fh:
        w = csv.writer(fh)
        w.writerow(['R', 'C', 'view_r', 'view_c', 'mad'])
        w.writerows(rows)
    from PIL import ImageChops
    side = Image.new('RGB', (640 * 2 + 8, 480), (0, 0, 0))
    side.paste(a, (0, 0))
    side.paste(b, (648, 0))
    side.save(args.out_prefix + '_sidebyside.png')
    ImageChops.difference(a, b).convert('L').point(
        lambda v: min(255, v * 3)).save(args.out_prefix + '_diff.png')
    vals = [r[4] for r in rows]
    print(f'exhibit cells: {len(rows)}, mad mean={sum(vals)/len(vals):.2f} '
          f'max={max(vals):.2f} -> {args.out_prefix}_cells.csv')


# ---------------------------------------------------------------- main

def main():
    p = argparse.ArgumentParser(description=__doc__,
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest='cmd', required=True)

    pi = sub.add_parser('index')
    pi.add_argument('--frames', required=True)
    pi.add_argument('--engine', required=True, choices=['orig', 'rec'])
    pi.add_argument('--run-id', default='run1')
    pi.add_argument('--map-w', type=int, required=True)
    pi.add_argument('--map-h', type=int, required=True)
    pi.add_argument('--extra-mask')
    pi.add_argument('--out', required=True)
    pi.set_defaults(func=cmd_index)

    pm = sub.add_parser('maskaudit')
    pm.add_argument('--frame', required=True)
    pm.add_argument('--map-w', type=int, required=True)
    pm.add_argument('--map-h', type=int, required=True)
    pm.add_argument('--vl', type=int)
    pm.add_argument('--vt', type=int)
    pm.add_argument('--extra-mask')
    pm.add_argument('--include-row6', action='store_true')
    pm.add_argument('--out', required=True)
    pm.set_defaults(func=cmd_maskaudit)

    ps = sub.add_parser('score')
    ps.add_argument('--index-a', nargs='+', required=True)
    ps.add_argument('--index-b', nargs='+', required=True)
    ps.add_argument('--map-w', type=int, required=True)
    ps.add_argument('--map-h', type=int, required=True)
    ps.add_argument('--extra-mask-a')
    ps.add_argument('--extra-mask-b')
    ps.add_argument('--include-row6', action='store_true')
    ps.add_argument('--k-cap', type=int, default=8)
    ps.add_argument('--shift', help='dx,dy negative control on index B')
    ps.add_argument('--dac-normalize', action='store_true',
                    help='quantize both sides to VGA 6-bit DAC before comparing')
    ps.add_argument('--t-anim', type=float, default=8.0)
    ps.add_argument('--t-unit', type=float, default=20.0)
    ps.add_argument('--t-maxd', type=int, default=6,
                    help='max per-channel diff for pixel-perfect identity (DAC)')
    ps.add_argument('--t-ident-mad', type=float, default=8.0,
                    help='max mean-abs-diff for terrain identity (dither/DAC tolerant)')
    ps.add_argument('--out-dir', required=True)
    ps.set_defaults(func=cmd_score)

    pe = sub.add_parser('exhibit')
    pe.add_argument('--frame-a', required=True)
    pe.add_argument('--frame-b', required=True)
    pe.add_argument('--map-w', type=int, required=True)
    pe.add_argument('--map-h', type=int, required=True)
    pe.add_argument('--extra-mask-a')
    pe.add_argument('--out-prefix', required=True)
    pe.set_defaults(func=cmd_exhibit)

    args = p.parse_args()
    args.func(args)


if __name__ == '__main__':
    main()
