#!/usr/bin/env python3
"""Tactical-BATTLE-view comparison: ORIGINAL clash95.exe (Win98/QEMU captures)
vs the recovered engine (clash95_bootstrap frame dumps).

Sibling of tile_compare.py (world map). The battle board is a square 64x64 grid,
NOT the world map's layout, so the geometry differs — authoritative recovered
source:

- Grid: 64x64 px cells, origin (32,16), a 7x7 visible window (VIEW=7, not 9).
  Board extent x[32,479] y[16,463] (a 448x448 square, top-left).
  Draw loop UnitBattle_DrawTileContents src/battle/0042E9E0_00430C20_battle_002.c
  :898-899:  screen_x = ((tileRow - cam808) << 6) + 32
             screen_y = ((tileCol - cam812) << 6) + 16
  Note the AXIS TRANSPOSITION vs the world map: the map ROW index drives screen
  X, the COL index drives screen Y. BattleUnitEntry.grid_x(+4)=tileRow,
  grid_y(+6)=tileCol (battle_003.c:803-804,567-574). Click inverse
  battle_001.c:49-59 (localRow=(mouseX-32)>>6, localCol=(mouseY-16)>>6, <=6).
- camCol (cam812/+812) is ALWAYS 0: map width (+800) is hard-fixed at 7, so the
  col-scroll clamp is [0,0] -> the 7 columns sit permanently at Y[16,463]. Only
  camRow (cam808/+808) scrolls, over a rowCount(<=20)-row map. There is NO
  minimap in battle, so camRow cannot be recovered from a panel -> supply it with
  --cam-row (deterministic for a given battle+turn: opening frame centers on the
  active unit, camRow = attacker.tileRow-3 clamped, or 0 for small maps).
- No battle fog-of-war (the full 7x7 window is always drawn). Per-cell unit
  animations (idle 8-frame battle_003.c:502-544, charge pulse, threat marks,
  projectiles, move-slide) churn animated cells frame-to-frame while static
  terrain/idle-still cells stay byte-identical -> the per-cell atlas + MAD/DAC
  identity buckets from tile_compare apply directly. Only the RNG-free OPENING
  battlefield frame (post-placement, pre-exchange) is frame-comparable; combat is
  time-seeded RNG (units_004.c:1062-1064).
- UI masks: right HUD panel x[480,639] (always); selected-unit info panel
  x[335,479] (conditional; --mask-info-panel); thin frame borders.

Battle frames are MINED from a capture series with the sibling
tools/vm/frame_classify.py (`classify` / `scan`), which labels each frame
black / world-map / tactical-battle / menu structurally - the original opens
this screen unattended in all-AI /A<n> runs, so battle frames can land anywhere
in a window.

Subcommands:
  index     - validate 640x480 battle frames + stamp cam_row -> CSV
  score     - per-cell atlas comparison of two index sets -> reports
  exhibit   - masked full-frame + per-cell diff of two frames
(selftest = `score` with two same-engine index sets; use --shift for the
negative control.)
"""
import argparse
import csv
import os
import sys

from PIL import Image, ImageDraw, ImageChops

TILE = 64
GRID_X0 = 32
GRID_Y0 = 16
VIEW = 7                      # 7x7 visible battle window
BOARD = (32, 16, 479, 463)   # comparable board region (inclusive)


# ---------------------------------------------------------------- geometry

def cell_rect(sx, sy):
    """Screen rect of viewport cell (sx=horizontal/tileRow-axis,
    sy=vertical/tileCol-axis). x = 32 + 64*sx, y = 16 + 64*sy."""
    x0 = GRID_X0 + TILE * sx
    y0 = GRID_Y0 + TILE * sy
    return x0, y0, x0 + TILE - 1, y0 + TILE - 1


