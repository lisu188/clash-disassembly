# Clash — Module Map

Reconstructed source-file layout of `clash.c` (Hex-Rays decompilation of the
Watcom C++ binary). Functions are laid out in the executable by source file in
link order, so debug/assert string references act as **module anchors**:
everything between two anchors of the same module belongs to that module.
Anchors are exact; the module of functions in a large gap between different
anchors is *inferred* and marked accordingly.

## High-level regions

| Region | Address range | Functions | Basis |
|---|---|---:|---|
| Watcom C/C++ runtime & startup | `010000`–`012C6E` | 81 | below first game anchor |
| Game logic (25 `.cpp` modules) | `012C6E`–`0654D5` | 958 | `*.cpp` assert/log anchors |
| Game engine: graphics / sound / AI glue | `0654D5`–`089860` | 695 | unanchored (no asserts) |
| CLIPS 6.x expert system (73 modules) | `089860`–`0EB580` | 2015 | CLIPS module-id anchors |
| Trailing library / math / DPMI runtime | `0EB580`–`1208EB` | 470 | unanchored |

**Total:** 4219 functions. **Named:** 468 (11.1%).

## Game modules (`0x12C6E`–`0x654D5`)

Order matches link order. Range = first..last confirmed anchor for that module.

| Module | Anchor range |
|---|---|
| `graph.cpp` | `012C6E`..`012D8D` |
| `sprite.cpp` | `01435C`..`0144C9` |
| `mouse.cpp` | `01751F`..`017733` |
| `edit.cpp` | `01A330`..`01A330` |
| `play.cpp` | `01E9DB`..`01F661` |
| `text.cpp` | `020C97`..`020EEE` |
| `menu.cpp` | `024041`..`024041` |
| `units.cpp` | `025E32`..`025E32` |
| `u_cache.cpp` | `029686`..`0298F1` |
| `u_track.cpp` | `02AFD6`..`02BAF5` |
| `u_info.cpp` | `0310DC`..`031ADD` |
| `battle_a.cpp` | `031E98`..`033AEC` |
| `building.cpp` | `0380AD`..`0385F2` |
| `castle.cpp` | `03A78E`..`03A78E` |
| `u_group.cpp` | `03BA36`..`03BAD4` |
| `trap.cpp` | `0405B3`..`0405B3` |
| `edit_b.cpp` | `041164`..`041164` |
| `b_cache.cpp` | `05AF63`..`05B2DE` |
| `temple.cpp` | `05B9DC`..`05B9DC` |
| `keep.cpp` | `05CC4F`..`05CC4F` |
| `fileio.cpp` | `05EF73`..`05EF73` |
| `port.cpp` | `0601E3`..`0601E3` |
| `savegame.cpp` | `06183E`..`06183E` |
| `windows.cpp` | `061AC4`..`063398` |
| `start.cpp` | `063990`..`0654D5` |

## CLIPS modules (`0x89860`–`0xEB580`)

