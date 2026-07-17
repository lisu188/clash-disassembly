#!/usr/bin/env python3
"""Minimal QMP client for the headless clash95 Win98 QEMU rig.

Talks to QEMU's QMP unix socket to drive a fully headless VM: send keystrokes
and mouse events, capture the framebuffer with screendump, and power the guest
down. No X/VNC/host window is ever opened.

Usage:
  qmp.py <sock> caps                       # negotiate capabilities (once/session)
  qmp.py <sock> key <k1> <k2> ...          # send-key (QKeyCode names or a#/ret/spc)
  qmp.py <sock> type "some text"           # type an ASCII string as keystrokes
  qmp.py <sock> shot <out.ppm>             # screendump to a PPM file
  qmp.py <sock> mouse <dx> <dy> [button]   # relative mouse move (+ optional click)
  qmp.py <sock> click [button]             # press+release at current position
  qmp.py <sock> powerdown                  # ACPI power button
  qmp.py <sock> quit                       # hard quit QEMU
  qmp.py <sock> raw '{"execute":...}'      # send a raw QMP command
"""
import json
import socket
import sys
import time

# ASCII -> QKeyCode for the `type` helper (US layout, Win98 setup only needs a subset).
SHIFT = set('~!@#$%^&*()_+{}|:"<>?ABCDEFGHIJKLMNOPQRSTUVWXYZ')
PLAIN = {
    ' ': 'spc', '\n': 'ret', '\t': 'tab', '-': 'minus', '=': 'equal',
    '[': 'bracket_left', ']': 'bracket_right', '\\': 'backslash',
    ';': 'semicolon', "'": 'apostrophe', '`': 'grave_accent', ',': 'comma',
    '.': 'dot', '/': 'slash',
}
SHIFTED = {
    '~': 'grave_accent', '!': '1', '@': '2', '#': '3', '$': '4', '%': '5',
    '^': '6', '&': '7', '*': '8', '(': '9', ')': '0', '_': 'minus',
    '+': 'equal', '{': 'bracket_left', '}': 'bracket_right', '|': 'backslash',
    ':': 'semicolon', '"': 'apostrophe', '<': 'comma', '>': 'dot', '?': 'slash',
}
ALIAS = {
    'ret': 'ret', 'enter': 'ret', 'esc': 'esc', 'spc': 'spc', 'space': 'spc',
    'tab': 'tab', 'up': 'up', 'down': 'down', 'left': 'left', 'right': 'right',
    'f8': 'f8', 'f3': 'f3', 'y': 'y', 'n': 'n', 'del': 'delete',
    'backspace': 'backspace', 'bksp': 'backspace', 'pgdn': 'pgdn', 'pgup': 'pgup',
}


class QMP:
    def __init__(self, path):
        self.s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.s.settimeout(20)
        self.s.connect(path)
        self.f = self.s.makefile('rw')
        self._read()  # greeting

    def _read(self):
        return json.loads(self.f.readline())

    def cmd(self, execute, **args):
        obj = {'execute': execute}
        if args:
            obj['arguments'] = args
        self.f.write(json.dumps(obj) + '\n')
        self.f.flush()
        while True:
            r = self._read()
            if 'event' in r and 'return' not in r and 'error' not in r:
                continue
            return r

    def caps(self):
        return self.cmd('qmp_capabilities')

    def sendkey(self, keys, hold_ms=40):
        codes = [{'type': 'qcode', 'data': k} for k in keys]
        return self.cmd('send-key', keys=codes, **{'hold-time': hold_ms})


def to_qcode(tok):
    tok = tok.lower()
    if tok in ALIAS:
        return [ALIAS[tok]]
    if len(tok) == 1:
        if tok in PLAIN:
            return [PLAIN[tok]]
        if tok.isalnum():
            return [tok]
    return [tok]  # assume already a QKeyCode


def type_string(q, text):
    for ch in text:
        if ch in SHIFTED or ch in SHIFT:
            base = SHIFTED.get(ch, ch.lower())
            q.sendkey(['shift', base])
        elif ch in PLAIN:
            q.sendkey([PLAIN[ch]])
        elif ch.isalnum():
            q.sendkey([ch.lower()])
        else:
            q.sendkey([ch])
        time.sleep(0.03)


def main():
    sock, op, rest = sys.argv[1], sys.argv[2], sys.argv[3:]
    q = QMP(sock)
    if op != 'caps':
        try:
            q.caps()
        except Exception:
            pass
    if op == 'caps':
        print(json.dumps(q.caps()))
    elif op == 'key':
        for tok in rest:
            for code in to_qcode(tok):
                pass
            q.sendkey(sum((to_qcode(t) for t in [tok]), []))
            time.sleep(0.05)
        print('ok')
    elif op == 'combo':  # all tokens as one chord
        keys = sum((to_qcode(t) for t in rest), [])
        print(json.dumps(q.sendkey(keys)))
    elif op == 'type':
        type_string(q, rest[0])
        print('ok')
    elif op == 'shot':
        print(json.dumps(q.cmd('screendump', filename=rest[0])))
    elif op == 'mouse':
        dx, dy = int(rest[0]), int(rest[1])
        q.cmd('input-send-event', events=[
            {'type': 'rel', 'data': {'axis': 'x', 'value': dx}},
            {'type': 'rel', 'data': {'axis': 'y', 'value': dy}},
        ])
        if len(rest) > 2:
            btn = rest[2]
            q.cmd('input-send-event', events=[{'type': 'btn', 'data': {'button': btn, 'down': True}}])
            time.sleep(0.05)
            q.cmd('input-send-event', events=[{'type': 'btn', 'data': {'button': btn, 'down': False}}])
        print('ok')
    elif op == 'click':
        btn = rest[0] if rest else 'left'
        q.cmd('input-send-event', events=[{'type': 'btn', 'data': {'button': btn, 'down': True}}])
        time.sleep(0.05)
        q.cmd('input-send-event', events=[{'type': 'btn', 'data': {'button': btn, 'down': False}}])
        print('ok')
    elif op == 'powerdown':
        print(json.dumps(q.cmd('system_powerdown')))
    elif op == 'quit':
        print(json.dumps(q.cmd('quit')))
    elif op == 'raw':
        print(json.dumps(q.cmd(**json.loads(rest[0]))))
    else:
        sys.exit('unknown op ' + op)


if __name__ == '__main__':
    main()
