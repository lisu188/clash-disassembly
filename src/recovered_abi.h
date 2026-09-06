/* Canonical recovered ABI declarations; validated by the split-source audit. */
#ifndef CLASH95_RECOVERED_ABI_H
#define CLASH95_RECOVERED_ABI_H

#include "platform/platform_sdl.h"
#include "compatibility/defs.h"
#include "instrumentation/runtime_mission_trace.h"
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
#define CLASH95_STATIC_ASSERT(condition, message) static_assert(condition, message)
#else
#define CLASH95_STATIC_ASSERT(condition, message) _Static_assert(condition, message)
#endif

/* Signed Win95 words in byte-aligned packed records. */
typedef __int16 clash95_unaligned_int16 __attribute__((aligned(1)));
CLASH95_STATIC_ASSERT(sizeof(clash95_unaligned_int16) == 2, "Win95 word width");
CLASH95_STATIC_ASSERT(__alignof__(clash95_unaligned_int16) == 1, "packed word alignment");

/* Win95 dwords in byte-aligned packed records, including army fact handles. */
typedef _DWORD clash95_unaligned_uint32 __attribute__((aligned(1)));
CLASH95_STATIC_ASSERT(sizeof(clash95_unaligned_uint32) == 4, "Win95 dword width");
CLASH95_STATIC_ASSERT(__alignof__(clash95_unaligned_uint32) == 1, "packed dword alignment");

/* Clang still mangles internal function names within extern "C" blocks.
 * Pin only TU-private declarations so both C++ compilers retain the C names. */
#if defined(__cplusplus) && (defined(__GNUC__) || defined(__clang__))
#define CLASH95_LOCAL_SYMBOL(name) __asm__(#name)
#else
#define CLASH95_LOCAL_SYMBOL(name)
#endif

/* Keep exact, individually audited C names for function-local data objects. */
#if defined(__cplusplus) && defined(__clang__)
#define CLASH95_LOCAL_DATA_SYMBOL(gcc_name, clang_name) __asm__(clang_name)
#elif defined(__cplusplus) && defined(__GNUC__)
#define CLASH95_LOCAL_DATA_SYMBOL(gcc_name, clang_name) __asm__(gcc_name)
#else
#define CLASH95_LOCAL_DATA_SYMBOL(gcc_name, clang_name)
#endif

#if defined(__GNUC__) || defined(__clang__)
#define CLASH95_INTERNAL __attribute__((visibility("hidden")))
#define CLASH95_UNUSED __attribute__((unused))
#else
#define CLASH95_INTERNAL
#define CLASH95_UNUSED
#endif
#ifdef CLASH95_TESTING
#define CLASH95_TEST_VISIBLE
#else
#define CLASH95_TEST_VISIBLE static CLASH95_UNUSED
#endif
#define CLASH95_LOCAL static CLASH95_UNUSED

#endif