def build_masks(mask_info_panel=False, extra_mask=None):
    """Masked screen rects (x0,y0,x1,y1 inclusive)."""
    masks = [
        (480, 0, 639, 479),    # right HUD / action panel (always)
        (0, 0, 639, 15),       # top frame border
        (0, 464, 639, 479),    # bottom frame border
        (0, 0, 31, 479),       # left frame border
    ]
    if mask_info_panel:
        masks.append((335, 0, 479, 479))  # selected-unit info panel
    if extra_mask:
        masks.append(extra_mask)
    return masks


def rects_overlap(a, b):
    return not (a[2] < b[0] or b[2] < a[0] or a[3] < b[1] or b[3] < a[1])


def admissible_cells(masks):
    """Viewport (sx,sy) cells fully unmasked."""
    out = []
    for sy in range(VIEW):
        for sx in range(VIEW):
            rect = cell_rect(sx, sy)
            if any(rects_overlap(rect, m) for m in masks):
                continue
            out.append((sx, sy))
    return out


# ---------------------------------------------------------------- metrics
# (identical machinery to tile_compare.py: dithered terrain differs by a full
# palette step between the 6-bit DirectDraw DAC and the 8-bit SDL path, so MEAN
# abs diff — not per-pixel max — is the robust identity metric.)

def cell_image(img, sx, sy):
    x0, y0, x1, y1 = cell_rect(sx, sy)
    return img.crop((x0, y0, x1 + 1, y1 + 1))


def dac6(img):
    return img.point(lambda v: v & 0xFC)


def pair_metrics(a, b):
    d = ImageChops.difference(a, b)
    h = d.histogram()
    total = count = maxd = 0
    for ch in range(3):
        for v in range(256):
            cnt = h[ch * 256 + v]
            if cnt:
                total += v * cnt
                count += cnt
                if v > maxd:
                    maxd = v
    gray = d.convert('L')
    gh = gray.point(lambda v: 255 if v > 16 else 0).histogram()
    npx = a.size[0] * a.size[1]
    pct = gh[255] / npx if npx else 0.0
    return total / (count or 1), maxd, pct


def mad(a, b):
    return pair_metrics(a, b)[0]


def classify(best, maxd, pct, sa, sb, t):
    def dyn(ss):
        if len(ss) < 2:
            return 0.0
        return max(mad(a, b) for i, (a, _) in enumerate(ss)
                   for (b, _) in [x for x in ss[i + 1:]])
    da, db = dyn(sa), dyn(sb)
    if best <= t['ident_mad']:
        if maxd <= t['maxd']:
            return 'identical-pixel'
        return 'identical-terrain'
    if da > t['unit'] or db > t['unit']:
        return 'unit-occupied'
    return 'content-mismatch'


CLASS_COLORS = {
    'unobserved': (60, 60, 60),
    'orig-only': (60, 90, 200),
    'rec-only': (0, 190, 190),
    'identical-pixel': (40, 220, 40),
    'identical-terrain': (60, 170, 60),
    'unit-occupied': (240, 140, 30),
    'content-mismatch': (230, 40, 40),
}


# ---------------------------------------------------------------- index

def validate_frame(path):
    try:
        img = Image.open(path).convert('RGB')
    except Exception as e:                       # noqa: BLE001
        return None, 'unreadable:%s' % e
    if img.size != (640, 480):
        return None, 'not-640x480:%dx%d' % img.size
    return img, 'ok'


def cmd_index(args):
    rows = []
    files = sorted(f for f in os.listdir(args.frames)
                   if f.lower().endswith(('.png', '.bmp')))
    for f in files:
        p = os.path.join(args.frames, f)
        img, status = validate_frame(p)
        rows.append({'path': p, 'engine': args.engine, 'run_id': args.run_id,
                     'cam_row': args.cam_row, 'status': status})
    with open(args.out, 'w', newline='') as fh:
        w = csv.DictWriter(fh, fieldnames=['path', 'engine', 'run_id',
                                           'cam_row', 'status'])
        w.writeheader()
        w.writerows(rows)
    ok = sum(1 for r in rows if r['status'] == 'ok')
    print('battle index: %d frames, %d ok, cam_row=%d -> %s'
          % (len(rows), ok, args.cam_row, args.out))


