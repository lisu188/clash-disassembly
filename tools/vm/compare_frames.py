#!/usr/bin/env python3
"""Pair an original (QEMU/Win98) capture with a recovered-engine frame and
quantify their similarity, for the original-vs-reconstruction fidelity report.

Usage:
  compare_frames.py <original.png> <recovered.png> <out_prefix> [label]

Emits:
  <out_prefix>_sidebyside.png   original | recovered, same height
  <out_prefix>_diff.png         per-pixel absolute-difference heatmap
  and prints one metrics line:
     label WxH mad=<mean-abs-diff 0..255> pctdiff=<% pixels differing >16>
            palcorr=<gray-histogram correlation 0..1>

Both frames are normalized to a common size (the smaller of the two) before
comparison; the game world-map states are deterministic across the SDL
reconstruction and the DirectDraw original, so a low MAD + high palette
correlation is the expected fidelity signal (cursor/fog/palette-timing aside).
"""
import sys

from PIL import Image, ImageChops


def load(path, size=None):
    im = Image.open(path).convert('RGB')
    if size and im.size != size:
        im = im.resize(size, Image.NEAREST)
    return im


def main():
    orig_p, rec_p, out = sys.argv[1], sys.argv[2], sys.argv[3]
    label = sys.argv[4] if len(sys.argv) > 4 else ''
    o = Image.open(orig_p).convert('RGB')
    r = Image.open(rec_p).convert('RGB')
    w = min(o.size[0], r.size[0])
    h = min(o.size[1], r.size[1])
    o = load(orig_p, (w, h))
    r = load(rec_p, (w, h))

    diff = ImageChops.difference(o, r)
    dg = diff.convert('L')
    px = list(dg.getdata())
    n = len(px) or 1
    mad = sum(px) / n
    pctdiff = 100.0 * sum(1 for v in px if v > 16) / n

    ho = o.convert('L').histogram()
    hr = r.convert('L').histogram()
    so, sr = sum(ho) or 1, sum(hr) or 1
    ho = [c / so for c in ho]
    hr = [c / sr for c in hr]
    mo, mr = sum(ho) / 256, sum(hr) / 256
    cov = sum((ho[i] - mo) * (hr[i] - mr) for i in range(256))
    vo = sum((ho[i] - mo) ** 2 for i in range(256)) ** 0.5
    vr = sum((hr[i] - mr) ** 2 for i in range(256)) ** 0.5
    palcorr = cov / (vo * vr) if vo and vr else 0.0

    side = Image.new('RGB', (w * 2 + 8, h), (0, 0, 0))
    side.paste(o, (0, 0))
    side.paste(r, (w + 8, 0))
    side.save(out + '_sidebyside.png')
    # brighten the diff so faint deltas are visible
    dg.point(lambda v: min(255, v * 3)).save(out + '_diff.png')

    print(f"{label} {w}x{h} mad={mad:.2f} pctdiff={pctdiff:.1f} palcorr={palcorr:.3f}")


if __name__ == '__main__':
    main()
