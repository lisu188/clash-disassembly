#include "../defs.h"

#include <ctype.h>
#include <errno.h>
#include <wchar.h>
#include <wctype.h>

int Mem_Alloc(int a1, int a2, char a3, _DWORD a4);
int sub_48703D(int a1, __lock *a2, int a3);
extern void *lpTlsValue;

/*
 * Narrow compile-time quarantine for late runtime helpers that still need
 * asm-backed reconstruction. These are outside the user-priority gameplay
 * path and are kept isolated so clash95.c can continue compiling.
 */

unsigned __int16 __ES__;
unsigned __int16 __DS__;
__lock unk_51A638;

/*
 * These are the lowest-risk CRT aliases still missing from the link surface.
 * They are kept here instead of being spread through gameplay code so later
 * runtime reconstruction can replace them in one place.
 */
int __thiscall nfree_(_DWORD a1)
{
  if ( a1 && a1 != (_DWORD)-1 )
    free((void *)(uintptr_t)a1);
  return 0;
}

__int64 __fastcall CRT_GetBootstrapThreadData(_DWORD a1, _DWORD a2)
{
  (void)a1;
  return __PAIR64__(a2, lpTlsValue);
}

int __fastcall CRT_RegisterFinalizableObject(_DWORD a1, _DWORD a2)
{
  /*
   * clash95.asm marks 0x473ED5 as an exact thunk to sub_48703D and shows
   * the target body using the fixed lock object at 0x51A638 rather than the
   * incoming edx value. Keeping the wrapper here removes the unresolved
   * thunk without spreading CRT bootstrap glue through clash95.c.
   */
  return sub_48703D((int)a1, &unk_51A638, (int)a2);
}

__int64 __thiscall j_Mem_Alloc(_DWORD a1)
{
  /*
   * clash95.asm marks 0x4730FB as a collapsed 5-byte thunk. The map binds
   * that thunk to j_Mem_Alloc, and the jump target is the recovered
   * Mem_Alloc body at 0x461C00.
   */
  return (unsigned int)Mem_Alloc((int)a1, 0, 0, 0);
}

int __fastcall strcmp_(_DWORD a1, _DWORD a2)
{
  const char *lhs;
  const char *rhs;

  lhs = (const char *)(uintptr_t)a1;
  rhs = (const char *)(uintptr_t)a2;
  if ( lhs == rhs )
    return 0;
  if ( !lhs )
    return -1;
  if ( !rhs )
    return 1;
  return strcmp(lhs, rhs);
}

int __cdecl sprintf_(char *buffer, const char *format, ...)
{
  int result;
  va_list args;

  if ( !buffer || !format )
    return -1;
  va_start(args, format);
  result = vsprintf(buffer, format, args);
  va_end(args);
  return result;
}

int __cdecl vsprintf_(char *buffer, const char *format, ...)
{
  int result;
  va_list args;

  if ( !buffer || !format )
    return -1;
  va_start(args, format);
  result = vsprintf(buffer, format, args);
  va_end(args);
  return result;
}

int __thiscall fclose_(_DWORD a1)
{
  FILE *stream;

  if ( !a1 || a1 == (_DWORD)-1 )
    return 0;
  stream = (FILE *)(uintptr_t)a1;
  return fclose(stream);
}

int fwrite_(const void *buffer, int size, int file_handle, int count)
{
  FILE *stream;

  if ( !buffer || !file_handle || file_handle == -1 || size < 0 || count < 0 )
    return 0;
  stream = (FILE *)(uintptr_t)file_handle;
  return (int)fwrite(buffer, (size_t)size, (size_t)count, stream);
}

int fread_(void *buffer, int size, int file_handle, int count)
{
  FILE *stream;

  if ( !buffer || !file_handle || file_handle == -1 || size < 0 || count < 0 )
    return 0;
  stream = (FILE *)(uintptr_t)file_handle;
  return (int)fread(buffer, (size_t)size, (size_t)count, stream);
}

int __fastcall strncmp_(_DWORD a1, _DWORD a2)
{
  return strcmp_(a1, a2);
}

int __fastcall tolower_(_DWORD a1, _DWORD a2)
{
  (void)a2;
  return tolower((unsigned __int8)a1);
}

int __thiscall toupper_(_DWORD a1)
{
  return toupper((unsigned __int8)a1);
}

int __thiscall towupper_(_DWORD a1)
{
  return towupper((wint_t)(unsigned __int16)a1);
}

errno_t __cdecl _set_errno_(int value)
{
  errno = value;
  return value;
}

int __fastcall sub_4697E0(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int sub_4849EE(void)
{
  return 0;
}

void __noreturn sub_4842DF(int a1, int a2)
{
  (void)a1;
  (void)a2;
  abort();
}

int sub_48469F(void)
{
  return 0;
}

/*
 * Map/asm corroborate these as collapsed one-byte `retn` placeholders.
 * Returning zero here is a compile/link quarantine choice, not a claim that
 * the original callers depended on a specific non-void result.
 */
int nullsub_1(void)
{
  return 0;
}

int __thiscall nullsub_2(_DWORD a1)
{
  (void)a1;
  return 0;
}

int __thiscall nullsub_3(_DWORD a1)
{
  (void)a1;
  return 0;
}

int nullsub_4(void)
{
  return 0;
}

int nullsub_5(void)
{
  return 0;
}

int __fastcall nullsub_6(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int __thiscall nullsub_7(_DWORD a1)
{
  (void)a1;
  return 0;
}

_DWORD nullsub_8(void)
{
  return 0;
}

int nullsub_9(void)
{
  return 0;
}

int nullsub_10(void)
{
  return 0;
}

int __fastcall nullsub_11(_DWORD a1, _DWORD a2)
{
  (void)a1;
  (void)a2;
  return 0;
}

int nullsub_15(void)
{
  return 0;
}

int nullsub_16(void)
{
  return 0;
}

int nullsub_19(void)
{
  return 0;
}

int nullsub_23(void)
{
  return 0;
}

int nullsub_24(void)
{
  return 0;
}

int nullsub_29(void)
{
  return 0;
}

int nullsub_30(void)
{
  return 0;
}

int nullsub_32(void)
{
  return 0;
}
