#!/usr/bin/env python3
from pathlib import Path

from clash_dat_message_handlers import recover_message_handlers, render_message_handlers
from decompile_clash_dat import parse_bsave


def main() -> int:
    source = Path("CLASH.DAT")
    ir = parse_bsave(source)
    report = recover_message_handlers(source, ir)
    rendered = render_message_handlers(report, ir)

    assert report["count"] == 69
    assert report["system_count"] + report["user_count"] == 69
    assert report["system_count"] > 0
    assert report["user_count"] > 0
    assert sum(report["type_counts"].values()) == 69
    assert sum(report["class_counts"].values()) == 69
    assert set(report["type_counts"]) == {"around", "before", "primary", "after"}

    handlers = report["handlers"]
    assert len(handlers) == 69
    assert all(item["min_params"] >= 1 for item in handlers)
    assert all(item["max_params"] == -1 or item["max_params"] == item["min_params"] for item in handlers)
    assert all(item["actions_expr"] == -1 or 0 <= item["actions_expr"] < ir["expression_count"] for item in handlers)
    assert all(item["handler_type_id"] in range(4) for item in handlers)
    assert all(item["class_name"] for item in handlers)
    assert all(item["name"] for item in handlers)

    # The 28-byte record stores min/max including implicit ?self. The source
    # parameter list must therefore contain minParams-1 explicit fixed params.
    for item in handlers:
        assert item["explicit_min_params"] == item["min_params"] - 1
        if item["variadic"]:
            assert item["explicit_max_params"] is None
        else:
            assert item["explicit_max_params"] == item["explicit_min_params"]

    assert rendered.count("(defmessage-handler ") == 69
    assert ";;; handlers=69" in rendered
    assert " primary (" in rendered
    assert "?self:" in rendered
    assert "handler-get(" not in rendered
    assert "handler-put(" not in rendered

    # Every raw HANDLER_GET/HANDLER_PUT expression reachable from handler bodies
    # is rendered through the exact six-byte class/slot decoder. Other opaque
    # primitives may still remain and are intentionally not guessed here.
    direct_slot_exprs = sum(expr[0] in (58, 59) for expr in ir["expressions"])
    assert direct_slot_exprs == 70

    print("CLASH.DAT message-handler recovery contract: PASS")
    print(
        f"handlers={report['count']} system={report['system_count']} user={report['user_count']} "
        f"variadic={report['variadic_count']} types={report['type_counts']}"
    )
    print(f"classes={report['class_counts']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
