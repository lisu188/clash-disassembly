#!/usr/bin/env python3
"""Frame classifier for clash95 capture series - ORIGINAL clash95.exe shots
(Win98/QEMU) and recovered clash95_bootstrap frame dumps alike.

Why: the original opens the MANUAL tactical battle unattended during all-AI
/A<n> runs, so a battle frame can land anywhere in a capture series.  This
labels every frame in a directory (or a whole capture tree) so battle frames
are mined automatically instead of eyeballed.

Labels: black, blank, world-map, tactical-battle, menu, unknown.

Every test is STRUCTURAL - it reconstructs the screen boxes the draw code lays
down - so a black/transition frame cannot pass the battle test by merely
lacking a minimap.

Authoritative geometry (same recovered sources as tile_compare.py and
battle_compare.py):
- Both in-game screens sit in the ornate frame with playfield origin (32,16)
  and 64x64 tiles, so a hard vertical edge runs down x=31|32 for the full
  playfield height.
- WORLD MAP: 9 cols x 7 rows visible (units_005.c:668-707) -> playfield
  x[32,607]; the ornate right border starts at x=608, giving an edge at
  x=607|608.  The minimap panel (world_003.c:1352-1439) carries a pure-white
  viewport-box OUTLINE of outer size (ppt*9+2) x (ppt*7+2), ppt in {2,4}.
- TACTICAL BATTLE: a 7x7 window (battle_002.c:898-899, redraw bounds
  battle_002.c:1259-1266) -> board x[32,479] y[16,463], exactly 448x448 = 7*64,
  with the HUD / action panel filling x[480,639] for the whole screen height.
  There is no minimap in battle.
  So the battle test is: all four edges of the 7x64 board box, a 64px-aligned
  interior grid, a non-degenerate HUD strip to its right, NO world-map
  playfield edge at x=607, and no minimap outline.
- MENU: no playfield frame at all, but a full-screen palettised artwork - a
  high distinct-colour count with few flat runs separates the game's menu
  screens from flat Windows/DOS screenshots that share the 640x480 size.

Edges are measured on 4px column/row block means, not raw neighbouring pixels:
Win9x screens (and the game's own terrain) are 1px-dithered, so a raw
neighbour-diff saturates everywhere and detects nothing.  The frame is also
contrast-normalised first (gain up to 4x onto a fixed 99th-percentile target),
so the half-faded frames of the battle fade-in still expose their box edges.

Subcommands:
  classify  - label every frame in a directory (or single files) -> table/CSV
  scan      - walk a capture tree, label everything, flag any tactical battle
  confusion - classify labelled ground-truth sets, print a confusion matrix
"""
import argparse
import csv
import os
import sys

import numpy as np
from PIL import Image

SCREEN = (640, 480)

TILE = 64
GRID_X0 = 32
GRID_Y0 = 16

BATTLE_VIEW = 7                                       # 7x7 battle window
WORLD_VIEW_COLS = 9                                   # 9 cols on the world map
WORLD_VIEW_ROWS = 7

BOARD_TOP = GRID_Y0                                   # 16
BOARD_BOTTOM = GRID_Y0 + TILE * BATTLE_VIEW - 1       # 463
BATTLE_RIGHT = GRID_X0 + TILE * BATTLE_VIEW - 1       # 479
WORLD_RIGHT = GRID_X0 + TILE * WORLD_VIEW_COLS - 1    # 607
FRAME_LEFT = GRID_X0 - 1                              # 31
FRAME_TOP = GRID_Y0 - 1                               # 15

EDGE_BLOCK = 4         # block width used to average away 1px dither
EDGE_DELTA = 24.0      # mean-RGB step between the two blocks that counts
EDGE_STRONG = 0.55     # fraction of the span that must show that step
EDGE_WEAK = 0.45       # below this the edge counts as absent
EDGE_BORDER = 0.45     # top/bottom playfield borders are looser (unit sprites
                       # and the nameplate ribbon interrupt them)
EDGE_GAIN_TARGET = 180.0   # 99th-percentile luma the edge pass normalises to
EDGE_GAIN_MAX = 4.0        # cap, so a black frame is never amplified to noise

BLACK_MEAN = 8.0
BLACK_STD = 3.0
BLANK_STD = 2.5

HUD_MIN_MEAN = 12.0    # the battle HUD strip is lit art, never black
HUD_MIN_STD = 6.0
BOARD_MIN_STD = 6.0    # the board carries terrain, never a flat fill

