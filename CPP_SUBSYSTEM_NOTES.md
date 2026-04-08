# C++ subsystem notes

This tree is a conservative first pass at the executable-regeneration path.

## Current scope

- `clash95::cpp::DLXSpriteSet`
- `clash95::cpp::CAviDecompressor`
- `clash95::cpp::CSyncObject`

Each wrapper is a raw-handle view with explicit comments pointing back to the
map-visible C/C++ names and the decompiled evidence.

## What is intentionally not claimed

- No SDL-native behavior is asserted here.
- No ownership model is asserted beyond a nullable raw handle.
- No file-format, AVI, renderer, or sync semantics have been promoted into the
  C++ layer yet.
- The recovered C baseline remains the source of truth for actual behavior.

## Validation shape

These sources are meant to compile as ordinary C++ translation units once they
are wired into the build graph.
For now, the main value is the namespace, class boundary, and crosswalk surface.

## Next seam candidates

- `DLXSpriteSet` method parity and constructor wiring
- `CAviDecompressor` layout extraction once the runtime object boundary is
  tighter
- `CSyncObject` ownership and call-site recovery once more than `Unlock` is
  evidenced
