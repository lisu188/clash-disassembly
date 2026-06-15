#!/usr/bin/env python3
"""Loose visual checks for retained SDL frame-dump BMPs."""

import argparse
import math
import os
import struct
import sys


def read_bmp(path):
    with open(path, "rb") as handle:
        data = handle.read()
    if len(data) < 54 or data[:2] != b"BM":
        raise ValueError("not a BMP file")

    pixel_offset = struct.unpack_from("<I", data, 10)[0]
    dib_size = struct.unpack_from("<I", data, 14)[0]
    if dib_size < 40:
        raise ValueError("unsupported BMP DIB header")

    width_raw = struct.unpack_from("<i", data, 18)[0]
    height_raw = struct.unpack_from("<i", data, 22)[0]
    planes = struct.unpack_from("<H", data, 26)[0]
    bpp = struct.unpack_from("<H", data, 28)[0]
    compression = struct.unpack_from("<I", data, 30)[0]
    colors_used = struct.unpack_from("<I", data, 46)[0] if dib_size >= 40 else 0
    if planes != 1:
        raise ValueError("unsupported BMP planes")
    if width_raw == 0 or height_raw == 0:
        raise ValueError("empty BMP")
    if compression not in (0, 3):
        raise ValueError("compressed BMPs are not supported")
    if bpp not in (8, 24, 32):
        raise ValueError("unsupported BMP depth")

    width = abs(width_raw)
    height = abs(height_raw)
    top_down = height_raw < 0
    rgb_rows = []

    if bpp == 8:
        palette_count = colors_used or 256
        palette_start = 14 + dib_size
        palette = []
        for index in range(palette_count):
            entry_offset = palette_start + 4 * index
            if entry_offset + 4 > len(data):
                break
            blue, green, red, _ = struct.unpack_from("<BBBB", data, entry_offset)
            palette.append((red, green, blue))
        if not palette:
            raise ValueError("8-bit BMP has no palette")
        row_stride = ((width + 3) // 4) * 4
        for row in range(height):
            source_row = row if top_down else height - row - 1
            start = pixel_offset + source_row * row_stride
            row_data = data[start:start + width]
            if len(row_data) < width:
                raise ValueError("truncated BMP row")
            rgb_rows.append([palette[pixel] if pixel < len(palette) else (0, 0, 0) for pixel in row_data])
    else:
        bytes_per_pixel = bpp // 8
        row_stride = ((width * bytes_per_pixel + 3) // 4) * 4
        for row in range(height):
            source_row = row if top_down else height - row - 1
            start = pixel_offset + source_row * row_stride
            row_data = data[start:start + width * bytes_per_pixel]
            if len(row_data) < width * bytes_per_pixel:
                raise ValueError("truncated BMP row")
            pixels = []
            for column in range(width):
                offset = column * bytes_per_pixel
                blue = row_data[offset]
                green = row_data[offset + 1]
                red = row_data[offset + 2]
                pixels.append((red, green, blue))
            rgb_rows.append(pixels)

    return {
        "path": path,
        "width": width,
        "height": height,
        "bpp": bpp,
        "pixels": rgb_rows,
    }


def luminance(pixel):
    red, green, blue = pixel
    return 0.2126 * red + 0.7152 * green + 0.0722 * blue


def summarize_frame(frame, black_threshold):
    total_luma = 0.0
    nonblack = 0
    colors = set()
    for row in frame["pixels"]:
        for pixel in row:
            luma = luminance(pixel)
            total_luma += luma
            if luma > black_threshold:
                nonblack += 1
            colors.add(pixel)
    pixel_count = frame["width"] * frame["height"]
    mean_luminance = total_luma / pixel_count if pixel_count else 0.0
    return {
        "path": frame["path"],
        "width": frame["width"],
        "height": frame["height"],
        "bpp": frame["bpp"],
        "mean_luminance": mean_luminance,
        "nonblack_pixels": nonblack,
        "unique_colors": len(colors),
    }


def frame_difference(left, right):
    if left["width"] != right["width"] or left["height"] != right["height"]:
        return math.inf
    total = 0.0
    count = 0
    for left_row, right_row in zip(left["pixels"], right["pixels"]):
        for left_pixel, right_pixel in zip(left_row, right_row):
            total += abs(luminance(left_pixel) - luminance(right_pixel))
            count += 1
    return total / count if count else 0.0


def format_summary(summary):
    return (
        "frame={path} width={width} height={height} bpp={bpp} "
        "mean_luminance={mean_luminance:.6f} nonblack_pixels={nonblack_pixels} "
        "unique_colors={unique_colors}"
    ).format(**summary)


def flatten_pixels(frame):
    return [pixel for row in frame["pixels"] for pixel in row]


def scaled_pixels(frame, target_width):
    scale = max(1, frame["width"] // max(1, target_width))
    out_width = max(1, frame["width"] // scale)
    out_height = max(1, frame["height"] // scale)
    rows = []
    for y in range(out_height):
        source_y = min(frame["height"] - 1, y * scale)
        row = []
        for x in range(out_width):
            source_x = min(frame["width"] - 1, x * scale)
            row.append(frame["pixels"][source_y][source_x])
        rows.append(row)
    return out_width, out_height, rows


def write_ppm_montage(frames, output_path, columns=4, thumb_width=160):
    if not frames:
        return
    thumbnails = [scaled_pixels(frame, thumb_width) for frame in frames]
    thumb_w = max(item[0] for item in thumbnails)
    thumb_h = max(item[1] for item in thumbnails)
    columns = max(1, columns)
    rows = (len(thumbnails) + columns - 1) // columns
    sheet_w = thumb_w * columns
    sheet_h = thumb_h * rows
    black = (0, 0, 0)
    sheet = [[black for _ in range(sheet_w)] for _ in range(sheet_h)]

    for index, (_, _, pixels) in enumerate(thumbnails):
        grid_x = (index % columns) * thumb_w
        grid_y = (index // columns) * thumb_h
        for y, row in enumerate(pixels):
            if grid_y + y >= sheet_h:
                break
            for x, pixel in enumerate(row):
                if grid_x + x >= sheet_w:
                    break
                sheet[grid_y + y][grid_x + x] = pixel

    os.makedirs(os.path.dirname(output_path) or ".", exist_ok=True)
    with open(output_path, "wb") as handle:
        handle.write(f"P6\n{sheet_w} {sheet_h}\n255\n".encode("ascii"))
        for row in sheet:
            for red, green, blue in row:
                handle.write(bytes((red, green, blue)))


def main(argv):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("frames", nargs="+", help="BMP frame paths to inspect")
    parser.add_argument("--min-mean", type=float, default=None)
    parser.add_argument("--min-nonblack", type=int, default=None)
    parser.add_argument("--min-colors", type=int, default=None)
    parser.add_argument("--black-threshold", type=float, default=2.0)
    parser.add_argument("--min-diff", type=float, default=None)
    parser.add_argument("--min-changed-pairs", type=int, default=None)
    parser.add_argument("--montage-out", default=None)
    parser.add_argument("--quiet", action="store_true")
    args = parser.parse_args(argv)

    frames = [read_bmp(path) for path in args.frames if os.path.isfile(path)]
    if not frames:
        raise SystemExit("no readable frame paths were supplied")

    summaries = [summarize_frame(frame, args.black_threshold) for frame in frames]
    failures = []
    for summary in summaries:
        if args.min_mean is not None and summary["mean_luminance"] < args.min_mean:
            failures.append(f"{summary['path']}: mean_luminance below {args.min_mean}")
        if args.min_nonblack is not None and summary["nonblack_pixels"] < args.min_nonblack:
            failures.append(f"{summary['path']}: nonblack_pixels below {args.min_nonblack}")
        if args.min_colors is not None and summary["unique_colors"] < args.min_colors:
            failures.append(f"{summary['path']}: unique_colors below {args.min_colors}")

    changed_pairs = 0
    max_diff = 0.0
    if len(frames) > 1:
        for left, right in zip(frames, frames[1:]):
            diff = frame_difference(left, right)
            if diff > max_diff:
                max_diff = diff
            if args.min_diff is not None and diff >= args.min_diff:
                changed_pairs += 1
    if args.min_changed_pairs is not None and changed_pairs < args.min_changed_pairs:
        failures.append(
            f"changed_pairs below {args.min_changed_pairs}: changed_pairs={changed_pairs} max_pair_mean_abs_diff={max_diff:.6f}"
        )

    if args.montage_out:
        write_ppm_montage(frames, args.montage_out)

    if not args.quiet:
        for summary in summaries:
            print(format_summary(summary))
        print(
            "progression frames={} changed_pairs={} max_pair_mean_abs_diff={:.6f}".format(
                len(frames), changed_pairs, max_diff
            )
        )

    if failures:
        for failure in failures:
            print(f"visual_check_failure={failure}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
