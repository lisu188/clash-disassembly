# CLASH.DAT message-handler recovery

The retail `CLASH.DAT` defclass section contains 69 serialized CLIPS 6.00
message-handler records. They are now decoded by
`tools/clash_dat_message_handlers.py` and included in the generated
`CLASH_recovered.clp` source projection.

## Binary record

The recovered `Class_BsaveWriteSlotRecords` routine writes 28 bytes per handler.
Combined with the runtime `messageHandler` layout and
`MessageHandler_CheckArgCount`, the record is:

```text
+00 uint32 flags
    bit 0      system/implicit handler
    bits 1..2  handler type: 0 around, 1 before, 2 primary, 3 after
+04 int32  minParams
+08 int32  maxParams
+0C int32  localVarCount
+10 int32  nameSymbol
+14 int32  classIndex
+18 int32  actionsExpr
```

`minParams` includes the implicit `?self` parameter. `maxParams == -1` marks a
handler with a wildcard parameter; otherwise the recovered runtime requires the
argument count to equal `minParams`.

The original explicit parameter spellings are not stored in the BSAVE handler
record. The normalized source therefore uses stable synthetic names:

```clips
(defmessage-handler oddzial example primary (?p1 ?p2)
  ...)

(defmessage-handler oddzial variadic-example primary (?p1 $?p2)
  ...)
```

This preserves exact arity without claiming original variable names.

## Direct slot references

The previously decoded expression types `HANDLER_GET` and `HANDLER_PUT` carry a
six-byte payload:

```text
uint16 class_id
uint32 slot_name_id
```

When those expressions occur in a recovered handler body they are now rendered
as source-level direct slot operations:

```clips
?self:x
(bind ?self:x <value>)
```

All 70 direct handler-slot references in the retail image resolve through the
recovered class and global slot-name tables.

## Source reconstruction

For every handler the recovery manifest records:

- owning class;
- handler/message name;
- around/before/primary/after type;
- system flag;
- exact minimum/maximum arity;
- local variable count;
- action expression root;
- class-local dispatch order when recoverable.

The handler body is rendered by walking the serialized expression sibling chain
from `actionsExpr`. Function calls, globals, deffunction calls, direct self-slot
gets/puts, procedure parameters and known compiled primitives retain the same
expression evidence used elsewhere by the CLASH.DAT decompiler.

## Validation

`tools/check_clash_dat_message_handlers.py` locks the retail-image contract:

- exactly 69 message handlers;
- every record belongs to the class range that serializes it;
- handler type is one of the four CLIPS handler categories;
- arity is exact or wildcard;
- all action roots are valid expression indices;
- exactly 69 `defmessage-handler` constructs are rendered;
- direct slot primitives render as `?self:<slot>` rather than opaque
  `handler-get(...)` / `handler-put(...)` placeholders.

The unified `tools/check_clash_recovered_clp.py` additionally requires the full
`CLASH_recovered.clp` projection to contain the 69 handlers while preserving the
existing globals, deffunctions, classes, RETE constraints and 95 rules.

## Remaining source-level uncertainty

The BSAVE image preserves handler parameter positions, but not the original
source spellings. Local variables may also still use synthetic names where only
compiled procedure-slot indices survive. These names are presentation-layer
choices; handler class/name/type/arity and serialized action topology are treated
as binary evidence.
