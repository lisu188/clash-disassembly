import hashlib
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ASM = (ROOT / 'clash95.asm').read_text(encoding='latin-1')
SOURCE = ROOT / 'src/buildings/00425540_00426FC0_buildings_006.cpp'
TIME_NORM_SHA256 = '7e0120ef65c18c2ef2117f1f8dc308d1a5073a0d9f3d2a5325f441d2fa037e9d'


def procedure(name):
    m = re.search(rf'(?ms)^\s*{re.escape(name)}\s+proc\b.*?^\s*{re.escape(name)}\s+endp\b', ASM)
    if not m:
        raise AssertionError(name)
    return m.group(0)


def normalized(proc):
    out = []
    for line in proc.splitlines()[1:-1]:
        code = line.split(';', 1)[0].strip()
        if code and not code.endswith(':'):
            out.append(re.sub(r'\s+', ' ', code))
    return out


def function(text, name):
    m = re.search(rf'(?m)^.*\b{re.escape(name)}\s*\([^;\n]*\)\s*$', text)
    if not m:
        raise AssertionError(name)
    brace = text.find('{', m.end())
    depth = 0
    for i in range(brace, len(text)):
        if text[i] == '{':
            depth += 1
        elif text[i] == '}':
            depth -= 1
            if depth == 0:
                return text[m.start():i+1]
    raise AssertionError(name)


class RoadModeTimingRecoveryTests(unittest.TestCase):
    def test_original_time_now_is_pinned_and_has_no_input_arguments(self):
        proc = procedure('Time_Now')
        norm = normalized(proc)
        self.assertEqual(hashlib.sha256('\n'.join(norm).encode()).hexdigest(), TIME_NORM_SHA256)
        self.assertNotRegex(proc, r'\barg_[0-9A-Fa-f]+\b')
        self.assertIn('push    ecx', proc)
        self.assertIn('push    edx', proc)
        self.assertIn('pop     edx', proc)
        self.assertIn('pop     ecx', proc)
        self.assertIn('call    cs:QueryPerformanceCounter', proc)
        self.assertIn('call    __I8D', proc)

    def test_original_road_loop_has_two_bare_time_now_calls(self):
        proc = procedure('sub_425540')
        self.assertEqual(proc.count('call    Time_Now'), 2)
        self.assertRegex(proc, r'call\s+sub_40ADF0\s*\n\s*call\s+Time_Now\s*\n\s*mov\s+edx, ds:dword_527C28\s*\n\s*sub\s+eax, 0Ah')
        self.assertRegex(proc, r'cmp\s+eax, edx\s*\n\s*jbe\s+loc_4256B7\s*\n\s*call\s+Time_Now\s*\n\s*imul\s+edx, ds:dword_511B58, 2D5h')

    def test_recovered_source_uses_explicit_ignored_inputs_only(self):
        body = function(SOURCE.read_text(), 'Builder_StartRoadBuildMode')
        self.assertEqual(body.count('Time_Now(0, 0)'), 2)
        self.assertNotIn('Time_Now(v8, v7)', body)
        self.assertNotIn('Time_Now(v9, g_RoadBuildModeLastAnimationTick)', body)
        self.assertNotRegex(body, r'\bint v[789];')
        self.assertNotIn("variable 'v7' is possibly undefined", SOURCE.read_text())
        self.assertNotIn("variable 'v8' is possibly undefined", SOURCE.read_text())
        self.assertNotIn("variable 'v9' is possibly undefined", SOURCE.read_text())

    def test_timing_order_and_threshold_are_unchanged(self):
        body = function(SOURCE.read_text(), 'Builder_StartRoadBuildMode')
        first = body.index('Time_Now(0, 0) - ROAD_BUILD_MARKER_ANIMATION_INTERVAL_TICKS')
        store = body.index('g_RoadBuildModeLastAnimationTick = Time_Now(0, 0);')
        frame = body.index('g_RoadBuildModeAnimationFrameIndex = v4;')
        self.assertLess(first, store)
        self.assertLess(store, frame)
        self.assertIn('> (unsigned int)g_RoadBuildModeLastAnimationTick', body)


if __name__ == '__main__':
    unittest.main()