The embedded [CLIPS](https://en.wikipedia.org/wiki/CLIPS) expert system (NASA rule engine) — ~48% of the binary. Module ids recovered from `PrintErrorID`/`SystemError` string arguments; each maps to a CLIPS 6.x source file (e.g. `FACTMNGR`→`factmngr.c`).

| CLIPS module | Anchor range |
|---|---|
| `ANALYSIS` | `089860`..`089980` |
| `ARGACCES` | `089DA0`..`08A620` |
| `BLOAD` | `08A6D0`..`08AE80` |
| `BSAVE` | `08BBB0`..`08BBB0` |
| `OBJECT` | `08C840`..`08C840` |
| `CLASSEXM` | `08D130`..`08D130` |
| `CLASSFUN` | `08DA70`..`08E7C0` |
| `OBJRTBLD` | `08FD00`..`08FD00` |
| `OBJECT` | `08FD70`..`08FD70` |
| `CLASSPSR` | `090730`..`090CC0` |
| `DEFAULT` | `0913F0`..`0913F0` |
| `CLSLTPSR` | `091B10`..`092010` |
| `CSTRNCHK` | `092150`..`092150` |
| `COMMLINE` | `092930`..`092930` |
| `CONSCOMP` | `092C40`..`093F30` |
| `CONSTRCT` | `094600`..`094600` |
| `CSTRCPSR` | `096BC0`..`0970A0` |
| `CSTRNBIN` | `097160`..`097160` |
| `CSTRNCHK` | `097A90`..`097A90` |
| `CSTRNCMP` | `097F10`..`097F10` |
| `CSTRNPSR` | `099610`..`09A600` |
| `SYMBOL` | `09AA50`..`09AA50` |
| `DEFAULT` | `09BC40`..`09BC40` |
| `DFFNXFUN` | `09EAF0`..`09EAF0` |
| `DFFNXPSR` | `09EF90`..`09EF90` |
| `DRIVE` | `09FB40`..`0A0540` |
| `EMATHFUN` | `0A0AB0`..`0A0B90` |
| `PRCCODE` | `0A2000`..`0A2000` |
| `EVALUATN` | `0A30B0`..`0A33E0` |
| `EXPRESSN` | `0A3B20`..`0A3B20` |
| `EXPRNPSR` | `0A4E00`..`0A57E0` |
| `FACTLHS` | `0A9A30`..`0A9A30` |
| `FACTMCH` | `0AA230`..`0AA230` |
| `FACTMNGR` | `0AA6B0`..`0AA8E0` |
| `FACTRHS` | `0AC460`..`0AC460` |
| `ANALYSIS` | `0AD760`..`0AD760` |
| `GENRCCOM` | `0AFC30`..`0AFC30` |
| `PRNTUTIL` | `0AFE20`..`0AFE20` |
| `GENRCCOM` | `0B0870`..`0B0870` |
| `GENRCEXE` | `0B0E10`..`0B18A0` |
| `GENRCFUN` | `0B1CE0`..`0B2260` |
| `GENRCPSR` | `0B2490`..`0B3340` |
| `PRCCODE` | `0B3670`..`0B3670` |
| `GENRCPSR` | `0B3700`..`0B3770` |
| `GLOBLPSR` | `0B5870`..`0B5870` |
| `INCRRSET` | `0B6220`..`0B6220` |
| `INHERPSR` | `0B6320`..`0B6610` |
| `INSCOM` | `0B77A0`..`0B77A0` |
| `INSFILE` | `0B9340`..`0B98A0` |
| `INSFUN` | `0B9FA0`..`0BA700` |
| `INSMNGR` | `0BAD10`..`0BBC80` |
| `INSMODDP` | `0BC780`..`0BC950` |
| `INSMULT` | `0BD4B0`..`0BD4B0` |
| `INSMNGR` | `0BDE00`..`0BDE00` |
| `INSQYPSR` | `0BF870`..`0BFBE0` |
| `IOFUN` | `0C05C0`..`0C1230` |
| `MISCFUN` | `0C3200`..`0C3200` |
| `MODULDEF` | `0C50C0`..`0C50C0` |
| `MODULPSR` | `0C5CD0`..`0C5CD0` |
| `MSGCOM` | `0C67C0`..`0C69A0` |
| `MSGFUN` | `0C73F0`..`0C75F0` |
| `MSGPSR` | `0C7A80`..`0C7A80` |
| `MSGFUN` | `0C7EF0`..`0C8330` |
| `MSGPASS` | `0C8900`..`0C9880` |
| `MSGPSR` | `0C9920`..`0CA220` |
| `MULTIFUN` | `0CBDE0`..`0CC770` |
| `OBJBIN` | `0CD820`..`0CD820` |
| `OBJRTBLD` | `0D0650`..`0D1C60` |
| `OBJRTMCH` | `0D5680`..`0D5680` |
| `PATTERN` | `0D5890`..`0D5910` |
| `RULEPSR` | `0D6100`..`0D6100` |
| `PATTERN` | `0D6280`..`0D6280` |
| `PRCCODE` | `0D6790`..`0D76E0` |
| `PRCDRPSR` | `0D85E0`..`0D8FD0` |
| `PRNTUTIL` | `0DA620`..`0DA8E0` |
| `REORDER` | `0DB670`..`0DB790` |
| `RETRACT` | `0DC540`..`0DC540` |
| `ROUTER` | `0DD270`..`0DD270` |
| `BUILD` | `0DE3B0`..`0DE3B0` |
| `RULECSTR` | `0DF9E0`..`0E01D0` |
| `RULELHS` | `0E0C40`..`0E1330` |
| `RULEPSR` | `0E1CB0`..`0E1CB0` |
| `SCANNER` | `0E25D0`..`0E25D0` |
| `STRNGFUN` | `0E3610`..`0E3610` |
| `ROUTER` | `0E39F0`..`0E3B40` |
| `SYMBOL` | `0E5680`..`0E60A0` |
| `TEXTPRO` | `0E7E50`..`0E7E50` |
| `TMPLTFUN` | `0EA070`..`0EA070` |
| `TMPLTRHS` | `0EB2E0`..`0EB2E0` |
| `TMPLTDEF` | `0EB400`..`0EB470` |
| `TMPLTFUN` | `0EB4D0`..`0EB4D0` |
| `CSTRNCHK` | `0EB580`..`0EB580` |
