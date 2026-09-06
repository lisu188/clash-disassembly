#ifndef CLASH95_DEFS_H
#define CLASH95_DEFS_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __cdecl
#define __cdecl
#endif

#ifndef __stdcall
#define __stdcall
#endif

#ifndef __fastcall
#define __fastcall
#endif

#ifndef __thiscall
#define __thiscall
#endif

#ifndef __noreturn
#define __noreturn __attribute__((noreturn))
#endif

#ifndef __hidden
#define __hidden
#endif

#ifndef __return_ptr
#define __return_ptr
#endif

#ifndef __struct_ptr
#define __struct_ptr
#endif

#ifndef __array_ptr
#define __array_ptr
#endif

#ifndef __cppobj
#define __cppobj
#endif

#ifndef __pure
#define __pure
#endif

#ifndef BYREF
#define BYREF
#endif

#ifndef __int8
#define __int8 char
#endif

#ifndef __int16
#define __int16 short
#endif

#ifndef __int32
#define __int32 int
#endif

#ifndef __int64
#define __int64 long long
#endif

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef struct CSyncObject {
  int unused;
} CSyncObject;
typedef struct WCIsvListBase {
  int unused;
} WCIsvListBase;
typedef struct bad_exception {
  int unused;
} bad_exception;
typedef struct _EXCEPTION_RECORD EXCEPTION_RECORD;
typedef struct _EXCEPTION_POINTERS _EXCEPTION_POINTERS;

typedef unsigned char _UNKNOWN;
typedef uint8_t _BYTE;
typedef uint16_t _WORD;
typedef uint32_t _DWORD;
typedef uint64_t _QWORD;
typedef uint8_t _BOOL1;
typedef int16_t _BOOL2;
typedef int32_t _BOOL4;

typedef struct __lock {
  int unused;
} __lock;

typedef int errno_t;

#define qmemcpy memcpy

#ifdef __cplusplus
extern "C" {
#endif

extern _WORD __ES__;
extern _WORD __DS__;

/* Watcom runtime helpers provided by decomp_runtime_stubs.cpp. */
int __fastcall _wcpp_4_ctor_array__(_DWORD base, _DWORD count);
int __fastcall _wcpp_4_dtor_array_store__(_DWORD base, _DWORD descriptor);
int __cdecl _wcpp_4_copy_array__(int base);
int __thiscall fclose_(_DWORD handle);
__int64 __fastcall nmalloc_(_DWORD count, _DWORD size);
int __fastcall memset_(_DWORD destination, _DWORD value);
int __fastcall strcmp_(_DWORD left, _DWORD right);
void *memmove_(void *destination, const void *source, size_t byte_count);
int __fastcall strupr_(_DWORD text, _DWORD unused);
_DWORD CRT_ProbeStackFrame(_DWORD size);
int atoi_(const char *text);
int __cdecl abs32(int value);
int __fastcall CRT_PutcToStream(_DWORD value, _DWORD stream);
int __fastcall CRT_SignedLongToDecimalString(_DWORD value, _DWORD buffer);
_DWORD CRT_FinalizeAnsiApiStringResult(const char *source);
_DWORD CRT_FinalizeWideApiStringResult(const _WORD *source);
void __lock_p(__lock *lock);
void __lock_v(__lock *lock);
int CRT_DispatchRegisteredFpeHandler(void);
void __fastcall __writefsdword(_DWORD offset, _DWORD value);
intptr_t __fastcall CRT_RegisterSignalHandler(
  int signal_number,
  intptr_t handler_value);
int __cdecl sprintf_(char *buffer, const char *format, ...);
char *strlwr_(char *text);
int __thiscall toupper_(_DWORD character);
int time_(void);
/* The recovered CRT import has the standard no-argument signature. */
int rand_(void);
/* Match the native render-hook ABI while preserving the direct pointer API. */
int Compat_WorldMapRenderHook(int first, char unused_char, _DWORD unused_context);
int Compat_UnitBattleRenderHook(int unused_first, char unused_char, _DWORD unused_context);
int Compat_DemoTextRenderHook(int first, char second, _DWORD context);
int Compat_CastleRenderHook(int first, char second, _DWORD unused_context);
int Compat_StreamWriteFormat32(int stream_ptr, const char *format,
                             const unsigned int *arg_slots, int arg_count);

#ifdef __cplusplus
}
#endif

#define BYTEn(x, n) (*((_BYTE *)&(x) + (n)))
#define WORDn(x, n) (*((_WORD *)&(x) + (n)))
#define DWORDn(x, n) (*((_DWORD *)&(x) + (n)))
#define MK_FP(seg, off) ((unsigned char *)(uintptr_t)(uint32_t)(uintptr_t)(off))

#define LOBYTE(x) BYTEn(x, 0)
#define HIBYTE(x) BYTEn(x, 1)
#define BYTE1(x) BYTEn(x, 1)
#define BYTE2(x) BYTEn(x, 2)
#define BYTE3(x) BYTEn(x, 3)
#define BYTE4(x) BYTEn(x, 4)
#define BYTE5(x) BYTEn(x, 5)
#define BYTE6(x) BYTEn(x, 6)
#define BYTE7(x) BYTEn(x, 7)
#define SBYTE1(x) (*((int8_t *)&(x) + 1))
#define LOWORD(x) WORDn(x, 0)
#define HIWORD(x) WORDn(x, 1)
#define LODWORD(x) DWORDn(x, 0)
#define HIDWORD(x) DWORDn(x, 1)
#define SHIDWORD(x) (*((int32_t *)&(x) + 1))
#define WORD1(x) WORDn(x, 1)
#define WORD2(x) WORDn(x, 2)
#define DWORD1(x) DWORDn(x, 1)
#define SLOBYTE(x) (*((int8_t *)&(x)))
#define SLOWORD(x) (*((int16_t *)&(x)))
#define SLODWORD(x) (*((int32_t *)&(x)))

#define COERCE_UNSIGNED_INT(x) (*((unsigned int *)&(x)))
#define COERCE_UNSIGNED_INT64(x) (*((unsigned long long *)&(x)))
#define COERCE_FLOAT(x) (*((float *)&(x)))
#define COERCE_DOUBLE(x) (*((double *)&(x)))

#define __PAIR64__(high, low) ((((uint64_t)(uint32_t)(uintptr_t)(high)) << 32) | (uint32_t)(uintptr_t)(low))
#define __CFSHL__(x, shift) ((((uint32_t)(x)) >> ((32 - ((shift) & 31)) & 31)) & ((shift) != 0))
#define __OFSUB__(x, y) ((((x) ^ (y)) & ((x) ^ ((x) - (y)))) < 0)

/* These existing inert inline seams retain their original local C names. */
#ifdef __cplusplus
static inline _DWORD ExcString_Ctor(void) __asm__("ExcString_Ctor");
static inline _DWORD ExcString_CtorFromPtr(void *this_) __asm__("ExcString_CtorFromPtr");
#endif

static inline _DWORD ExcString_Ctor(void) {
  return 0;
}

static inline _DWORD ExcString_CtorFromPtr(void *this_) {
  (void)this_;
  return 0;
}

#endif
