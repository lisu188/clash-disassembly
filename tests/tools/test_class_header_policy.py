#!/usr/bin/env python3
"""Class/binding headers cannot hide aggregate exposure or recovered coupling."""

from __future__ import annotations

import json
from pathlib import Path
import shutil
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'tools'))
import audit_header_surface as audit
import gen_subsystem_headers as generation


@unittest.skipUnless(shutil.which('g++'), 'class-header policy requires the existing GNU preprocessing dependency')
class ClassHeaderPolicyTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.write('src/recovered_types.h', '#ifndef TYPES\n#define TYPES\n#define FieldAlias shared_game_global\n#endif\n')
        self.write('src/world/WorldMap.cpp', '#include "WorldMap.hpp"\n')
        self.write('src/state/storage.cpp', '')
        self.declarations = {'shared_state_layout': 'consumer', 'functions': {
            'LegacyCall': {'decl': 'int LegacyCall(void);'},
        }, 'globals': {'shared_game_global': {'decl': 'extern int shared_game_global;'}}}
        self.write('data/recovered_decls.json', json.dumps(self.declarations))
        self.manifest = {'schema_version': 3, 'state_owner': 'src/state/storage.cpp', 'functions': [{
            'name': 'LegacyCall', 'source': 'src/world/WorldMap.cpp',
            'implementation': {'kind': 'method', 'qualified_name': 'clash95::WorldMap::LegacyCall', 'header': 'src/world/WorldMap.hpp'},
        }]}
        self.write('data/recovered_sources.json', json.dumps(self.manifest))
        for module in (audit, generation):
            patch = mock.patch.object(module, 'REPO', self.root)
            patch.start()
            self.addCleanup(patch.stop)
        patch = mock.patch.object(audit, 'DECLS', self.root / 'data/recovered_decls.json')
        patch.start()
        self.addCleanup(patch.stop)

    def write(self, relative, text):
        path = self.root / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)

    def errors(self, body):
        self.write('src/world/WorldMap.hpp', body)
        return audit.class_header_policy_errors(self.manifest)

    def test_borrowing_constructor_and_member_accessor_are_allowed(self):
        errors = self.errors('''#pragma once
#include "../recovered_types.h"
namespace clash95 {
class WorldMap final {
 public:
  explicit WorldMap(int *value) noexcept : address_(value) {}
  int LegacyCall() const;
  int localValue() const noexcept { return *address_; }
 private:
  int *address_;
};
}
''')
        self.assertEqual(errors, [])

    def test_direct_forbidden_aggregate_is_rejected(self):
        for name in ('recovered_all.h', 'recovered_internal.h', 'recovered_functions.h', 'recovered_foundation.h'):
            with self.subTest(name=name):
                errors = self.errors('#include "../' + name + '"\n')
                self.assertTrue(any('forbidden aggregate' in error for error in errors))

    def test_transitive_binding_h_cannot_hide_aggregate(self):
        self.write('src/world/Bindings.h', '#include "../recovered_all.h"\n')
        errors = self.errors('#include "Bindings.h"\n')
        self.assertTrue(any('Bindings.h' in error and 'forbidden aggregate' in error for error in errors))

    def test_foreign_state_internal_and_local_headers_are_rejected(self):
        for name in ('units_state.h', 'units_shared_state.h', 'units_internal.h', '01234567_local.h', 'state_shared.h'):
            with self.subTest(name=name):
                self.write('src/world/Bindings.h', '#include "../units/./' + name + '"\n')
                self.assertTrue(self.errors('#include "Bindings.h"\n'))

    def test_foundation_is_still_traversed_for_forbidden_includes(self):
        self.write('src/recovered_types.h', '#include "recovered_all.h"\n')
        self.assertTrue(self.errors('#include "../recovered_types.h"\n'))

    def test_computed_include_fails_closed(self):
        self.assertTrue(any('computed include' in error for error in self.errors('#define H "../recovered_all.h"\n#include H\n')))

    def test_inline_global_access_is_rejected(self):
        errors = self.errors('class WorldMap { int value() const { return shared_game_global; } };\n')
        self.assertTrue(any('shared_game_global' in error for error in errors))

    def test_inline_alias_access_is_rejected_after_preprocessing(self):
        errors = self.errors('#include "../recovered_types.h"\nclass WorldMap { int value() const { return FieldAlias; } };\n')
        self.assertTrue(any('shared_game_global' in error for error in errors))

    def test_inline_function_call_is_not_masked_as_a_declaration(self):
        errors = self.errors('class WorldMap { int LegacyCall() const; int value() const { return LegacyCall(); } };\n')
        self.assertTrue(any('LegacyCall' in error for error in errors))

    def test_default_argument_function_dependency_is_retained(self):
        errors = self.errors('class WorldMap { int LegacyCall(int value = LegacyCall()); };\n')
        self.assertTrue(any('LegacyCall' in error for error in errors))

    def test_constructor_and_member_initializers_are_checked(self):
        for body in ('class WorldMap { WorldMap() : pointer_(&shared_game_global) {} int *pointer_; };',
                     'class WorldMap { int value_ = FieldAlias; };',
                     'class WorldMap { int (*callback_)() = LegacyCall; };'):
            with self.subTest(body=body):
                self.assertTrue(self.errors(body))

    def test_transitive_macros_use_actual_include_order(self):
        self.write('src/world/Bindings.h', 'inline int binding() { return HeaderAlias; }\n')
        errors = self.errors('#define HeaderAlias FieldAlias\n#include "Bindings.h"\nclass WorldMap {};\n')
        self.assertTrue(any('shared_game_global' in error for error in errors))

    def test_unused_object_and_function_macro_dependencies_are_checked(self):
        for macro in ('#define HIDDEN FieldAlias\n', '#define HIDDEN() FieldAlias\n', '#define HIDDEN(x) LegacyCall()\n'):
            with self.subTest(macro=macro):
                self.assertTrue(self.errors(macro + 'class WorldMap {};\n'))

    def test_comments_and_string_literals_are_not_dependencies(self):
        self.assertEqual(self.errors('''// shared_game_global LegacyCall()
#define LABEL "shared_game_global LegacyCall"
class WorldMap { const char *label_; const char *label() const { return label_; } };
'''), [])

    def test_pure_control_flow_cannot_hide_business_logic(self):
        for expression in ('if (value_) return value_; return other_;',
                           'for (;;) {}', 'while (value_) {}', 'do {} while (value_);',
                           'switch (value_) { default: return value_; }',
                           'goto label; label: return value_;',
                           'return value_ ? value_ : other_;'):
            with self.subTest(expression=expression):
                errors = self.errors('class WorldMap { int predicate() { ' + expression + ' } int value_, other_; };')
                self.assertTrue(any('control flow' in error for error in errors))

    def test_unknown_helper_calls_or_arithmetic_are_not_trivial_accessors(self):
        for expression in ('return helper();', 'return value_ + other_;', 'return value_ == other_;', 'value_ = 7;'):
            with self.subTest(expression=expression):
                errors = self.errors('class WorldMap { int predicate() { ' + expression + ' } int value_, other_; };')
                self.assertTrue(any('nontrivial inline' in error for error in errors))

    def test_unknown_initializer_calls_cannot_bypass_empty_constructor_rule(self):
        for body in ('class WorldMap { WorldMap() : pointer_(unknown_factory()) {} int *pointer_; };',
                     'class WorldMap { int value_ = unknown_factory(); };'):
            with self.subTest(body=body):
                self.assertTrue(any('initializers' in error for error in self.errors(body)))

    def test_missing_registered_class_header_fails(self):
        errors = audit.class_header_policy_errors(self.manifest)
        self.assertTrue(any('missing class header' in error for error in errors))

    def test_member_initializer_cannot_hide_arithmetic_or_comparisons(self):
        for expression in ('operand_ * 2', '(operand_ + 1)', 'operand_ == 2',
                           'operand_ << 1', 'operand_ | 2', '(operand_, 2)'):
            with self.subTest(expression=expression):
                errors = self.errors('class WorldMap { int operand_; int cached_ = '
                                     + expression + '; };')
                self.assertTrue(any('nontrivial header initializers' in error for error in errors))

    def test_direct_member_and_scalar_initializers_are_allowed(self):
        self.assertEqual(self.errors('class WorldMap { int operand_; int *ref_ = &operand_; '
                                     'int flag_ = -1; };'), [])

    def test_array_type_alias_is_not_runtime_initialization(self):
        self.assertEqual(self.errors('class WorldMap { using table_type = int[3]; '
                                     'table_type &table_; };'), [])

    def test_include_policy_calls_header_closure_gate(self):
        self.write('src/world/Bindings.h', '#include "../recovered_all.h"\n')
        self.write('src/world/WorldMap.hpp', '#include "Bindings.h"\n')
        self.assertTrue(any('forbidden aggregate' in error for error in audit.include_policy_errors()))

    def test_unregistered_production_hpp_is_also_audited(self):
        self.write('src/world/Other.hpp', 'inline int other() { return FieldAlias; }\n')
        errors = self.errors('class WorldMap {};\n')
        self.assertTrue(any('Other.hpp' in error and 'shared_game_global' in error for error in errors))

    def test_system_template_bodies_do_not_count_as_hidden_game_logic(self):
        errors = self.errors('#include <array>\nclass WorldMap { int LegacyCall() const; std::array<int, 2> fields_; };\n')
        self.assertEqual(errors, [])


if __name__ == '__main__':
    unittest.main()
