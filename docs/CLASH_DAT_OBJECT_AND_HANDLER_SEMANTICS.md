# CLASH.DAT object constraints and direct handler slots

This note records the next verified layer of the retail `CLASH.DAT` CLIPS 6.00
BSAVE recovery.

## Object join comparisons

`OBJ_JN_CMP1` contains two global CLIPS slot-name ids plus two compiled pattern
numbers and pass/fail polarity. Historical CLIPS 6.x generator code confirms that
this primitive is emitted for comparisons between simple single-field object
slots. `tools/clash_dat_object_constraints.py` resolves those slot ids through
the recovered `defclass` slot-name table and emits ordinary `eq`/`neq` tests only
when both object pattern references resolve uniquely.

## Object pattern constants

`OBJ_PN_CONSTANT` does not store a slot id in the primitive payload. The slot is
implicit in the object pattern node whose `networkTest` points at the expression.
The recovery therefore walks the object alpha `lastLevel` chain and associates
each alpha test with its pattern-node `slot_name_id` before translation.

The current translator emits a source test only for the conservative simple-slot
case (`general=0`, non-multifield node, zero offset from the beginning). General
or multifield cases remain explicit unresolved evidence.

## HANDLER_GET / HANDLER_PUT

The recovered Win95 runtime gives the exact six-byte payload used by both direct
message-handler slot primitives:

```text
uint16 class_id
uint32 slot_name_id
```

`MessageHandler_GetSelfSlotDirect` and `MessageHandler_PutSelfSlotDirect` both
resolve the class id through the bloaded class-id table and use the following
32-bit value as the class slot-name-map id. `tools/clash_dat_handler_slots.py`
therefore decodes all type-58/type-59 expressions to recovered class and slot
names.

At source level these primitives correspond to CLIPS static active-instance slot
syntax:

```clips
?self:<slot-name>
(bind ?self:<slot-name> <value>*)
```

The decoder records this source target but does not yet synthesize all 69
`defmessage-handler` constructs; handler construct reconstruction is the next
natural integration step.

## Validation

The contracts require the retail image to retain 47 `HANDLER_GET` and 23
`HANDLER_PUT` references, each with a six-byte payload. The handler report also
requires every reference to resolve to a recovered class and non-system slot.

The unified recovered CLP contract additionally requires at least one named
`OBJ_JN_CMP1` translation and at least one context-backed `OBJ_PN_CONSTANT`
translation, while preserving every untranslatable primitive as an evidence
comment.