MENU_MIN_COLORS = 120  # dithered 8bpp artwork; Win98/DOS shots peak near 67
MENU_MAX_FLAT = 0.35   # fraction of pixels inside a >=8px flat horizontal run
MENU_MIN_STD = 12.0

LABELS = ('black', 'blank', 'world-map', 'tactical-battle', 'menu', 'unknown')

FRAME_EXT = ('.png', '.bmp', '.ppm', '.pgm', '.pnm', '.jpg', '.jpeg', '.gif',
             '.tif', '.tiff')


# ---------------------------------------------------------------- loading

def load_frame(path):
    """-> (float32 HxWx3, uint8 HxWx3, None) or (None, None, reason)."""
    try:
        im = Image.open(path).convert('RGB')
    except Exception as e:                            # noqa: BLE001
        return None, None, 'unreadable:%s' % e
    if im.size != SCREEN:
        return None, None, 'not-640x480:%dx%d' % im.size
    u8 = np.asarray(im, dtype=np.uint8)
    return u8.astype(np.float32), u8, None


# ---------------------------------------------------------------- edges

def edge_gain(a):
    """Contrast gain applied before the edge pass.  The battle fade-in presents
    the whole screen at a fraction of its final brightness, which would drop
    every box edge below EDGE_DELTA; normalising onto a fixed 99th-percentile
    luma keeps those frames detectable without touching the raw statistics."""
    p99 = float(np.percentile(a.mean(axis=2), 99))
    if p99 <= 1.0:
        return 1.0
    return float(min(EDGE_GAIN_MAX, max(1.0, EDGE_GAIN_TARGET / p99)))


def col_edge(a, x, y0=BOARD_TOP, y1=BOARD_BOTTOM, k=EDGE_BLOCK):
    """Fraction of rows in [y0,y1] where the k-px block means straddling the
    x|x+1 boundary differ by more than EDGE_DELTA."""
    left = a[y0:y1 + 1, x - k + 1:x + 1, :].mean(axis=1)
    right = a[y0:y1 + 1, x + 1:x + 1 + k, :].mean(axis=1)
    return float((np.abs(left - right).mean(axis=1) > EDGE_DELTA).mean())


def row_edge(a, y, x0, x1, k=EDGE_BLOCK):
    """Same, for the y|y+1 boundary across columns [x0,x1]."""
    up = a[y - k + 1:y + 1, x0:x1 + 1, :].mean(axis=0)
    down = a[y + 1:y + 1 + k, x0:x1 + 1, :].mean(axis=0)
    return float((np.abs(up - down).mean(axis=1) > EDGE_DELTA).mean())


def grid64_score(a, x0=GRID_X0, x1=BATTLE_RIGHT, y0=BOARD_TOP, y1=BOARD_BOTTOM):
    """64px-grid evidence inside the board box: mean column-step energy on the
    interior tile boundaries (x = 32+64k-1) minus the median off them.  Battle
    terrain is drawn per 64px cell from a tile atlas, so the cell seams carry
    more step energy than the cell interiors.  Reported always; only used as a
    tie-breaker, since a board of one repeated tile has no visible seams."""
    d = np.abs(a[y0:y1 + 1, x0 + 1:x1 + 1, :]
               - a[y0:y1 + 1, x0:x1, :]).mean(axis=2).mean(axis=0)
    idx = np.arange(d.shape[0]) + x0        # column index of the left pixel
    on = ((idx - x0 + 1) % TILE) == 0
    on[0] = False
    if not on.any() or not (~on).any():
        return 0.0
    return float(d[on].mean() - np.median(d[~on]))


# ---------------------------------------------------------------- minimap