def load_index(paths):
    frames = []
    for ip in paths:
        with open(ip) as fh:
            for r in csv.DictReader(fh):
                if r.get('status') == 'ok':
                    r['cam_row'] = int(r['cam_row'])
                    frames.append(r)
    return frames


# ---------------------------------------------------------------- atlas + score

def build_atlas(frames, masks, k_cap, shift=(0, 0), normalize=False,
                keep_min_mad=1.0):
    cells = admissible_cells(masks)
    atlas = {}
    for fr in frames:
        img = Image.open(fr['path']).convert('RGB')
        cam = fr['cam_row']
        for (sx, sy) in cells:
            R = cam + sx + shift[0]     # absolute tileRow
            C = sy + shift[1]           # absolute tileCol
            sample = cell_image(img, sx, sy)
            if normalize:
                sample = dac6(sample)
            bucket = atlas.setdefault((R, C), [])
            if len(bucket) >= k_cap:
                continue
            if not bucket or all(mad(sample, s) > keep_min_mad for s, _ in bucket):
                bucket.append((sample, os.path.basename(fr['path'])))
    return atlas


def cmd_score(args):
    extra_a = parse_rect(args.extra_mask_a) if args.extra_mask_a else None
    extra_b = parse_rect(args.extra_mask_b) if args.extra_mask_b else None
    masks_a = build_masks(args.mask_info_panel, extra_a)
    masks_b = build_masks(args.mask_info_panel, extra_b)
    frames_a = load_index(args.index_a)
    frames_b = load_index(args.index_b)
    shift = tuple(int(v) for v in args.shift.split(',')) if args.shift else (0, 0)
    atlas_a = build_atlas(frames_a, masks_a, args.k_cap, normalize=args.dac_normalize)
    atlas_b = build_atlas(frames_b, masks_b, args.k_cap, shift=shift,
                          normalize=args.dac_normalize)
    t = {'unit': args.t_unit, 'maxd': args.t_maxd, 'ident_mad': args.t_ident_mad}
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
                        'n_a': len(sa), 'n_b': len(sb), 'best_a': fa, 'best_b': fb})

    with open(os.path.join(args.out_dir, 'tiles.csv'), 'w', newline='') as fh:
        w = csv.DictWriter(fh, fieldnames=['R', 'C', 'class', 'best_mad',
                                           'best_maxd', 'pct_diff', 'n_a', 'n_b',
                                           'best_a', 'best_b'])
        w.writeheader()
        w.writerows(results)

    # worst montage (orig | rec | 4x diff)
    bad = [r for r in results if r['class'] in ('content-mismatch', 'unit-occupied')]
    bad.sort(key=lambda r: -r['best_mad'])
    bad = bad[:24]
    if bad:
        mont = Image.new('RGB', (3 * TILE + 40, len(bad) * (TILE + 14)), (25, 25, 25))
        md = ImageDraw.Draw(mont)
        y = 0
        for res in bad:
            sa = next(s for s, f in atlas_a[(res['R'], res['C'])] if f == res['best_a'])
            sb = next(s for s, f in atlas_b[(res['R'], res['C'])] if f == res['best_b'])
            diff = ImageChops.difference(sa, sb).point(lambda v: min(255, v * 4))
            mont.paste(sa, (0, y)); mont.paste(sb, (TILE + 6, y))
            mont.paste(diff, (2 * TILE + 12, y))
            md.text((2, y + TILE + 1),
                    "(%d,%d) %s mad=%s" % (res['R'], res['C'], res['class'], res['best_mad']),
                    fill=(255, 255, 128))
            y += TILE + 14
        mont.save(os.path.join(args.out_dir, 'worst_montage.png'))

    from collections import Counter
    counts = Counter(r['class'] for r in results)
    static = [r for r in results if r['class'] in ('identical-pixel', 'identical-terrain')]
    denom = [r for r in results if r['class'] != 'unit-occupied']
    lines = ['battle_compare score summary',
             '  index A (orig): %s (%d frames)' % (args.index_a, len(frames_a)),
             '  index B (rec):  %s (%d frames)' % (args.index_b, len(frames_b)),
             '  shift (negative control): %s' % (shift,),
             '  dac-normalize: %s   mask-info-panel: %s' % (args.dac_normalize, args.mask_info_panel),
             '  thresholds: %s' % t,
             '  cells: A=%d B=%d both=%d' % (len(atlas_a), len(atlas_b), len(both))]
    for cls in CLASS_COLORS:
        if cls in counts:
            lines.append('  %s: %d' % (cls, counts[cls]))
    if denom:
        lines.append('  matched (identical) / non-unit cells: %d/%d = %.1f%%'
                     % (len(static), len(denom), 100.0 * len(static) / len(denom)))
    lines.append('  known-acceptable: idle/charge/threat animation phase (unit cells),'
                 ' 6-bit-DAC dither, cursor, masked HUD/info panels')
    summary = '\n'.join(lines) + '\n'
    open(os.path.join(args.out_dir, 'summary.txt'), 'w').write(summary)
    sys.stdout.write(summary)


