#!/usr/bin/env python3
"""Evidence artifact: T1 void-prototype tranche object-diff classification.

The T1 tranche (tools/gen_void_prototypes.py) rewrote 553 zero-argument
recovered functions from unprototyped `int Foo();` / old-style `int Foo()` to
`int Foo(void);` / `int Foo(void)`. Unlike prior identity-preserving batches,
this is NOT objdump-identical at -O0 on x86-64: the SysV ABI requires callers
of UNPROTOTYPED (potentially variadic) functions to zero %al before the call
(vector-register count protocol). Once a callee has a (void) prototype, GCC
stops emitting that `mov $0x0,%eax` at its call sites.

This script re-proves the accepted-exception claim: diffing the normalized
per-TU disassembly snapshots before/after the tranche, EVERY difference is a
removed `mov $0x0,%eax` immediately preceding a call whose relocation target is
one of the 553 rewritten functions, and NOTHING is added. Verdict at tranche
time: removed=1312, added=0, unexplained=0 across all 138 TUs.

Why the removal is behavior-neutral: none of the 553 callees is variadic and
none reads %al; the zeroing was the ABI's conservative default for unknown
prototypes. The original Win95 binary is 32-bit x86 (cdecl/fastcall) where no
such protocol exists, so the instruction was purely a 64-bit-host artifact and
carries no recovered behavior.

Usage (re-verification):
  bash tools/obj_diff_gate.sh --snapshot before.asm   # at the parent commit
  ... apply tranche ...
  bash tools/obj_diff_gate.sh --snapshot after.asm
  python3 docs/archive/warning_tranches/t1_obj_diff_classification.py \
      before.asm after.asm docs/archive/warning_tranches/t1_void_prototypes_report.json
"""
import difflib
import json
import re
import sys


def normalize(path):
    out = []
    for ln in open(path, encoding="latin-1"):
        # strip bare jump/call target offsets ("je 613 <Sym>" -> "je <Sym>")
        out.append(re.sub(r"\b[0-9a-f]+\s+(<)", r"\1", ln.rstrip("\n")))
    return out


def main(before_p, after_p, report_p):
    t1 = {r["name"] for r in json.load(open(report_p))["rewritten"]}
    b, a = normalize(before_p), normalize(after_p)
    sm = difflib.SequenceMatcher(None, b, a, autojunk=False)
    removed, added = [], []
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            continue
        removed += [(i, b[i]) for i in range(i1, i2)]
        added += [(j, a[j]) for j in range(j1, j2)]

    # In .o disassembly the rendered <sym> for an unresolved call is the
    # CONTAINING function; the true callee is the following relocation line.
    reloc = re.compile(r"R_X86_64_(?:PLT32|PC32)\s+([A-Za-z_][A-Za-z0-9_]*)-0x4")
    unexplained = []
    for idx, ln in removed:
        if ln.strip() != "mov    $0x0,%eax":
            unexplained.append((idx, ln))
            continue
        tgt = None
        for k in range(idx + 1, min(idx + 5, len(b))):
            if "call" in b[k]:
                m = reloc.search(b[k + 1]) if k + 1 < len(b) else None
                if not m:
                    m = re.search(r"call.*<([A-Za-z_][A-Za-z0-9_]*)>", b[k])
                tgt = m.group(1) if m else None
                break
        if tgt is None or tgt not in t1:
            unexplained.append((idx, f"{ln.strip()} [callee: {tgt}]"))

    print(f"removed={len(removed)} added={len(added)} "
          f"unexplained={len(unexplained)}")
    ok = not added and not unexplained
    print("VERDICT:", "PASS - all diffs are dead varargs-protocol %eax zeroing"
          if ok else "FAIL - unexplained differences present")
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main(*sys.argv[1:4]))
