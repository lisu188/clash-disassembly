# Spent-turn low32 arithmetic regression

This asset-free fixture compiles the actual implementations selected by the
source manifest for `UnitStack_SetSpentTurnFlag` and
`UnitStack_ClearSpentTurnFlag`. It checks complete 800-byte images and the full
native pointer result, including addresses above `INT_MAX`.

The original routines at `0x00412A30` and `0x00412A60` are each 38 bytes with no
calls. They add 6 to EAX, visit at most ten packed 31-byte slots until the signed
word sentinel -1, set or clear flag bit 2 at slot offset 13, and increment EAX by
31 after each processed slot. The return is therefore
`(incoming low32 + 6 + 31 * processed_slots) mod 2^32`. A native result must
zero-extend that value, including when bit 31 is set.

`original_measurement.json` records the original executable/instruction hashes
and input/output stream hashes measured by executing those unchanged original
instructions at their original addresses in a freestanding 32-bit harness.
The original executable and instruction bytes are not included. `contract.py`
reconstructs the exact measured corpus and output stream without retail assets.
Changing its stream hashes requires fresh original instruction measurements.

The 72,688 cases exercise both routines, every prefix length, all 256 flag bytes,
all 16 alignments, signed type extremes, stopping sentinels, non-slot bytes,
return cursors crossing `INT_MAX`, and mapped starts above `INT_MAX`.
GCC 13 and Clang 18 each run O0/O2 with signed/unsigned char and fatal UBSan.
The comparison retains all eight bytes of the native pointer so sign extension
cannot be hidden by truncating the test result.

The frozen reference functions document the former defects and are never used
as an expected-output oracle: they sign-extend negative input addresses and
perform overflowing signed addition on some return cursors. This behavioral
repair changes only the entry and return casts to uint32 arithmetic. It does not
migrate either function to a class or change the slot scan/stores.

The mapped corpus does not claim a readable allocation crossing the 4GiB wrap
boundary. There is no campaign, visual, or live-game acceptance claim here.
