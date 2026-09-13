"""Shared stimulus/wire contract; expected output is measured from original code."""
import struct

CALLS = {name: i + 1 for i, name in enumerate((
    "animation", "has_builder", "init_draw", "viewport", "pump", "frame",
    "select_stack", "poll", "flipping", "road", "dig", "trap", "min_ap",
    "cargo", "building_new", "minimap", "sound", "button_sound", "info",
    "begin", "sync", "status", "refresh"))}
STATE_FIELDS = ["arena", "selected", "action", "primary", "device", "language"] + [
    f"arena{arena}_stack{stack}_{axis}" for arena in range(2)
    for stack in range(4) for axis in ("row", "column")]
STATE = {name: i for i, name in enumerate(STATE_FIELDS)}
ARG_WORDS = 8
STATE_WORDS = len(STATE_FIELDS)
HEADER_WORDS = 9
EVENT_WORDS = 1 + ARG_WORDS + STATE_WORDS
FINAL_WORDS = 1 + STATE_WORDS + 3
ARENA_BYTES = 150200
RENDER_BYTES = 1144
MASK = 0xffffffff

# Argument order, with remaining words zero. Pointer normalization never rewrites
# unexpected addresses to expected identities. Trap's discarded ECX is excluded.
ARGUMENTS = {
    "animation": ["widget raw", "delay"], "has_builder": ["selected raw"],
    "init_draw": ["table identity: builder=1/main=2"], "viewport": ["present"],
    "pump": ["render identity=1", "carried frame DWORD", "BL", "EDX=0"],
    "frame": ["carried frame DWORD"], "select_stack": [],
    "poll": ["builder identity=1", "context"], "flipping": ["render identity=1"],
    "road": ["context", "float low", "float high"],
    "dig": ["selected", "action", "context", "signed render low byte", "zero", "float low", "float high"],
    "trap": ["building type", "action low byte", "float low", "float high"],
    "min_ap": ["arena identity 0/1", "stack slot 0..3"],
    "cargo": ["arena identity 0/1", "stack slot 0..3"],
    "building_new": ["type", "selected", "float low", "float high", "template identity 1..3", "force"],
    "minimap": ["signed row", "signed column"], "sound": ["string identity 1..3", "volume"],
    "button_sound": ["string identity: unselected=1/no-builder=2"],
    "info": ["message identity 1..3", "style", "delay", "context", "local-copy-end identity=4", "global-message-end identity=5"],
    "begin": ["render identity=1", "zero"], "sync": ["context"],
    "status": ["context"], "refresh": ["context"],
}

def event(name, result=0, **changes):
    return {"id": CALLS[name], "result": result & MASK,
            "changes": [[STATE[key], value & MASK] for key, value in changes.items()]}

def initial_state():
    values = [0, 1, 0x1234, 0x12345678, 0x76543210, 0]
    values += [value & MASK for arena in range(2) for slot in range(4)
               for value in (-300 + 101*arena + 3*slot, 270 - 71*arena - 5*slot)]
    return values

def case(name, events, *, guard=0, main_guard=0, selected=1, arena=0,
         language=0, delay=0x89abcdef, frame=0x87654321, context=0x92345678,
         floating=1.25, defined_before=True, before_expected_match=True, category="caller", **states):
    state = initial_state()
    for key, value in dict(selected=selected, arena=arena, language=language, **states).items():
        state[STATE[key]] = value & MASK
    low, high = struct.unpack("<II", struct.pack("<d", floating))
    return {"name": name, "category": category, "defined_before": defined_before,
            "before_expected_match": before_expected_match,
            "header": [guard & MASK, main_guard & MASK, 0x12345000, delay & MASK,
                       frame & MASK, context & MASK, low, high, len(events)],
            "state": state, "events": events}

def accepted():
    return [event("animation"), event("has_builder", 1), event("init_draw"), event("viewport")]

def iteration(poll_result=1, action=0):
    result = [event("pump"), event("frame"), event("select_stack"), event("poll", poll_result, action=action)]
    if not poll_result:
        result.append(event("flipping"))
    return result

def cleanup(result=0xfedcba98):
    return [event("init_draw"), event("sync"), event("viewport"), event("status"), event("refresh", result)]