def minimap_outline(u8):
    """Map-size agnostic hunt for the world-map minimap viewport box.

    world_003.c:1352-1439 draws a pure-white (255,255,255) rectangle OUTLINE of
    outer size (ppt*9+2) x (ppt*7+2) with ppt in {2,4} -> 20x16 or 38x30.  The
    panel's right edge is pinned at x=608 and its top at y=16, so the outline
    always lands in the upper-right.  Require an exact-length white run, all
    four verified sides and a non-solid interior.
    """
    white = (u8[:, :, 0] == 255) & (u8[:, :, 1] == 255) & (u8[:, :, 2] == 255)
    H, W = white.shape
    for ppt in (2, 4):
        bw = ppt * WORLD_VIEW_COLS + 2
        bh = ppt * WORLD_VIEW_ROWS + 2
        rows = np.flatnonzero(white[:H - bh].any(axis=1))
        for y in rows:
            row = white[y]
            xs = np.flatnonzero(row)
            for x in xs:
                if x + bw > W or (x and row[x - 1]):
                    continue
                if not row[x:x + bw].all() or (x + bw < W and row[x + bw]):
                    continue
                if not (white[y + bh - 1, x:x + bw].all()
                        and white[y:y + bh, x].all()
                        and white[y:y + bh, x + bw - 1].all()):
                    continue
                inner = white[y + 1:y + bh - 1, x + 1:x + bw - 1]
                if inner.size and inner.mean() < 0.9:
                    return {'ppt': ppt, 'x': int(x), 'y': int(y),
                            'w': bw, 'h': bh}
    return None


# ---------------------------------------------------------------- features

def region_stats(a, x0, y0, x1, y1):
    g = a[y0:y1 + 1, x0:x1 + 1, :].mean(axis=2)
    return float(g.mean()), float(g.std())


def color_count(u8, step=3):
    f = u8[::step, ::step, :].reshape(-1, 3).astype(np.uint32)
    return int(np.unique((f[:, 0] << 16) | (f[:, 1] << 8) | f[:, 2]).size)


def flat_fraction(u8, run=8):
    """Fraction of pixels that start a horizontal run of `run` identical
    pixels.  Windows/DOS chrome is full of flat runs; the game's dithered
    artwork is not."""
    a = u8.astype(np.int32)
    key = (a[:, :, 0] << 16) | (a[:, :, 1] << 8) | a[:, :, 2]
    same = key[:, 1:] == key[:, :-1]
    width = same.shape[1] - run + 2
    acc = same[:, :width].copy()
    for k in range(1, run - 1):
        acc &= same[:, k:width + k]
    return float(acc.mean())


def features(a, u8):
    f = {}
    g = a.mean(axis=2)
    f['mean'] = float(g.mean())
    f['std'] = float(g.std())
    f['gain'] = edge_gain(a)
    e = a * f['gain'] if f['gain'] != 1.0 else a
    f['edge_left31'] = col_edge(e, FRAME_LEFT)
    f['edge_battle479'] = col_edge(e, BATTLE_RIGHT)
    f['edge_world607'] = col_edge(e, WORLD_RIGHT)
    f['edge_top_board'] = row_edge(e, FRAME_TOP, GRID_X0, BATTLE_RIGHT)
    f['edge_bot_board'] = row_edge(e, BOARD_BOTTOM, GRID_X0, BATTLE_RIGHT)
    f['edge_top_world'] = row_edge(e, FRAME_TOP, GRID_X0, WORLD_RIGHT)
    f['edge_bot_world'] = row_edge(e, BOARD_BOTTOM, GRID_X0, WORLD_RIGHT)
    f['board_mean'], f['board_std'] = region_stats(a, GRID_X0, BOARD_TOP,
                                                   BATTLE_RIGHT, BOARD_BOTTOM)
    f['hud_mean'], f['hud_std'] = region_stats(a, BATTLE_RIGHT + 1, 0, 639, 479)
    f['grid64'] = grid64_score(e)
    f['colors'] = color_count(u8)
    f['flat'] = flat_fraction(u8)
    f['minimap'] = minimap_outline(u8)
    return f


# ---------------------------------------------------------------- classify

