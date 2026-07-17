#!/usr/bin/env python3
"""Screendump the running VM via QMP and convert PPM->PNG, with quick stats.

Usage: vm_shot.py <qmp.sock> <out.png> [label]
Prints: WxH colors=<n> mean_lum=<f> nonblack=<n>  -- used to drive the installer
checkpoint loop (decide the next keystrokes) and to gate capture stability.
"""
import os
import subprocess
import sys
import tempfile

from PIL import Image

HERE = os.path.dirname(os.path.abspath(__file__))


def screendump(sock, ppm_path):
    subprocess.run([sys.executable, os.path.join(HERE, 'qmp.py'), sock, 'shot', ppm_path],
                   check=True, capture_output=True, text=True)


def main():
    sock, out = sys.argv[1], sys.argv[2]
    label = sys.argv[3] if len(sys.argv) > 3 else ''
    with tempfile.NamedTemporaryFile(suffix='.ppm', delete=False) as tf:
        ppm = tf.name
    try:
        screendump(sock, ppm)
        # QEMU writes the PPM asynchronously; wait briefly for it to be non-empty.
        import time
        for _ in range(40):
            if os.path.exists(ppm) and os.path.getsize(ppm) > 64:
                break
            time.sleep(0.1)
        im = Image.open(ppm).convert('RGB')
        im.save(out)
        g = im.convert('L').histogram()
        total = sum(g) or 1
        mean = sum(i * c for i, c in enumerate(g)) / total
        nonblack = total - g[0]
        colors = im.getcolors(maxcolors=1 << 20)
        nc = len(colors) if colors else -1
        print(f"{im.size[0]}x{im.size[1]} colors={nc} mean_lum={mean:.1f} nonblack={nonblack} {label}")
    finally:
        try:
            os.unlink(ppm)
        except OSError:
            pass


if __name__ == '__main__':
    main()