def cmd_exhibit(args):
    masks = build_masks(args.mask_info_panel)
    a = Image.open(args.frame_a).convert('RGB')
    b = Image.open(args.frame_b).convert('RGB')
    for m in masks:
        for im in (a, b):
            ImageDraw.Draw(im).rectangle(m, fill=(0, 0, 0))
    sbs = Image.new('RGB', (640 * 2 + 8, 480), (20, 20, 20))
    sbs.paste(a, (0, 0)); sbs.paste(b, (648, 0))
    sbs.save(args.out_prefix + '_sidebyside.png')
    diff = ImageChops.difference(a, b).point(lambda v: min(255, v * 4))
    diff.save(args.out_prefix + '_diff.png')
    print('exhibit -> %s_{sidebyside,diff}.png  board-MAD=%.2f'
          % (args.out_prefix, mad(a.crop(BOARD), b.crop(BOARD))))


def parse_rect(s):
    return tuple(int(v) for v in s.split(','))


def main():
    p = argparse.ArgumentParser(description=__doc__,
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest='cmd', required=True)

    pi = sub.add_parser('index')
    pi.add_argument('--frames', required=True)
    pi.add_argument('--engine', required=True, choices=['orig', 'rec'])
    pi.add_argument('--run-id', default='run1')
    pi.add_argument('--cam-row', type=int, default=0,
                    help='battle camRow (cam808) for these frames; must match the '
                         'other engine for the same battle/turn')
    pi.add_argument('--out', required=True)
    pi.set_defaults(func=cmd_index)

    ps = sub.add_parser('score')
    ps.add_argument('--index-a', nargs='+', required=True)
    ps.add_argument('--index-b', nargs='+', required=True)
    ps.add_argument('--mask-info-panel', action='store_true')
    ps.add_argument('--extra-mask-a')
    ps.add_argument('--extra-mask-b')
    ps.add_argument('--k-cap', type=int, default=8)
    ps.add_argument('--shift', help='dR,dC negative control on index B')
    ps.add_argument('--dac-normalize', action='store_true')
    ps.add_argument('--t-unit', type=float, default=20.0)
    ps.add_argument('--t-maxd', type=int, default=6)
    ps.add_argument('--t-ident-mad', type=float, default=8.0)
    ps.add_argument('--out-dir', required=True)
    ps.set_defaults(func=cmd_score)

    pe = sub.add_parser('exhibit')
    pe.add_argument('--frame-a', required=True)
    pe.add_argument('--frame-b', required=True)
    pe.add_argument('--mask-info-panel', action='store_true')
    pe.add_argument('--out-prefix', required=True)
    pe.set_defaults(func=cmd_exhibit)

    args = p.parse_args()
    return args.func(args) or 0


if __name__ == '__main__':
    sys.exit(main())