def classify_features(f):
    """-> (label, reason)."""
    if f['mean'] < BLACK_MEAN and f['std'] < BLACK_STD:
        return 'black', 'luma mean=%.1f std=%.1f' % (f['mean'], f['std'])
    if f['std'] < BLANK_STD:
        return 'blank', 'uniform fill mean=%.1f std=%.1f' % (f['mean'], f['std'])

    left = f['edge_left31'] >= EDGE_STRONG

    battle_box = (left
                  and f['edge_battle479'] >= EDGE_STRONG
                  and f['edge_top_board'] >= EDGE_BORDER
                  and f['edge_bot_board'] >= EDGE_BORDER
                  and f['edge_world607'] < EDGE_WEAK)
    hud_ok = f['hud_mean'] >= HUD_MIN_MEAN and f['hud_std'] >= HUD_MIN_STD
    board_ok = f['board_std'] >= BOARD_MIN_STD

    if battle_box and hud_ok and board_ok and f['minimap'] is None:
        return 'tactical-battle', (
            '7x64 board box x[32,479] y[16,463] edges L=%.2f R=%.2f T=%.2f '
            'B=%.2f, no world playfield edge at 607 (%.2f), HUD x[480,639] '
            'mean=%.1f std=%.1f, grid64=%.2f'
            % (f['edge_left31'], f['edge_battle479'], f['edge_top_board'],
               f['edge_bot_board'], f['edge_world607'], f['hud_mean'],
               f['hud_std'], f['grid64']))

    if f['minimap'] is not None:
        mm = f['minimap']
        return 'world-map', ('minimap viewport outline %dx%d ppt=%d at (%d,%d)'
                             % (mm['w'], mm['h'], mm['ppt'], mm['x'], mm['y']))

    if (left and f['edge_world607'] >= EDGE_STRONG
            and f['edge_top_world'] >= EDGE_BORDER
            and f['edge_bot_world'] >= EDGE_BORDER
            and f['board_std'] >= BOARD_MIN_STD):
        # ornate frame plus the 9-col playfield edge, but the viewport outline
        # is hidden (minimap panel toggled off / covered) - still the world map.
        return 'world-map', ('9-col playfield edge x=607 (%.2f) inside the '
                             'ornate frame (L=%.2f T=%.2f B=%.2f), viewport '
                             'outline not visible'
                             % (f['edge_world607'], f['edge_left31'],
                                f['edge_top_world'], f['edge_bot_world']))

    if (not left and f['colors'] >= MENU_MIN_COLORS
            and f['flat'] <= MENU_MAX_FLAT and f['std'] >= MENU_MIN_STD):
        return 'menu', ('no playfield frame (left edge %.2f); full-screen '
                        'palettised artwork colors=%d flat=%.2f std=%.1f'
                        % (f['edge_left31'], f['colors'], f['flat'], f['std']))

    return 'unknown', ('L31=%.2f R479=%.2f R607=%.2f T=%.2f B=%.2f colors=%d '
                       'flat=%.2f std=%.1f'
                       % (f['edge_left31'], f['edge_battle479'],
                          f['edge_world607'], f['edge_top_world'],
                          f['edge_bot_world'], f['colors'], f['flat'],
                          f['std']))


def classify_path(path):
    a, u8, err = load_frame(path)
    if err:
        return {'path': path, 'label': 'unknown', 'reason': err, 'features': {}}
    f = features(a, u8)
    label, reason = classify_features(f)
    return {'path': path, 'label': label, 'reason': reason, 'features': f}


# ---------------------------------------------------------------- reporting

FIELDS = ['path', 'label', 'reason', 'mean', 'std', 'gain', 'edge_left31',
          'edge_battle479', 'edge_world607', 'edge_top_board',
          'edge_bot_board', 'edge_top_world', 'edge_bot_world', 'board_std',
          'hud_mean', 'hud_std', 'grid64', 'colors', 'flat', 'minimap']


def row_of(res):
    f = res['features']
    mm = f.get('minimap')
    row = {'path': res['path'], 'label': res['label'], 'reason': res['reason'],
           'minimap': '%d,%d,ppt%d' % (mm['x'], mm['y'], mm['ppt']) if mm else ''}
    for k in FIELDS:
        if k in ('path', 'label', 'reason', 'minimap'):
            continue
        v = f.get(k, '')
        row[k] = round(v, 3) if isinstance(v, float) else v
    return row


def list_frames(directory):
    return sorted(os.path.join(directory, f) for f in os.listdir(directory)
                  if f.lower().endswith(FRAME_EXT)
                  and os.path.isfile(os.path.join(directory, f)))


def collect(sources):
    paths = []
    for src in sources:
        if os.path.isdir(src):
            paths.extend(list_frames(src))
        else:
            paths.append(src)
    return paths


def tally(results):
    counts = {}
    for r in results:
        counts[r['label']] = counts.get(r['label'], 0) + 1
    return counts


def fmt_tally(counts):
    return ' '.join('%s=%d' % (k, counts[k]) for k in LABELS if counts.get(k))


def write_csv(path, results):
    with open(path, 'w', newline='') as fh:
        w = csv.DictWriter(fh, fieldnames=FIELDS)
        w.writeheader()
        w.writerows(row_of(r) for r in results)
    print('csv -> %s' % path)