def cases():
    result = []
    for guard in (0, 1, -7):
        for raw in (0, 0xffffffff, 0x87654321):
            result.append(case(f"unselected-g{guard}-r{raw:08x}", [event("button_sound"), event("begin", raw)],
                               guard=guard, main_guard=guard, selected=-1, category="rejected"))
        for language in range(3):
            result.append(case(f"no-builder-g{guard}-lang{language}",
                               [event("animation", selected=2), event("has_builder"),
                                event("button_sound"), event("info", 0xdeadbeef)],
                               guard=guard, main_guard=guard, language=language,
                               delay=(0, 0x80000000, 0xffffffff)[language],
                               defined_before=False, category="recovered-delay"))
        result.append(case(f"friendly-exit-g{guard}", accepted()+[
            event("pump"),event("frame"),event("select_stack",0x80000000)]+cleanup(),
            guard=guard,main_guard=guard,category="guard"))
        result.append(case(f"empty-poll-flipping-exit-g{guard}", accepted()+[
            event("pump"),event("frame"),event("select_stack"),event("poll"),event("flipping",-1)]+cleanup(),
            guard=guard,main_guard=guard,category="poll"))
    for action in (0, 1, 2, 6, 0x80000000, 0xfffffffe):
        for poll in (0, 0x80000000):
            calls = accepted()+iteration(poll, action)
            if action < 3:
                calls.append(event(("road","dig","trap")[action]))
            calls += [event("flipping")]+cleanup()
            result.append(case(f"dispatch-{action:08x}-poll{poll:08x}", calls,
                               floating=(-0.0 if poll else 19.75), defined_before=action != 2,
                               category="dispatch"))
    result.append(case("sentinel-skips-post-flip", accepted()+iteration(1,-1)+[
        event("pump"),event("frame"),event("select_stack",1)]+cleanup(), category="continuation"))
    for action in range(6):
        calls=accepted()+iteration(1,action)
        if action<3:
            calls.append(event(("road","dig","trap")[action]))
        else:
            if action==3:calls.append(event("min_ap",1))
            if action==4:calls.append(event("cargo",0))
            calls.append(event("building_new",0))
        calls += [event("flipping",1,action=0x12345678),event("pump"),event("frame"),event("select_stack",1)]+cleanup()
        result.append(case(f"action-{action}-flip-continues",calls,defined_before=action!=2,category="continuation"))
    for action, predicate, pred_result in ((3,"min_ap",0),(4,"cargo",0xffffffff)):
        result.append(case(f"action-{action}-predicate-reject",accepted()+iteration(1,action)+[
            event(predicate,pred_result),event("flipping")]+cleanup(),category="construction"))
    for action in (3,4,5):
        for construct in (0,1,2,0xffffffff):
            calls=accepted()+iteration(1,action)
            if action==3:calls.append(event("min_ap",0x80000000,selected=2,arena=1))
            if action==4:calls.append(event("cargo",0,selected=2,arena=1))
            calls.append(event("building_new",construct,selected=3,arena=0,
                               arena0_stack3_row=0x8000,arena0_stack3_column=0x7fff))
            if construct==1:
                if action==3:calls.append(event("minimap"))
                calls.append(event("sound"))
            calls += [event("flipping")]+cleanup()
            result.append(case(f"construction-{action}-return{construct:08x}",calls,
                               before_expected_match=construct in (0,1),
                               category="construction" if construct in (0,1) else "noncanonical-bool-boundary"))
    for action in (3,4):
        calls=accepted()+iteration(1,action)
        calls.append(event("min_ap" if action==3 else "cargo",1 if action==3 else 0,
                           selected=0x80000002,arena=3))
        calls.append(event("building_new",1,selected=0x80000003,arena=2,
                           arena0_stack3_row=0xffff,arena0_stack3_column=0x8000))
        if action==3:calls.append(event("minimap"))
        calls += [event("sound"),event("flipping")]+cleanup()
        result.append(case(f"wrapped-address-action-{action}",calls,selected=0x80000001,arena=2,
                           defined_before=False,category="modulo-address"))
    for mutation in ("action-callback", "flipping"):
        calls=accepted()+iteration(1,0)+[event("road",**({"action":-1} if mutation=="action-callback" else {})),
                                      event("flipping",0,**({"action":-1} if mutation=="flipping" else {})),
                                      event("pump"),event("frame"),event("select_stack",1)]+cleanup()
        result.append(case(f"fresh-action-{mutation}",calls,category="fresh-state"))
    calls=accepted()+[event("pump"),event("frame"),event("select_stack",1,primary=0xf1234567)]+[
        event("init_draw",primary=0x12340000,device=0xa7654321),event("sync",selected=2),
        event("viewport",action=0x98765432),event("status",language=2),event("refresh",0x87654321)]
    result.append(case("cleanup-fresh-state-raw-return",calls,category="cleanup"))
    assert len({item["name"] for item in result})==len(result)
    return result

def pack_inputs(records):
    words=[len(records)]
    for record in records:
        assert len(record["header"])==HEADER_WORDS and len(record["state"])==STATE_WORDS
        assert record["header"][8]==len(record["events"])
        words.extend(record["header"]+record["state"])
        for item in record["events"]:
            words.extend([item["id"],item["result"],len(item["changes"])])
            for field,value in item["changes"]:words.extend([field,value])
    return struct.pack("<"+"I"*len(words),*(word&MASK for word in words))

def decode_output(payload, records):
    offset=0
    traces=[]
    for record in records:
        size=4*(len(record["events"])*EVENT_WORDS+FINAL_WORDS)
        trace=payload[offset:offset+size]
        if len(trace)!=size:raise ValueError(f"short output for {record['name']}")
        traces.append(trace)
        offset+=size
    if offset!=len(payload):raise ValueError("unexpected trailing output")
    return traces
