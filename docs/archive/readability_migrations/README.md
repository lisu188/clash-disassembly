# Superseded readability specifications

`dlx_cached_entry_signed_pr128.json` preserves the exact Git blob from
`18b6ace` / PR 128 (also present in integration parent `55872f9`). Its SHA-256 is
`737daa7e4c4a7549560a8a845bd653bb9d9959689726f9c51b6f42b0ced4efe4`.

This concurrent specification converted serialized size to signed `int` before
subtracting the header length, introducing signed overflow for DWORD values
`0x80000000..0x80000009`. It is retained as historical evidence, outside the
active migration directory, and must not be replayed as the accepted body.

The independently validated migration from the pre-view body remains in
[the active v1 plan](../../../data/readability_migrations/dlx_cached_entry_v1.json).
[The unsigned v2 plan](../../../data/readability_migrations/dlx_cached_entry_unsigned_v2.json)
also accepts PR 128's body hash and converges to that same reviewed unsigned
body. Both Git histories are retained. The frozen original canonical fixture
and signed-overflow negative control document why the unsigned subtraction wins
the conflict. See [the recovery record](../../DLX_CACHED_ENTRY_RECOVERY.md).
