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
