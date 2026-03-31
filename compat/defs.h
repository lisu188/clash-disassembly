#ifndef HEXRAYS_DEFS_H
#define HEXRAYS_DEFS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef unsigned char _BYTE;
typedef unsigned short _WORD;
typedef unsigned int _DWORD;
typedef uint64_t _QWORD;
typedef unsigned char _UNKNOWN;
typedef int __lock;
typedef uint16_t _BOOL2;
typedef struct CSyncObject CSyncObject;

struct CSyncObject
{
  int unused;
};

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
#ifndef __usercall
#define __usercall
#endif
#ifndef __userpurge
#define __userpurge
#endif
#ifndef __spoils
#define __spoils(...)
#endif
#ifndef __hidden
#define __hidden
#endif
#ifndef __pure
#define __pure
#endif
#ifndef __noreturn
#define __noreturn __attribute__((noreturn))
#endif

#ifndef BYREF
#define BYREF
#endif

#ifndef qmemcpy
#define qmemcpy memcpy
#endif

#define BYTEn(x, n) (*((_BYTE *)&(x) + (n)))
#define WORDn(x, n) (*((_WORD *)&(x) + (n)))
#define DWORDn(x, n) (*((_DWORD *)&(x) + (n)))

#define LOBYTE(x) BYTEn(x, 0)
#define HIBYTE(x) BYTEn(x, 1)
#define BYTE1(x) BYTEn(x, 1)
#define BYTE2(x) BYTEn(x, 2)
#define BYTE6(x) BYTEn(x, 6)
#define SLOBYTE(x) (*((int8_t *)&(x)))
#define SBYTE1(x) (*((int8_t *)&(x) + 1))

#define LOWORD(x) WORDn(x, 0)
#define HIWORD(x) WORDn(x, 1)
#define WORD2(x) WORDn(x, 2)

#define LODWORD(x) DWORDn(x, 0)
#define HIDWORD(x) DWORDn(x, 1)

#define COERCE_UNSIGNED_INT64(v) ((uint64_t)(uintptr_t)(v))

#endif
