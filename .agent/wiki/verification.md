# Verification

- `cmake --build build --target clash95_recovered clash95_bootstrap clash95_cpp_regen -j`
  - passed
- `timeout 1s build/bin/clash95_bootstrap`
  - exit `124`
- `timeout 2s build/bin/clash95_bootstrap --authentic-startup-prelude`
  - exit `124`
- `timeout 1s build/bin/clash95_cpp_regen`
  - exit `124`
- `gdb -batch -ex 'set debuginfod enabled off' -ex 'set environment CLASH95_TRACE_MENU_PROBE 1' -ex 'set environment CLASH95_MENU_PROBE_AUTO_CLICK load' -ex 'set environment CLASH95_LOAD_MENU_PROBE_AUTO_CLICK confirm' -ex 'set environment CLASH95_LOAD_MENU_PROBE_AUTO_SLOT 0' -ex 'set environment CLASH95_LOAD_MENU_PROBE_DRAW_ROWS 1' -ex 'set environment CLASH95_LOAD_MENU_PROBE_POST_CONFIRM 1' -ex 'run --authentic-menu-probe' -ex 'bt 40' --args build/bin/clash95_bootstrap`
  - reaches `load-menu-post-confirm-load-save` and reports the first crash in `sub_4443C0 -> sprintf_`
- `env CLASH95_TRACE_MENU_PROBE=1 CLASH95_MENU_PROBE_AUTO_CLICK=load CLASH95_LOAD_MENU_PROBE_AUTO_CLICK=confirm CLASH95_LOAD_MENU_PROBE_AUTO_SLOT=0 CLASH95_LOAD_MENU_PROBE_DRAW_ROWS=1 CLASH95_LOAD_MENU_PROBE_POST_CONFIRM=1 timeout -s KILL 15s build/bin/clash95_bootstrap --authentic-menu-probe`
  - reaches `load-menu-post-confirm-after-save` and `main-after-menu-probe`, then stays alive until timeout kills it with exit `137`