def report_battles(results):
    hits = [r for r in results if r['label'] == 'tactical-battle']
    if hits:
        print('TACTICAL BATTLE FRAMES (%d):' % len(hits))
        for r in hits:
            print('  %s\n    %s' % (r['path'], r['reason']))
    return hits


# ---------------------------------------------------------------- commands

def cmd_classify(args):
    results = [classify_path(p) for p in collect(args.frames)]
    for r in results:
        if args.only and r['label'] != args.only:
            continue
        print('%-16s %-44s %s' % (r['label'], os.path.basename(r['path']),
                                  r['reason'] if args.verbose else ''))
    print('total %d: %s' % (len(results), fmt_tally(tally(results))))
    report_battles(results)
    if args.csv:
        write_csv(args.csv, results)
    return 0


def cmd_scan(args):
    results = []
    grand = {}
    for root, dirs, files in os.walk(args.root):
        dirs.sort()
        paths = sorted(os.path.join(root, f) for f in files
                       if f.lower().endswith(FRAME_EXT))
        if not paths:
            continue
        part = [classify_path(p) for p in paths]
        results.extend(part)
        counts = tally(part)
        for k, v in counts.items():
            grand[k] = grand.get(k, 0) + v
        print('%-28s %4d frames  %s'
              % (os.path.relpath(root, args.root), len(part), fmt_tally(counts)))
    print('-' * 72)
    print('TOTAL %d frames  %s' % (len(results), fmt_tally(grand)))
    if not report_battles(results):
        print('NO tactical-battle frames under %s' % args.root)
    if args.csv:
        write_csv(args.csv, results)
    return 0


def cmd_confusion(args):
    truth = []
    for spec in args.truth:
        label, _, src = spec.partition('=')
        if label not in LABELS:
            raise SystemExit('unknown truth label %r (choose from %s)'
                             % (label, ', '.join(LABELS)))
        paths = collect([src])
        if not paths:
            raise SystemExit('no frames under %s' % src)
        truth.extend((label, p) for p in paths)

    matrix = {}
    wrong = []
    for label, path in truth:
        res = classify_path(path)
        key = (label, res['label'])
        matrix[key] = matrix.get(key, 0) + 1
        if res['label'] != label:
            wrong.append((label, res['label'], path, res['reason']))

    rows = [l for l in LABELS if any(k[0] == l for k in matrix)]
    cols = [l for l in LABELS if any(k[1] == l for k in matrix)]
    w = max([len(c) for c in cols] + [8]) + 2
    print('confusion matrix (rows = truth, cols = predicted)')
    print('%-18s%s' % ('truth \\ pred', ''.join('%*s' % (w, c) for c in cols)))
    for t in rows:
        print('%-18s%s' % (t, ''.join('%*d' % (w, matrix.get((t, c), 0))
                                      for c in cols)))
    total = sum(matrix.values())
    right = sum(v for k, v in matrix.items() if k[0] == k[1])
    print('accuracy %d/%d = %.1f%%' % (right, total, 100.0 * right / (total or 1)))
    for t, p, path, why in wrong:
        print('  MISLABELLED truth=%s predicted=%s %s\n    %s' % (t, p, path, why))
    return 0 if not wrong else 1


def main():
    p = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest='cmd', required=True)

    pc = sub.add_parser('classify', help='label frames in directories/files')
    pc.add_argument('--frames', nargs='+', required=True,
                    help='directories and/or single frame files')
    pc.add_argument('--csv')
    pc.add_argument('--verbose', action='store_true')
    pc.add_argument('--only', choices=LABELS,
                    help='print only rows with this label (tally is unfiltered)')
    pc.set_defaults(func=cmd_classify)

    ps = sub.add_parser('scan', help='walk a capture tree, flag any battle')
    ps.add_argument('--root', required=True)
    ps.add_argument('--csv')
    ps.set_defaults(func=cmd_scan)

    pk = sub.add_parser('confusion', help='score against labelled ground truth')
    pk.add_argument('--truth', nargs='+', required=True, metavar='LABEL=PATH',
                    help='e.g. world-map=caps/m05-frames tactical-battle=x.bmp')
    pk.set_defaults(func=cmd_confusion)

    args = p.parse_args()
    return args.func(args)


if __name__ == '__main__':
    sys.exit(main())
