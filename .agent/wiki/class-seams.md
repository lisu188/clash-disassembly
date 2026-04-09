# Class Seams

- No new C++ class-seam recovery landed this batch.
- Existing conservative executable-regeneration seams remain:
  - `DLXSpriteSet`
  - `CAviDecompressor`
  - `CSyncObject`
- The world-map top-menu path still touches the raw `DLXSpriteSet` seam through `WorldMap_LoadResources` / `WorldMapTopMenu_LoadSpriteSet`, but the live frontier remains in recovered C save/load and boot-path helpers rather than the C++ seam library.
