/* CLIPS modules, classes, methods, and object metadata.
 * Original function-marker range: 0x00491580..0x004943A0.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00491580) --------------------------------------------------------
_DWORD *Module_BeginEnum()
{
  _DWORD *v0; // edx
  _DWORD *result; // eax

  v0 = *(_DWORD **)(dword_54DBA8 + 48);
  if ( v0 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 48);
    *(_DWORD *)(dword_54DBA8 + 48) = *v0;
    result = (_DWORD *)dword_54DBAC;
  }
  else
  {
    result = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *result = dword_51A9A8;
  dword_51A9A8 = 0;
  result[1] = dword_51A9B0;
  result[2] = dword_51A9A4;
  dword_51A9A4 = (int)result;
  return result;
}
// 51A9A4: using guessed type int dword_51A9A4;
// 51A9A8: using guessed type int dword_51A9A8;
// 51A9B0: using guessed type int dword_51A9B0;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004915E0) --------------------------------------------------------
int Module_EndEnum()
{
  int *v0; // eax
  int result; // eax

  v0 = (int *)dword_51A9A4;
  dword_51A9A4 = *(_DWORD *)(dword_51A9A4 + 8);
  dword_51A9A8 = *v0;
  dword_51A9B0 = v0[1];
  dword_54DBAC = (int)v0;
  *v0 = *(_DWORD *)(dword_54DBA8 + 48);
  result = dword_54DBAC;
  *(_DWORD *)(dword_54DBA8 + 48) = dword_54DBAC;
  return result;
}
// 51A9A4: using guessed type int dword_51A9A4;
// 51A9A8: using guessed type int dword_51A9A8;
// 51A9B0: using guessed type int dword_51A9B0;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491620) --------------------------------------------------------
int  Module_GetItem(int result, int a2)
{
  int v2; // ebx

  if ( !result )
  {
    if ( !dword_51A9B0 )
      return result;
    result = dword_51A9B0;
  }
  v2 = *(_DWORD *)(result + 8);
  if ( v2 )
    return *(_DWORD *)(v2 + 4 * a2);
  else
    return 0;
}
// 51A9B0: using guessed type int dword_51A9B0;

//----- (00491680) --------------------------------------------------------
int Module_CreateMainModule()
{
  int free_module; // edx
  int module; // ecx
  signed int *module_name; // eax
  int index; // esi
  int construct; // ecx
  int slot_offset; // edx
  int construct_data; // eax
  int (__fastcall *construct_initializer)(int, int); // eax

  free_module = *(_DWORD *)(dword_54DBA8 + 128);
  if ( free_module )
  {
    dword_54DBAC = free_module;
    *(_DWORD *)(dword_54DBA8 + 128) = *(_DWORD *)free_module;
    module = dword_54DBAC;
  }
  else
  {
    module = Mem_HeapAllocWithRetry((_DWORD *)0x20);
  }
  module_name = Str_Intern(aMain_1, module);
  *(_DWORD *)module = module_name;
  ++module_name[1];
  *(_DWORD *)(module + 28) = 0;
  *(_DWORD *)(module + 4) = 0;
  *(_DWORD *)(module + 12) = 0;
  *(_DWORD *)(module + 16) = 0;
  *(_DWORD *)(module + 24) = 0;
  if ( dword_51A9B8 )
  {
    *(_DWORD *)(module + 8) = Mem_SmallBlockAlloc(4 * dword_51A9B8);
    index = 0;
    construct = dword_51A9BC;
    if ( dword_51A9B8 > 0 )
    {
      slot_offset = 0;
      do
      {
        if ( !construct )
          break;
        if ( *(_DWORD *)(construct + 8) )
        {
          construct_initializer = (int (__fastcall *)(int, int))(uintptr_t)(unsigned int)*(_DWORD *)(construct + 8);
          construct_data = construct_initializer(construct, slot_offset);
          *(_DWORD *)(slot_offset + *(_DWORD *)(module + 8)) = construct_data;
          construct_data = *(_DWORD *)(slot_offset + *(_DWORD *)(module + 8));
          *(_DWORD *)(construct_data + 4) = 0;
          *(_DWORD *)(construct_data + 8) = 0;
          *(_DWORD *)construct_data = module;
        }
        else
        {
          *(_DWORD *)(slot_offset + *(_DWORD *)(module + 8)) = 0;
        }
        slot_offset += 4;
        ++index;
        construct = *(_DWORD *)(construct + 28);
      }
      while ( index < dword_51A9B8 );
    }
  }
  else
  {
    *(_DWORD *)(module + 8) = 0;
  }
  Module_SetModuleCount(1);
  dword_51A9B4 = module;
  dword_51A9AC = module;
  return Module_SetCurrent(module);
}
// 4916B3: variable 'v3' is possibly undefined
// 491728: variable 'v7' is possibly undefined
// 491759: variable 'v9' is possibly undefined
// 51A9AC: using guessed type int dword_51A9AC;
// 51A9B4: using guessed type int dword_51A9B4;
// 51A9B8: using guessed type int dword_51A9B8;
// 51A9BC: using guessed type int dword_51A9BC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491790) --------------------------------------------------------
void  Module_SetModuleListHead(int a1)
{
  dword_51A9AC = a1;
  dword_51A9B4 = a1;
  if ( a1 )
  {
    while ( *(_DWORD *)(dword_51A9B4 + 28) )
      dword_51A9B4 = *(_DWORD *)(dword_51A9B4 + 28);
  }
  return;
}
// 51A9AC: using guessed type int dword_51A9AC;
// 51A9B4: using guessed type int dword_51A9B4;

//----- (004917C0) --------------------------------------------------------
int  Module_NextEnum(int a1)
{
  if ( a1 )
    return *(_DWORD *)(a1 + 28);
  else
    return dword_51A9AC;
}
// 51A9AC: using guessed type int dword_51A9AC;

//----- (004917D0) --------------------------------------------------------
int  Module_GetName(int a1)
{
  return *(_DWORD *)(*(_DWORD *)a1 + 16);
}

//----- (004917E0) --------------------------------------------------------
int  Module_GetPPForm(int a1)
{
  return *(_DWORD *)(a1 + 4);
}

//----- (004917F0) --------------------------------------------------------
int Module_RemoveAllModules()
{
  int result; // eax
  int next_module; // edx

  if ( dword_51A9AC )
  {
    do
    {
      next_module = *(_DWORD *)(dword_51A9AC + 28);
      result = Module_FreeModule(dword_51A9AC);
      dword_51A9AC = next_module;
    }
    while ( next_module );
  }
  dword_51A9B0 = 0;
  dword_51A9B4 = 0;
  return result;
}
// 51A9AC: using guessed type int dword_51A9AC;
// 51A9B0: using guessed type int dword_51A9B0;
// 51A9B4: using guessed type int dword_51A9B4;

//----- (00491840) --------------------------------------------------------
int  Module_FreeModule(int result)
{
  int module; // esi
  int construct; // edx
  int construct_index; // ecx
  int slot_offset; // ebx
  int construct_data; // eax
  void (*construct_cleanup)(int); // eax
  int node; // edx
  int next_node; // ecx
  int module_name; // ebp

  module = result;
  if ( result )
  {
    Module_SetCurrent(result);
    if ( *(_DWORD *)(module + 8) )
    {
      construct = dword_51A9BC;
      construct_index = 0;
      if ( dword_51A9B8 > 0 )
      {
        slot_offset = 0;
        do
        {
          if ( !construct )
            break;
          if ( *(_DWORD *)(construct + 12) )
          {
            construct_data = *(_DWORD *)(slot_offset + *(_DWORD *)(module + 8));
            construct_cleanup = (void (*)(int))(uintptr_t)(unsigned int)*(_DWORD *)(construct + 12);
            construct_cleanup(construct_data);
          }
          slot_offset += 4;
          ++construct_index;
          construct = *(_DWORD *)(construct + 28);
        }
        while ( construct_index < dword_51A9B8 );
      }
      Mem_SmallBlockFree((_DWORD *)*(_DWORD *)(module + 8), 4 * dword_51A9B8);
    }
    Rules_DecrementSymbolCount(*(_DWORD *)module, 0);
    node = *(_DWORD *)(module + 12);
    if ( node )
    {
      do
      {
        next_node = *(_DWORD *)(node + 12);
        if ( *(_DWORD *)node )
          Rules_DecrementSymbolCount(*(_DWORD *)node, 0);
        if ( *(_DWORD *)(node + 4) )
          Rules_DecrementSymbolCount(*(_DWORD *)(node + 4), 0);
        if ( *(_DWORD *)(node + 8) )
          Rules_DecrementSymbolCount(*(_DWORD *)(node + 8), 0);
        dword_54DBAC = node;
        *(_DWORD *)node = *(_DWORD *)(dword_54DBA8 + 64);
        *(_DWORD *)(dword_54DBA8 + 64) = dword_54DBAC;
        node = next_node;
      }
      while ( next_node );
    }
    node = *(_DWORD *)(module + 16);
    if ( node )
    {
      do
      {
        next_node = *(_DWORD *)(node + 12);
        if ( *(_DWORD *)node )
          Rules_DecrementSymbolCount(*(_DWORD *)node, 0);
        if ( *(_DWORD *)(node + 4) )
          Rules_DecrementSymbolCount(*(_DWORD *)(node + 4), 0);
        if ( *(_DWORD *)(node + 8) )
          Rules_DecrementSymbolCount(*(_DWORD *)(node + 8), 0);
        dword_54DBAC = node;
        *(_DWORD *)node = *(_DWORD *)(dword_54DBA8 + 64);
        *(_DWORD *)(dword_54DBA8 + 64) = dword_54DBAC;
        node = next_node;
      }
      while ( next_node );
    }
    module_name = *(_DWORD *)(module + 4);
    if ( module_name )
      Mem_SmallBlockFree((_DWORD *)module_name, strlen((const char *)module_name) + 1);
    dword_54DBAC = module;
    *(_DWORD *)module = *(_DWORD *)(dword_54DBA8 + 128);
    *(_DWORD *)(dword_54DBA8 + 128) = dword_54DBAC;
    result = dword_54DBAC;
  }
  return result;
}
// 49188A: variable 'v4' is possibly undefined
// 49188B: variable 'v3' is possibly undefined
// 4918A9: variable 'v2' is possibly undefined
// 4918C3: variable 'v6' is possibly undefined
// 4918CC: variable 'v7' is possibly undefined
// 491918: variable 'v8' is possibly undefined
// 491921: variable 'v9' is possibly undefined
// 51A9B8: using guessed type int dword_51A9B8;
// 51A9BC: using guessed type int dword_51A9BC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004919B0) --------------------------------------------------------
int * Module_FindByName(_BYTE *a1)
{
  int *result; // eax
  int *v2; // edx
  int module;
  int module_symbol;
  int module_name;

  result = Rules_FindSymbolEntry(a1);
  v2 = result;
  if ( result )
  {
    result = (int *)dword_51A9AC;
    if ( dword_51A9AC )
    {
      while ( v2 != (int *)*result )
      {
        result = (int *)result[7];
        if ( !result )
          return 0;
      }
    }
    else
    {
      return 0;
    }
  }
  if ( result )
    return result;
  module = dword_51A9AC;
  while ( module )
  {
    module_symbol = *(_DWORD *)module;
    module_name = module_symbol ? *(_DWORD *)(module_symbol + 16) : 0;
    if ( module_name && !strcmp_((int)(uintptr_t)a1, module_name) )
      return (int *)(uintptr_t)(unsigned int)module;
    module = *(_DWORD *)(module + 28);
  }
  return 0;
}
// 51A9AC: using guessed type int dword_51A9AC;

//----- (004919E0) --------------------------------------------------------
signed int *Module_GetCurrentCommand()
{
  int v0; // ecx

  Lexer_TokenExpect(0);
  if ( dword_51A9B0 )
    return Str_Intern(*(char **)(*(_DWORD *)dword_51A9B0 + 16), v0);
  else
    return (signed int *)dword_54DD70;
}
// 491A06: variable 'v0' is possibly undefined
// 51A9B0: using guessed type int dword_51A9B0;
// 54DD70: using guessed type int dword_54DD70;

//----- (00491A10) --------------------------------------------------------
signed int * Module_SetCurrentCommand(int a1, double a2)
{
  signed int *v4; // esi
  int *v5; // eax
  int v6; // edx
  int v7; // ecx
  _DWORD v8[10]; // [esp-8h] [ebp-28h] BYREF

  v8[8] = a1;
  if ( !dword_51A9B0 )
    return (signed int *)dword_54DD70;
  v4 = Str_Intern(*(char **)(*(_DWORD *)dword_51A9B0 + 16), a1);
  if ( Lexer_TokenExpect(1) == -1 )
    return v4;
  if ( !Lexer_ParseValueList(1, v8, 2, a2) )
    return v4;
  v5 = Module_FindByName(*(_BYTE **)(v8[2] + 16));
  if ( v5 )
    Module_SetCurrent((int)v5);
  else
    Rules_ReportCantFindItem(v7, v6);
  return v4;
}
// 491A94: variable 'v7' is possibly undefined
// 491A94: variable 'v6' is possibly undefined
// 51A9B0: using guessed type int dword_51A9B0;
// 54DD70: using guessed type int dword_54DD70;

//----- (00491AE0) --------------------------------------------------------
signed int Module_ReportIllegalSpecifierError()
{
  int v0; // ecx

  Rules_PrintErrorID((int)aModuldef, 1, 1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIllegalUseOfTh, v0);
}
// 491AFD: variable 'v0' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00491B10) --------------------------------------------------------
signed int IO_RegisterStringRouter()
{
  return IO_AddRouter((int)aString, 0, (int)IO_StringRouterPrint, (int)IO_StringRouterQuery, (int)IO_StringRouterGetc, (int)IO_StringRouterUngetc, 0);
}

//----- (00491B40) --------------------------------------------------------
signed int  IO_StringRouterQuery(int a1)
{
  int router_entry; // ecx

  router_entry = dword_51A9C8;
  while ( router_entry )
  {
    if ( !strcmp_(*(_DWORD *)router_entry, a1) )
      return 1;
    router_entry = *(_DWORD *)(router_entry + 20);
  }
  return 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9C8: using guessed type int dword_51A9C8;

//----- (00491B80) --------------------------------------------------------
int  IO_StringRouterPrint(int a1, const char *a2)
{
  int v3; // ecx
  _DWORD *v4; // esi
  int v5; // ecx

  v4 = (_DWORD *)IO_FindStringRouter(a1);
  if ( !v4 )
  {
    Rules_ReportSystemError(v3, 3);
    IO_RunRouterExitCallbacks();
  }
  if ( v4[4] != 1 )
    return 1;
  v5 = v4[2];
  if ( v4[3] - 1 <= v5 )
    return v4[4];
  strncpy_(v5, a2);
  v4[2] += strlen(a2);
  return 1;
}
// 491BB4: variable 'v3' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (00491C00) --------------------------------------------------------
int  IO_StringRouterGetc(int a1)
{
  _DWORD *v1; // ecx
  int result; // eax
  int v3; // esi

  v1 = (_DWORD *)IO_FindStringRouter(a1);
  if ( !v1 )
  {
    Rules_ReportSystemError(0, 1);
    IO_RunRouterExitCallbacks();
  }
  if ( v1[4] )
    return -1;
  if ( v1[2] < v1[3] )
  {
    v3 = v1[2];
    result = *(unsigned __int8 *)(v3 + v1[1]);
    v1[2] = v3 + 1;
  }
  else
  {
    result = -1;
    ++v1[2];
  }
  return result;
}
// 491C0F: variable 'v1' is possibly undefined

//----- (00491C70) --------------------------------------------------------
int __fastcall IO_StringRouterUngetc(int a1, int a2)
{
  int v2; // ecx
  int v3; // ebx

  v2 = IO_FindStringRouter(a2);
  if ( !v2 )
  {
    Rules_ReportSystemError(0, 2);
    IO_RunRouterExitCallbacks();
  }
  if ( *(_DWORD *)(v2 + 16) )
    return 0;
  v3 = *(_DWORD *)(v2 + 8);
  if ( v3 > 0 )
    *(_DWORD *)(v2 + 8) = v3 - 1;
  return 1;
}
// 491C7E: variable 'v2' is possibly undefined

//----- (00491CC0) --------------------------------------------------------
signed int  IO_OpenStringSource(int a1, const char *a2, int a3)
{
  if ( a2 )
    return IO_OpenTextSource(a1, a2, strlen(a2), a3);
  else
    return IO_OpenTextSource(a1, 0, 0, 0);
}

//----- (00491D00) --------------------------------------------------------
signed int  IO_OpenTextSource(int a1, const void *a2, int a3, int a4)
{
  const char *v4; // esi
  _DWORD *v6; // edx
  char *payload_copy; // eax
  size_t name_length; // eax

  v4 = (const char *)a1;
  if ( IO_FindStringRouter(a1) )
    return 0;
  v6 = *(_DWORD **)(dword_54DBA8 + 96);
  if ( v6 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 96);
    *(_DWORD *)(dword_54DBA8 + 96) = *v6;
  }
  else
  {
    v6 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  name_length = strlen(v4) + 1;
  v6[0] = (int)Mem_SmallBlockAllocZeroed(name_length);
  memcpy((void *)v6[0], v4, name_length);
  if ( a2 && a3 > 0 )
  {
    payload_copy = (char *)Compat_AllocLow32Bytes(a3 + 1);
    if ( !payload_copy )
      return 0;
    memcpy(payload_copy, a2, a3);
    payload_copy[a3] = 0;
    v6[1] = (int)(uintptr_t)payload_copy;
  }
  else
  {
    v6[1] = 0;
  }
  v6[2] = a4;
  v6[3] = a3;
  v6[4] = 0;
  v6[5] = dword_51A9C8;
  dword_51A9C8 = (int)v6;
  return 1;
}
// 51A9C8: using guessed type int dword_51A9C8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491DB0) --------------------------------------------------------
signed int  IO_CloseStringRouter(int a1)
{
  _DWORD *v2; // ebx
  _DWORD *v3; // esi
  int key_length; // edx

  v2 = (_DWORD *)dword_51A9C8;
  v3 = 0;
  while ( v2 )
  {
    if ( !strcmp_(v2[0], a1) )
      break;
    v3 = v2;
    v2 = (_DWORD *)v2[5];
  }
  if ( !v2 )
    return 0;
  if ( v3 )
  {
    v3[5] = v2[5];
  }
  else
  {
    dword_51A9C8 = v2[5];
  }
  if ( !v2[4] && v2[1] )
    Compat_FreeLow32Bytes(v2[1]);
  key_length = strlen((const char *)v2[0]) + 1;
  Mem_SmallBlockFree((_DWORD *)v2[0], key_length);
  dword_54DBAC = (int)v2;
  v2[0] = *(_DWORD *)(dword_54DBA8 + 96);
  *(_DWORD *)(dword_54DBA8 + 96) = dword_54DBAC;
  return 1;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9C8: using guessed type int dword_51A9C8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491E80) --------------------------------------------------------
signed int  IO_OpenStringDestination(int a1, const void *a2, int a3)
{
  const char *v3; // esi
  _DWORD *v5; // edx
  size_t name_length; // eax

  v3 = (const char *)a1;
  if ( IO_FindStringRouter(a1) )
    return 0;
  v5 = *(_DWORD **)(dword_54DBA8 + 96);
  if ( v5 )
  {
    dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 96);
    *(_DWORD *)(dword_54DBA8 + 96) = *v5;
  }
  else
  {
    v5 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x18);
  }
  name_length = strlen(v3) + 1;
  v5[0] = (int)Mem_SmallBlockAllocZeroed(name_length);
  memcpy((void *)v5[0], v3, name_length);
  v5[2] = 0;
  v5[4] = 1;
  v5[1] = (int)a2;
  v5[3] = a3;
  v5[5] = dword_51A9C8;
  dword_51A9C8 = (int)v5;
  return 1;
}
// 51A9C8: using guessed type int dword_51A9C8;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00491F30) --------------------------------------------------------
int  IO_FindStringRouter(int a1)
{
  _DWORD *v2; // ecx

  v2 = (_DWORD *)dword_51A9C8;
  while ( v2 )
  {
    if ( !strcmp_(v2[0], a1) )
      return (int)v2;
    v2 = (_DWORD *)v2[5];
  }
  return 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9C8: using guessed type int dword_51A9C8;

//----- (00491F60) --------------------------------------------------------
int  Rules_ParseAssertCommand(int a1, _DWORD *a2, int a3, int *a4, int a5, int a6)
{
  int v7; // eax
  signed int v8; // esi
  int v9; // edx
  unsigned int v10; // ecx
  int **Symbol; // eax
  signed int v12; // eax
  int v13; // ecx
  signed int v14; // ecx
  int **v16; // eax
  int v17; // ecx
  signed int v20; // [esp+8h] [ebp-10h]

  v7 = a5;
  *a4 = 0;
  if ( !a5 && *a2 == 101 )
  {
    if ( a3 )
    {
      *a4 = 1;
      Parser_ReportSyntaxError();
    }
    return 0;
  }
  v8 = 0;
  v20 = 0;
  while ( 1 )
  {
    v10 = Rules_ParseAssertRHSPattern(a1, (int)a2, 0, a4, v7, 1, 101);
    if ( !v10 )
      break;
    AST_Append(v10, v9);
    Symbol = Rules_MakeSymbol(aAssert_1);
    v12 = AST_NewNode(10, (int)Symbol);
    *(_DWORD *)(v12 + 6) = v13;
    v14 = v12;
    if ( v8 )
      *(_DWORD *)(v8 + 10) = v12;
    else
      v20 = v12;
    v7 = 1;
    v8 = v14;
  }
  if ( *a4 )
  {
    AST_Free(v20);
    return 0;
  }
  else
  {
    if ( *a2 == 101 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_504BB8);
    }
    if ( !v20 )
    {
      if ( a3 )
      {
        *a4 = 1;
        Parser_ReportSyntaxError();
        return 0;
      }
      return 0;
    }
    if ( *(_DWORD *)(v20 + 10) )
    {
      v16 = Rules_MakeSymbol(aProgn_3);
      v20 = AST_NewNode(10, (int)v16);
      *(_DWORD *)(v20 + 6) = v17;
    }
    return v20;
  }
}
// 491FA6: variable 'v9' is possibly undefined
// 491FC1: variable 'v13' is possibly undefined
// 492079: variable 'v17' is possibly undefined

//----- (00492090) --------------------------------------------------------
unsigned int  Rules_ParseAssertRHSPattern(
        int a1,
        int a2,
        int a3,
        int *a4,
        int a5,
        int a6,
        int a7)
{
  unsigned int v10; // eax
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // eax
  int v16; // ebx
  int v17; // eax
  _BYTE *v19; // ebx
  int v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // edx
  signed int v24; // edx
  int v25; // eax
  signed int v26; // eax
  int v27; // [esp+0h] [ebp-30h] BYREF
  int v28; // [esp+4h] [ebp-2Ch] BYREF
  signed int v29; // [esp+8h] [ebp-28h]
  signed int v30; // [esp+Ch] [ebp-24h]
  int v31; // [esp+10h] [ebp-20h]
  int v32; // [esp+14h] [ebp-1Ch]
  int v33; // [esp+18h] [ebp-18h]
  int v34; // [esp+1Ch] [ebp-14h]
  int v35; // [esp+20h] [ebp-10h]

  v33 = a3;
  v34 = 0;
  *a4 = 0;
  v35 = 0;
  if ( a5 )
    Parser_NextToken(a1, a2);
  if ( a6 )
  {
    v10 = *(_DWORD *)a2;
    if ( *(_DWORD *)a2 == a7 )
      return a7 ^ v10;
    if ( v10 != 100 )
      goto LABEL_20;
  }
  Parser_NextToken(a1, a2);
  v32 = *(_DWORD *)((uintptr_t)(unsigned int)a2 + 4);
  v19 = (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)v32 + 16);
  if ( *(_DWORD *)(uintptr_t)(unsigned int)a2 != 2 || !strcmp((const char *)v19, asc_504BF4) || !strcmp((const char *)v19, asc_504BF8) )
  {
LABEL_20:
    Parser_ReportSyntaxError();
    *a4 = 1;
    return 0;
  }
  if ( Rules_IsReservedPatternSymbol((int)(uintptr_t)v19, 0) )
  {
    Rules_PrintReservedSymbolErrorMessage((int)(uintptr_t)v19, (int)aARelationName);
    *a4 = 1;
    return 0;
  }
  if ( Rules_FindModuleSeparator(v19) )
  {
    Module_ReportIllegalSpecifierError();
    *a4 = 1;
    return 0;
  }
  v15 = Rules_FindImportExportConstruct(aDeftemplate, &v28, v19, 1, 0);
  v16 = v15;
  if ( v28 > 1 )
  {
    Rules_ReportAmbiguousReferenceError((int)aDeftemplate, (int)(uintptr_t)v19);
    *a4 = 1;
    return 0;
  }
  if ( !v15 )
  {
    if ( Rules_IsBloaded() )
    {
      Rules_ReportNoTemplateError();
      *a4 = 1;
      return 0;
    }
    v20 = Module_GetCurrent();
    if ( Rules_FindImportExportConflict(aDeftemplate, v20, v19) )
    {
      Lexer_WarnImpliedTemplate((int)aImpliedDeftemp, (int)(uintptr_t)v19, 0);
      *a4 = 1;
      return 0;
    }
    v16 = Rules_CreateDeftemplateRecord(v32, 1);
  }
  if ( (*(_BYTE *)(v16 + 24) & 1) != 0 )
  {
    v31 = AST_NewNode(35, v16);
    while ( 1 )
    {
      IO_OutWriteToken(asc_504C2C);
      v17 = Rules_ParseAssertArgument(a1, (unsigned int *)(uintptr_t)(unsigned int)a2, a4, a7, v33, &v27);
      if ( !v17 )
        break;
      if ( v35 )
        *(_DWORD *)(v34 + 10) = v17;
      else
        v35 = v17;
      v34 = v17;
    }
    if ( *a4 )
    {
      if ( v27 )
        Parser_ReportSyntaxError();
      AST_Free(v31);
      AST_Free(v35);
      return 0;
    }
    else
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(*(char **)(a2 + 8));
      v25 = Rules_AddBitmapValue(g_Rules_DefaultZeroBitmapValue, v24);
      v26 = AST_NewNode(34, v25);
      *(_DWORD *)(v31 + 10) = v26;
      *(_DWORD *)(v26 + 6) = v35;
      return v31;
    }
  }
  else
  {
    v30 = AST_NewNode(35, v16);
    v29 = v30;
    v22 = Rules_ParseAssertTemplate(a1, a2, a7, a4, v21, v16);
    v23 = v30;
    *(_DWORD *)(v30 + 10) = v22;
    if ( *a4 )
    {
      AST_Free(v23);
      return 0;
    }
    return v29;
  }
}
// 4920F3: variable 'v11' is possibly undefined
// 49210B: variable 'v12' is possibly undefined
// 492124: variable 'v13' is possibly undefined
// 49222E: variable 'v14' is possibly undefined
// 49231D: variable 'v21' is possibly undefined
// 4923AB: variable 'v24' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 504C30: using guessed type _BYTE byte_504C30[4];

//----- (004923E0) --------------------------------------------------------
int  Rules_ParseAssertArgument(int a1, unsigned int *a2, _DWORD *a3, int a4, int a5, _DWORD *a6)
{
  unsigned int v7; // edx
  int token_symbol; // eax
  const char *token_text; // eax
  bool parse_expression; // zf
  int result; // eax
  unsigned int token_type; // eax

  *a6 = 1;
  Parser_NextToken(a1, (int)a2);
  v7 = *a2;
  if ( a4 == *a2 )
    return 0;
  if ( v7 == 2 )
  {
    token_symbol = a2[1];
    token_text = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)token_symbol + 16);
    parse_expression = strcmp(token_text, asc_504BF4) == 0;
  }
  else
  {
    parse_expression = v7 == 100;
  }
  if ( !parse_expression )
  {
    token_type = *a2;
    if ( *a2 != 2 && token_type != 3 && token_type != 8 && token_type >= 2 )
    {
      if ( token_type != 15 && token_type != 13 && token_type != 14 && token_type != 16 )
      {
        *a3 = 1;
        return 0;
      }
      if ( a5 )
      {
        *a3 = 1;
        return 0;
      }
    }
    return AST_NewNode(*a2, a2[1]);
  }
  if ( a5 )
  {
    *a3 = 1;
    return 0;
  }
  else
  {
    if ( *a2 == 100 )
      result = Parser_ParseExpression(a1, a4);
    else
      result = Parser_ParseRequiredFunctionCall(a1, a4);
    if ( !result )
    {
      *a6 = 0;
      *a3 = 1;
    }
  }
  return result;
}
// 49247B: simplified comparisons for 'eax.4': ==0 || ==1 became <2u

//----- (004924D0) --------------------------------------------------------
_DWORD * Rules_StringToFact(const char *a1, int a2, double a3)
{
  signed int v4; // esi
  unsigned int v5; // edi
  int v6; // ecx
  int v7; // ecx
  int i; // eax
  _DWORD *v9; // eax
  __int16 *v10; // ecx
  _DWORD *v11; // esi
  _DWORD *v12; // ebx
  EvalResultBuffer parsed; // [esp-4h] [ebp-3Ch] BYREF
  int token_buffer_ptr; // [esp+14h] [ebp-24h]
  int v20[6]; // [esp+20h] [ebp-18h] BYREF

  v20[4] = a2;
  v4 = 0;
  v20[0] = 0;
  token_buffer_ptr = Compat_AllocLow32Bytes(12);
  if ( !token_buffer_ptr )
    return 0;
  IO_OpenStringSource((int)aAssert_str, a1, 0);
  v5 = Rules_ParseAssertRHSPattern((int)aAssert_str, token_buffer_ptr, 0, v20, 1, 1, 101);
  IO_CloseStringRouter((int)aAssert_str);
  if ( v20[0] )
  {
    AST_Free(v5);
    Compat_FreeLow32Bytes(token_buffer_ptr);
    return 0;
  }
  else if ( AST_TreeContainsSpecialTag(v5, 0) )
  {
    Rules_ReportLocalVariableError();
    Lexer_ErrorRecover(1);
    AST_Free(v5);
    Compat_FreeLow32Bytes(token_buffer_ptr);
    return 0;
  }
  else
  {
    for ( i = *(_DWORD *)((uintptr_t)(unsigned int)v5 + 10); i; ++v4 )
      i = *(_DWORD *)(i + 10);
    v9 = Module_AllocList(v4);
    v9[4] = *(_DWORD *)((uintptr_t)(unsigned int)v5 + 2);
    v10 = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)v5 + 10);
    v11 = v9;
    if ( v10 )
    {
      v12 = v9;
      do
      {
        memset(&parsed, 0, sizeof(parsed));
        Parser_ParseForm(v10, (_DWORD *)&parsed, (int)v10, a3);
        *((_WORD *)v12 + 27) = parsed.type;
        v12[14] = parsed.value;
        v10 = (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)v10 + 10);
        v12 = (_DWORD *)((char *)v12 + 6);
      }
      while ( v10 );
    }
    AST_Free(v5);
    Compat_FreeLow32Bytes(token_buffer_ptr);
    return v11;
  }
}

//----- (004925D0) --------------------------------------------------------
signed int Rules_ReportNoTemplateError()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aFactrhs, 1, 0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTemplate, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v1, v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDoesNotExistFo, v2);
}
// 4925F0: variable 'v0' is possibly undefined
// 4925FC: variable 'v1' is possibly undefined
// 49260B: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00492620) --------------------------------------------------------
int  Rules_FindModuleSeparator(_BYTE *a1)
{
  int v1; // ecx
  int v2; // edx
  char v3; // bl

  if ( getenv("CLASH95_TRACE_PARSER_QUALIFIER_SCAN") )
  {
    fprintf(stderr, "[parser] qualifier-scan text=%p caller=%p\n", a1, __builtin_return_address(0));
    fflush(stderr);
  }
  v1 = 0;
  v2 = 0;
  if ( *a1 )
  {
    do
    {
      if ( *a1 == 58 )
      {
        if ( v2 )
          return v1;
        v2 = 1;
      }
      else
      {
        v2 = 0;
      }
      v3 = *++a1;
      ++v1;
    }
    while ( v3 );
  }
  return 0;
}

//----- (00492660) --------------------------------------------------------
signed int * Rules_ExtractModuleName(signed int a1)
{
  char *v2; // esi
  int v3; // edx
  int v4; // ecx
  int v5; // ecx
  signed int *v6; // ebx
  int v7; // edx

  if ( a1 <= 1 )
    return 0;
  v2 = (char *)Mem_SmallBlockAlloc(a1);
  strncpy_(v4, v3);
  v2[v5 - 1] = 0;
  v6 = Str_Intern(v2, v5);
  Mem_SmallBlockFree(v2, v7);
  return v6;
}
// 492678: variable 'v4' is possibly undefined
// 492678: variable 'v3' is possibly undefined
// 49267D: variable 'v5' is possibly undefined
// 492691: variable 'v7' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (004926A0) --------------------------------------------------------
signed int * Rules_ExtractConstructName(int a1, char *a2, int a3)
{
  signed int v3; // ecx
  int v5; // esi
  _DWORD *v6; // eax
  int v7; // edx
  char *v8; // ecx
  signed int *v9; // ebx
  _DWORD *v10; // ecx

  if ( !a1 )
    return Str_Intern(a2, a3);
  v3 = strlen(a2);
  if ( v3 <= a1 + 1 )
    return 0;
  v5 = v3 - a1;
  v6 = Mem_SmallBlockAlloc(v3 - a1);
  strncpy_(v6, v7);
  v9 = Str_Intern(v8, (int)v8);
  Mem_SmallBlockFree(v10, v5);
  return v9;
}
// 4926E1: variable 'v7' is possibly undefined
// 4926E8: variable 'v8' is possibly undefined
// 4926F3: variable 'v10' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (00492700) --------------------------------------------------------
int  Rules_ExtractModuleAndConstructName(_BYTE *a1)
{
  signed int qualifier_length; // eax
  signed int *module_symbol; // eax
  int *module_record; // eax
  signed int *local_symbol; // eax

  qualifier_length = Rules_FindModuleSeparator(a1);
  if ( !qualifier_length )
    return (int)a1;
  module_symbol = Rules_ExtractModuleName(qualifier_length);
  if ( !module_symbol )
    return 0;
  module_record = Module_FindByName((_BYTE *)module_symbol[4]);
  if ( !module_record )
    return 0;
  Module_SetCurrent((int)module_record);
  local_symbol = Rules_ExtractConstructName(qualifier_length, (char *)a1, (int)a1);
  if ( !local_symbol )
    return 0;
  return local_symbol[4];
}

//----- (00492760) --------------------------------------------------------
int  Rules_FindImportExportConstruct(char *a1, _DWORD *a2, _BYTE *a3, int a4, int a5)
{
  int construct_record; // ebx
  signed int *local_symbol; // ecx
  signed int *construct_symbol; // eax
  int result; // edx

  *a2 = 0;
  if ( Rules_FindModuleSeparator(a3) )
    return 0;
  Module_BeginEnum();
  construct_record = Module_FindItemByName((int)a1);
  if ( construct_record && *(_DWORD *)((uintptr_t)(unsigned int)construct_record + 24) )
  {
    Rules_ClearModuleSearchMarkers();
    local_symbol = Str_Intern((char *)a3, 0);
    construct_symbol = Str_Intern(a1, 0);
    result = Rules_SearchImportExportModules((int)(uintptr_t)construct_symbol, 0, (int)(uintptr_t)local_symbol, construct_record, a2, a4, a5);
    Module_EndEnum();
    return result;
  }
  else
  {
    Module_EndEnum();
    return 0;
  }
}

//----- (004927E0) --------------------------------------------------------
signed int  Rules_ReportAmbiguousReferenceError(int a1, int a2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx

  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAmbiguousRefer, a1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v3, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_504CA8, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], a2, v5);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)a_ItIsImportedF, v6);
}
// 4927FC: variable 'v3' is possibly undefined
// 49280B: variable 'v4' is possibly undefined
// 492817: variable 'v5' is possibly undefined
// 492826: variable 'v6' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (00492830) --------------------------------------------------------
int Rules_ClearModuleSearchMarkers()
{
  int result; // eax

  if ( !dword_51A9B0 )
  {
    result = Module_NextEnum(0);
    if ( !result )
      return 0;
    Module_SetCurrent(result);
  }
  *(_DWORD *)(dword_51A9B0 + 20) = 0;
  for ( result = Module_NextEnum(0); result; result = Module_NextEnum(result) )
    *(_DWORD *)(result + 20) = 0;
  return result;
}
// 51A9B0: using guessed type int dword_51A9B0;

//----- (00492870) --------------------------------------------------------
int  Rules_SearchImportExportModules(int a1, int a2, int a3, int a4, _DWORD *a5, int a6, int a7)
{
  int current_module; // edx
  int found_construct; // eax
  int import_node; // ebp
  int imported_module; // eax
  int export_node; // eax
  int import_matches; // ecx
  int export_matches; // edx
  int result; // [esp+8h] [ebp-14h]
  int (*lookup_by_name)(const char *, int); // [esp+Ch] [ebp-10h]
  const char *local_name; // eax

  current_module = Module_GetCurrent();
  result = 0;
  if ( *(_DWORD *)((uintptr_t)(unsigned int)current_module + 20) )
    return 0;
  if ( a6 && (!a2 || current_module == a2) )
  {
    lookup_by_name = (int (*)(const char *, int))(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a4 + 24);
    local_name = (const char *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)a3 + 16);
    found_construct = lookup_by_name(local_name, a4);
    if ( current_module == a7 )
    {
      result = found_construct;
      ++*a5;
    }
    else if ( found_construct )
    {
      if ( current_module == *(_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)found_construct + 8) )
        ++*a5;
      result = found_construct;
    }
  }
  *(_DWORD *)((uintptr_t)(unsigned int)current_module + 20) = 1;
  current_module = Module_GetCurrent();
  import_node = *(_DWORD *)((uintptr_t)(unsigned int)current_module + 12);
  while ( import_node )
  {
    imported_module = current_module;
    import_matches = 0;
    found_construct = *(_DWORD *)((uintptr_t)(unsigned int)import_node + 4);
    if ( !found_construct || a1 == found_construct )
    {
      found_construct = *(_DWORD *)((uintptr_t)(unsigned int)import_node + 8);
      if ( !found_construct || a3 == found_construct )
      {
        import_matches = 1;
        imported_module = (int)(uintptr_t)Module_FindByName(
                                            (_BYTE *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)import_node + 16));
        if ( !imported_module )
          goto next_import;
      }
    }
    if ( import_matches )
    {
      export_matches = 0;
      export_node = *(_DWORD *)((uintptr_t)(unsigned int)imported_module + 16);
      while ( export_node )
      {
        found_construct = *(_DWORD *)((uintptr_t)(unsigned int)export_node + 4);
        if ( !found_construct || a1 == found_construct )
        {
          found_construct = *(_DWORD *)((uintptr_t)(unsigned int)export_node + 8);
          if ( !found_construct || a3 == found_construct )
          {
            export_matches = 1;
            break;
          }
        }
        export_node = *(_DWORD *)((uintptr_t)(unsigned int)export_node + 12);
      }
      if ( !export_matches )
        goto next_import;
    }
    if ( import_matches )
    {
      Module_SetCurrent(imported_module);
      found_construct = Rules_SearchImportExportModules(a1, a2, a3, a4, a5, 1, a7);
      if ( found_construct )
        result = found_construct;
    }
next_import:
    import_node = *(_DWORD *)((uintptr_t)(unsigned int)import_node + 12);
  }
  return result;
}

//----- (004929E0) --------------------------------------------------------
int  Rules_ListConstructsAcrossModules(
        int a1,
        int Enum,
        int a3,
        int a4,
        int (__cdecl *a5)(int),
        int (*a6)(void),
        void (__fastcall *a7)(int, int),
        int (*a8)(void))
{
  int v9; // ebp
  int v10; // edi
  int v11; // edx
  int Name; // eax
  int v13; // ecx
  int v14; // ecx
  int result; // eax
  int i; // ecx
  int v17; // ecx
  int v18; // ebx
  int v19; // ecx
  int v20; // [esp+0h] [ebp-18h]

  v20 = a3;
  Module_BeginEnum();
  v9 = 0;
  v10 = 0;
  if ( !v11 )
  {
    v10 = 1;
    Enum = Module_NextEnum(0);
  }
  while ( Enum )
  {
    if ( v10 )
    {
      Name = Module_GetName(Enum);
      Output_Write(a1, Name, v13);
      Output_Write(a1, (int)asc_504CDC, v14);
    }
    Module_SetCurrent(Enum);
    result = a5(v20);
    for ( i = result; result; i = result )
    {
      if ( dword_51A968 == 1 )
        return result;
      if ( !a8 || a8() )
      {
        if ( !a6 )
        {
          if ( !a7 )
            goto LABEL_15;
          if ( v10 )
            Output_Write(a1, (int)asc_504CE0, i);
          a7(i, i);
          goto LABEL_14;
        }
        v18 = a6();
        if ( v18 )
        {
          if ( v10 )
            Output_Write(a1, (int)asc_504CE0, v17);
          Output_Write(a1, v18, v17);
LABEL_14:
          Output_Write(a1, (int)asc_504CE4, v19);
        }
      }
LABEL_15:
      result = ((int (*)(void))a5)();
      ++v9;
    }
    if ( !v10 )
      break;
    Enum = Module_NextEnum(Enum);
  }
  if ( a4 )
    Rules_PrintTally(a1, v9, v20, a4);
  return Module_EndEnum();
}
// 4929FE: variable 'v11' is possibly undefined
// 492A1F: variable 'v13' is possibly undefined
// 492A2B: variable 'v14' is possibly undefined
// 492A3B: variable 'v20' is possibly undefined
// 492A7F: variable 'v17' is possibly undefined
// 492A94: variable 'v19' is possibly undefined
// 492B04: variable 'i' is possibly undefined
// 51A968: using guessed type int dword_51A968;

//----- (00492B30) --------------------------------------------------------
int Rules_RegisterDeftemplateConstruct()
{
  int v0; // edx
  int v1; // ecx

  Rules_InitFacts();
  Rules_InitDeftemplateHashTable();
  Rules_RegisterDeftemplateFunctions(v1, v0);
  Rules_RegisterModifyDuplicateFunctions();
  dword_54E650 = (int)Rules_RegisterConstructType(
                        (int)aDeftemplate_1,
                        (int)aDeftemplates,
                        (int)Rules_FindDeftemplateByName,
                        (int)Rules_ParseDeftemplate,
                        (int)Rules_GetConstructNameSymbol,
                        (int)Rules_GetModuleConstructListHead,
                        (int)Rules_GetConstructOwnerModule,
                        (int)Rules_GetNextDeftemplate,
                        (int)Rules_SetConstructNextInModule,
                        (int)Rules_DeftemplateIsDeletable,
                        (int)Rules_DeleteDeftemplate,
                        (int)Rules_FreeDeftemplateRecord);
  return Rules_RegisterEvaluationHandler((int)&unk_51A9CC, 35);
}
// 492B3D: variable 'v1' is possibly undefined
// 492B3D: variable 'v0' is possibly undefined
// 54E650: using guessed type int dword_54E650;

//----- (00492BA0) --------------------------------------------------------
int *Rules_InitDeftemplateHashTable()
{
  dword_54E654 = Module_RegisterItem(
                   (int)aDeftemplate_1,
                   (int)Rules_AllocDeftemplateHashNode,
                   (int)Rules_DeftemplateGetBloadedModuleItem,
                   (int)Rules_FreeDeftemplateHashNode,
                   (int)Rules_DeftemplateWriteModuleHeaderRef,
                   (int)Rules_FindDeftemplateByName);
  return Module_RegisterImportExportConstructType((int)aDeftemplate_1, 2);
}
// 54E654: using guessed type int dword_54E654;

//----- (00492BE0) --------------------------------------------------------
signed int Rules_AllocDeftemplateHashNode()
{
  _DWORD *v0; // edx

  v0 = *(_DWORD **)(dword_54DBA8 + 48);
  if ( !v0 )
    return Mem_HeapAllocWithRetry((_DWORD *)0xC);
  dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 48);
  *(_DWORD *)(dword_54DBA8 + 48) = *v0;
  return dword_54DBAC;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00492C10) --------------------------------------------------------
int  Rules_FreeDeftemplateHashNode(int a1)
{
  int result; // eax
  _DWORD *freed_node; // ecx

  result = Rules_ClearModuleConstructList(a1, dword_54E650, a1);
  freed_node = (_DWORD *)a1;
  dword_54DBAC = a1;
  *freed_node = *(_DWORD *)(dword_54DBA8 + 48);
  *(_DWORD *)(dword_54DBA8 + 48) = dword_54DBAC;
  return result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E650: using guessed type int dword_54E650;

//----- (00492C60) --------------------------------------------------------
int  Rules_FindDeftemplateByName(_BYTE *a1, int a2)
{
  return Rules_FindConstructByNameGeneric(a1, dword_54E650);
}
// 54E650: using guessed type int dword_54E650;

//----- (00492C70) --------------------------------------------------------
int  Rules_GetNextDeftemplate(int a1)
{
  return Class_Enum(a1, dword_54E654);
}
// 54E654: using guessed type int dword_54E654;

//----- (00492C80) --------------------------------------------------------
int Rules_DeftemplateIsDeletable()
{
  int result; // eax
  int v1; // edx

  result = Rules_IsBloaded();
  if ( result )
    return 0;
  if ( *(int *)(v1 + 28) <= 0 && !*(_DWORD *)(v1 + 32) )
    return 1;
  return result;
}
// 492C8C: variable 'v1' is possibly undefined

//----- (00492CB0) --------------------------------------------------------
int  Rules_FreeDeftemplateRecord(int result)
{
  int template_def; // ecx
  int slot; // edx
  int next_slot; // ecx

  template_def = result;
  if ( result )
  {
    dword_51A948 = (*(_BYTE *)(template_def + 24) & 2) != 0;
    slot = *(_DWORD *)(template_def + 20);
    while ( slot )
    {
      Rules_DecrementSymbolCount(*(_DWORD *)slot, template_def);
      AST_RemoveHashedNodeChain((__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)(slot + 12), template_def);
      AST_DecrementNodeRefCount((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(slot + 8));
      *(_DWORD *)(slot + 12) = 0;
      *(_DWORD *)(slot + 8) = 0;
      next_slot = *(_DWORD *)(slot + 16);
      slot = next_slot;
    }
    Rules_FreeTemplateSlotList(*(_DWORD *)(template_def + 20));
    Rules_FreeConstructHeaderString((int *)(uintptr_t)(unsigned int)template_def, template_def);
    dword_54DBAC = template_def;
    *(_DWORD *)template_def = *(_DWORD *)(dword_54DBA8 + 144);
    result = dword_54DBAC;
    *(_DWORD *)(dword_54DBA8 + 144) = dword_54DBAC;
  }
  return result;
}
// 51A948: using guessed type int dword_51A948;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00492D60) --------------------------------------------------------
int  Rules_FreeTemplateSlotList(int result)
{
  int node; // edx
  int next; // ecx
  int last_result; // eax

  node = result;
  last_result = 0;
  while ( node )
  {
    next = *(_DWORD *)(node + 16);
    AST_Free(*(_DWORD *)(node + 12));
    AST_DecrementNodeRefCount((_DWORD *)(uintptr_t)(unsigned int)*(_DWORD *)(node + 8));
    dword_54DBAC = node;
    *(_DWORD *)node = *(_DWORD *)(dword_54DBA8 + 80);
    last_result = dword_54DBA8;
    *(_DWORD *)(dword_54DBA8 + 80) = dword_54DBAC;
    node = next;
  }
  return last_result;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00492DB0) --------------------------------------------------------
int  Rules_DecrementBusyCount(int result)
{
  if ( !g_Rules_ClearInProgressFlag )
    --*(_DWORD *)(result + 28);
  return result;
}
// 51A180: using guessed type int dword_51A180;

//----- (00492DC0) --------------------------------------------------------
int  Rules_IncrementBusyCount(int result)
{
  ++*(_DWORD *)(result + 28);
  return result;
}

//----- (00492DD0) --------------------------------------------------------
int Rules_InitExpressionHashTable()
{
  int result; // eax

  Rules_CacheConnectiveSymbols();
  dword_51A9FC = (int)Mem_SmallBlockAlloc(0x7DCu);
  for ( result = 0; result != 2012; result += 4 )
    *(_DWORD *)(dword_51A9FC + result) = 0;
  return result;
}
// 51A9FC: using guessed type int dword_51A9FC;

//----- (00492E10) --------------------------------------------------------
int **Rules_CacheConnectiveSymbols()
{
  int **result; // eax
  int v1; // ecx

  dword_54E65C = (int)Rules_MakeSymbol(aAnd);
  dword_54E664 = (int)Rules_MakeSymbol(aOr);
  dword_54E658 = (int)Rules_MakeSymbol(aEq);
  dword_54E668 = (int)Rules_MakeSymbol(aNeq);
  result = Rules_MakeSymbol(aNot);
  dword_54E660 = (int)result;
  if ( !dword_54E65C || !dword_54E664 || !dword_54E658 || !dword_54E668 || !result )
  {
    Rules_ReportSystemError(v1, 1);
    return (int **)IO_RunRouterExitCallbacks();
  }
  return result;
}
// 492E91: variable 'v1' is possibly undefined
// 54E658: using guessed type int dword_54E658;
// 54E65C: using guessed type int dword_54E65C;
// 54E660: using guessed type int dword_54E660;
// 54E664: using guessed type int dword_54E664;
// 54E668: using guessed type int dword_54E668;

//----- (00492EB0) --------------------------------------------------------
__int16 * AST_InstallNodeChain(__int16 *result)
{
  __int16 *node; // ecx
  int child_node; // eax
  int next_node; // ecx

  for ( node = result; node; node = (__int16 *)(uintptr_t)(unsigned int)next_node )
  {
    Rules_AtomInstall(*node, *(_DWORD *)(node + 1), (int)(uintptr_t)node);
    child_node = *(_DWORD *)((char *)node + 6);
    AST_InstallNodeChain((__int16 *)(uintptr_t)(unsigned int)child_node);
    next_node = *(_DWORD *)((char *)node + 10);
  }
  return result;
}

//----- (00492EE0) --------------------------------------------------------
__int16 * AST_DeinstallNodeChain(__int16 *result)
{
  __int16 *node; // ecx
  int child_node; // eax
  int next_node; // ecx

  for ( node = result; node; node = (__int16 *)(uintptr_t)(unsigned int)next_node )
  {
    Rules_AtomDeinstall(
      *node,
      (__int16 *)(uintptr_t)(unsigned int)*(_DWORD *)((char *)node + 2),
      (int)(uintptr_t)node);
    child_node = *(_DWORD *)((char *)node + 6);
    AST_DeinstallNodeChain((__int16 *)(uintptr_t)(unsigned int)child_node);
    next_node = *(_DWORD *)((char *)node + 10);
  }
  return result;
}

//----- (00492F10) --------------------------------------------------------
_DWORD * AST_PackNodeChain(_DWORD *result)
{
  int node_count; // eax
  _DWORD *copy; // esi

  if ( result )
  {
    node_count = AST_CountTreeNodes((int)result);
    copy = Mem_NewArray(14 * node_count);
    AST_CopyNodeChainToArray((int)result, (int)copy, 0);
    return copy;
  }
  return result;
}

//----- (00492F50) --------------------------------------------------------
int  AST_CopyNodeChainToArray(int a1, int a2, int a3)
{
  int node; // ecx
  int current_index; // edi
  int output_node; // eax
  int child_node; // edx
  int next_node; // edi

  node = a1;
  if ( !a1 )
    return a3;
  while ( node )
  {
    current_index = a3;
    output_node = a2 + 14 * a3;
    *(_WORD *)output_node = *(_WORD *)node;
    *(_DWORD *)(output_node + 2) = *(_DWORD *)(node + 2);
    ++a3;
    child_node = *(_DWORD *)(node + 6);
    if ( child_node )
    {
      *(_DWORD *)(output_node + 6) = a2 + 14 * a3;
      a3 = AST_CopyNodeChainToArray(child_node, a2, a3);
    }
    else
    {
      *(_DWORD *)(output_node + 6) = 0;
    }
    next_node = *(_DWORD *)(node + 10);
    if ( next_node )
      *(_DWORD *)(a2 + 14 * current_index + 10) = a2 + 14 * a3;
    else
      *(_DWORD *)(a2 + 14 * current_index + 10) = 0;
    node = next_node;
  }
  return a3;
}

//----- (00492FD0) --------------------------------------------------------
int  AST_FreePackedNodeChain(int result)
{
  int node_count; // eax

  if ( result )
  {
    node_count = AST_CountTreeNodes(result);
    return Mem_SmallBlockRelease((_DWORD *)result, 14 * node_count);
  }
  return result;
}

//----- (00492FF0) --------------------------------------------------------
signed int AST_AllocNode()
{
  int node;

  node = *(_DWORD *)(dword_54DBA8 + 288);
  if ( node )
  {
    dword_54DBAC = node;
    *(_DWORD *)(dword_54DBA8 + 288) = *(_DWORD *)node;
    node = dword_54DBAC;
  }
  else
  {
    node = Mem_HeapAllocWithRetry((_DWORD *)0x48);
  }

  *(_DWORD *)node = 103;
  *(_DWORD *)(node + 4) = 0;
  *(_DWORD *)(node + 16) = 0;
  *(_DWORD *)(node + 20) = 0;
  *(_DWORD *)(node + 24) = 0;
  *(_DWORD *)(node + 28) = -1;
  *(_DWORD *)(node + 32) = -1;
  *(_DWORD *)(node + 36) = 0;
  *(_DWORD *)(node + 40) = -1;
  *(_DWORD *)(node + 44) = 1;
  *(_DWORD *)(node + 48) = 1;
  *(_DWORD *)(node + 52) = 0;
  *(_DWORD *)(node + 56) = 0;
  *(_DWORD *)(node + 60) = 0;
  *(_DWORD *)(node + 64) = 0;
  *(_DWORD *)(node + 68) = 0;
  *(_DWORD *)(node + 8) &= 0xE0003FC0;
  *(_WORD *)(node + 12) &= 0xC000u;
  *(_BYTE *)(node + 8) |= 0x20u;
  return node;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493050) --------------------------------------------------------
int AST_FreeNode(int result)
{
  int node;
  int owner;
  int (__thiscall *cleanup_fn)(void *this, int);

  node = result;
  if ( !node )
    return 0;

  AST_Free(*(_DWORD *)(node + 52));
  AST_FreeNode(*(_DWORD *)(node + 64));
  AST_FreeNode(*(_DWORD *)(node + 68));
  AST_FreeNode(*(_DWORD *)(node + 56));
  if ( *(_BYTE *)(node + 8) & 0x10 )
    AST_DecrementNodeRefCount(*(_DWORD **)(node + 16));

  if ( *(_DWORD *)(node + 60) )
  {
    owner = *(_DWORD *)(node + 24);
    if ( owner )
    {
      cleanup_fn = *(int (__thiscall **)(void *this, int))(owner + 64);
      if ( cleanup_fn )
        cleanup_fn((void *)owner, *(_DWORD *)(node + 60));
    }
  }

  dword_54DBAC = node;
  *(_DWORD *)node = *(_DWORD *)(dword_54DBA8 + 288);
  *(_DWORD *)(dword_54DBA8 + 288) = dword_54DBAC;
  return dword_54DBA8;
}
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493000) --------------------------------------------------------
int  AST_Free(int result)
{
  int i; // edx
  _DWORD *v2; // eax

  for ( i = result; i; *(_DWORD *)(dword_54DBA8 + 56) = dword_54DBAC )
  {
    if ( *(_DWORD *)(i + 6) )
      AST_Free(*(_DWORD *)(i + 6));
    v2 = (_DWORD *)i;
    i = *(_DWORD *)(i + 10);
    dword_54DBAC = (int)v2;
    *v2 = *(_DWORD *)(dword_54DBA8 + 56);
    result = dword_54DBAC;
  }
  return result;
}
// 493015: variable 'i' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493050) --------------------------------------------------------
__int16 * AST_FindHashedNodeChain(__int16 *result, _DWORD *a2)
{
  __int16 *v3; // esi
  unsigned int v4; // eax
  unsigned int *v5; // edx
  int v6; // ecx
  int v7; // ecx

  v3 = result;
  if ( result )
  {
    v4 = AST_HashNodeChain(result);
    *v5 = v4;
    *a2 = 0;
    v6 = *(_DWORD *)(dword_51A9FC + 4 * *v5);
    if ( v6 )
    {
      while ( !AST_NodeListsEqual(*(__int16 **)(v6 + 8), v3) )
      {
        *a2 = v7;
        v6 = *(_DWORD *)(v7 + 12);
        if ( !v6 )
          return 0;
      }
      return (__int16 *)v7;
    }
    else
    {
      return 0;
    }
  }
  return result;
}
// 493060: variable 'v5' is possibly undefined
// 493084: variable 'v7' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;

//----- (004930A0) --------------------------------------------------------
unsigned int  AST_HashNodeChain(__int16 *a1)
{
  __int16 *v1; // edx
  int v2; // ecx
  unsigned int v3; // eax
  int v4; // ebx
  unsigned int v5; // eax

  v1 = a1;
  v2 = *(_DWORD *)(a1 + 3);
  v3 = 269;
  if ( v2 )
    v3 = 257 * AST_HashNodeChain(v2) + 269;
  while ( v1 )
  {
    v4 = *(_DWORD *)(v1 + 1);
    v5 = 263 * *v1 + v3;
    v1 = *(__int16 **)(v1 + 5);
    v3 = v4 + v5;
  }
  return v3 % 0x1F7;
}
// 4930B3: variable 'v1' is possibly undefined

//----- (004930F0) --------------------------------------------------------
__int16 * AST_RemoveHashedNodeChain(__int16 *a1, int a2)
{
  __int16 *result; // eax
  int v4; // ecx
  int v5; // edx
  _DWORD *v6; // edx
  _DWORD v7[5]; // [esp+0h] [ebp-14h] BYREF

  v7[3] = a2;
  result = AST_FindHashedNodeChain(a1, v7);
  if ( result )
  {
    v4 = *((_DWORD *)result + 1) - 1;
    *((_DWORD *)result + 1) = v4;
    if ( !v4 )
    {
      if ( v7[0] )
        *(_DWORD *)(v7[0] + 12) = *((_DWORD *)result + 3);
      else
        *(_DWORD *)(dword_51A9FC + 4 * v7[1]) = *((_DWORD *)result + 3);
      AST_DeinstallNodeChain(*((__int16 **)result + 2));
      AST_FreePackedNodeChain(*(_DWORD *)(v5 + 8));
      dword_54DBAC = (int)v6;
      *v6 = *(_DWORD *)(dword_54DBA8 + 80);
      result = (__int16 *)dword_54DBAC;
      *(_DWORD *)(dword_54DBA8 + 80) = dword_54DBAC;
    }
  }
  return result;
}
// 493127: variable 'v5' is possibly undefined
// 493134: variable 'v6' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493170) --------------------------------------------------------
__int16 * AST_AddHashedNodeChain(__int16 *result, int a2, int a3)
{
  __int16 *v3; // eax
  _DWORD *v4; // ecx
  _DWORD *v5; // edx
  _DWORD *v6; // edx
  __int16 *v7; // eax
  int v8; // edx
  _DWORD *v9; // edx
  _DWORD v10[5]; // [esp-4h] [ebp-14h] BYREF

  v10[3] = a3;
  v10[2] = a2;
  if ( result )
  {
    v3 = AST_FindHashedNodeChain(result, v10);
    if ( v3 )
    {
      ++*((_DWORD *)v3 + 1);
      return (__int16 *)*((_DWORD *)v3 + 2);
    }
    else
    {
      v5 = *(_DWORD **)(dword_54DBA8 + 80);
      if ( v5 )
      {
        dword_54DBAC = *(_DWORD *)(dword_54DBA8 + 80);
        *(_DWORD *)(dword_54DBA8 + 80) = *v5;
        v6 = (_DWORD *)dword_54DBAC;
      }
      else
      {
        v6 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x14);
      }
      *v6 = v10[1];
      v6[1] = 1;
      v7 = (__int16 *)AST_PackNodeChain(v4);
      *(_DWORD *)(v8 + 8) = v7;
      AST_InstallNodeChain(v7);
      v9[3] = *(_DWORD *)(dword_51A9FC + 4 * *v9);
      *(_DWORD *)(dword_51A9FC + 4 * *v9) = v9;
      v9[4] = 0;
      return (__int16 *)v9[2];
    }
  }
  return result;
}
// 4931B9: variable 'v4' is possibly undefined
// 4931BE: variable 'v8' is possibly undefined
// 4931CC: variable 'v9' is possibly undefined
// 51A9FC: using guessed type int dword_51A9FC;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (00493210) --------------------------------------------------------
signed int  AST_GetHashedNodeIndex(__int16 *a1)
{
  __int16 *v2; // eax
  int v3; // [esp+0h] [ebp-8h] BYREF

  if ( !a1 )
    return -1;
  v2 = AST_FindHashedNodeChain(a1, &v3);
  if ( v2 )
    return *((_DWORD *)v2 + 4);
  else
    return -1;
}

//----- (00493250) --------------------------------------------------------
char * Parser_NextToken(int a1, int a2)
{
  unsigned int v4; // ecx
  char v5; // dl
  signed int v6; // eax
  unsigned int v7; // ecx
  int v8; // eax
  signed int v9; // edx
  signed int *v10; // eax
  int v11; // eax
  char *v12; // eax
  char *result; // eax
  unsigned int v14; // ecx
  int v15; // ecx
  unsigned int v16; // ecx
  signed int v17; // ecx
  int v18; // edi
  const char *v19; // edi
  int v20; // edx
  int v21; // edx
  unsigned int v22; // kr0C_4
  int v23; // ecx
  signed int *v24; // eax
  unsigned int v25; // ecx
  int v26; // ecx
  unsigned int v27; // ecx
  signed int v28; // ecx
  int v29; // edi
  const char *v30; // edi
  int v31; // edx
  int v32; // edx
  unsigned int v33; // kr18_4
  int v34; // ecx
  signed int *v35; // eax
  signed int *v36; // eax
  int v37; // eax
  unsigned int v38; // ecx
  signed int v39; // ecx
  signed int v40; // eax
  int v41; // ecx
  int v42; // ecx
  char *appended; // eax
  signed int *v44; // eax
  signed int *v45; // eax
  signed int *v46; // eax
  unsigned int v47; // ecx
  int v48; // ecx
  int v49; // [esp+0h] [ebp-1Ch] BYREF
  int i; // [esp+4h] [ebp-18h]

  if ( getenv("CLASH95_TRACE_PARSER_TOKEN") )
  {
    fprintf(
      stderr,
      "[parser] next-token lexer=%08x token=%08x caller=%p\n",
      a1,
      a2,
      __builtin_return_address(0));
    fflush(stderr);
  }
  *(_DWORD *)a2 = 103;
  *(_DWORD *)(a2 + 4) = 0;
  *(_DWORD *)(a2 + 8) = aUnknown;
  g_TokenCap = 0;
  g_TokenLen = 0;
  for ( i = Lexer_PeekChar(a1, 0xDu);
        i == 32 || i == 10 || i == 12 || v4 == i || i == 59 || i == 9;
        i = Lexer_PeekChar(a1, v4) )
  {
    if ( i == 59 )
    {
      for ( i = Lexer_PeekChar(a1, v4); i != 10; i = Lexer_PeekChar(a1, v4) )
      {
        if ( v4 == i )
          break;
        if ( i == -1 )
          break;
      }
    }
  }
  v5 = IsTable[(unsigned __int8)(i + 1)];
  if ( (v5 & 0xC0) != 0 )
  {
    v6 = i;
    *(_DWORD *)a2 = 2;
    Lexer_SkipChar(v6, a1, v4);
    v8 = a1;
    v9 = 0;
LABEL_12:
    v10 = (signed int *)(uintptr_t)(unsigned int)(uintptr_t)Lexer_ReadToken(v8, v9, &v49, v7);
    *(_DWORD *)(a2 + 4) = (int)(uintptr_t)v10;
LABEL_13:
    v11 = v10[4];
LABEL_14:
    *(_DWORD *)(a2 + 8) = v11;
    goto LABEL_15;
  }
  if ( (v5 & 0x20) != 0 )
    goto LABEL_37;
  if ( i >= 41 )
  {
    if ( i <= 41 )
    {
      *(_DWORD *)a2 = 101;
      v44 = Str_Intern(asc_504D38, v4);
      *(_DWORD *)(a2 + 8) = asc_504D38;
      *(_DWORD *)(a2 + 4) = v44;
      goto LABEL_15;
    }
    if ( i >= 60 )
    {
      if ( i <= 60 )
      {
        *(_DWORD *)a2 = 2;
        appended = Str_AppendCharEscaping(
                     60,
                     (char *)g_TokenBuf,
                     (unsigned int *)&g_TokenLen,
                     &g_TokenCap,
                     g_TokenLen + 80);
        v9 = 1;
        g_TokenBuf = (int)appended;
        v8 = a1;
        goto LABEL_12;
      }
      if ( i >= 124 )
      {
        if ( i <= 124 )
        {
          *(_DWORD *)a2 = 92;
          v45 = Str_Intern(asc_504D40, v4);
          *(_DWORD *)(a2 + 8) = asc_504D40;
          *(_DWORD *)(a2 + 4) = v45;
          goto LABEL_15;
        }
        if ( i == 126 )
        {
          *(_DWORD *)a2 = 90;
          v24 = Str_Intern(asc_504D3C, v4);
          *(_DWORD *)(a2 + 8) = asc_504D3C;
          *(_DWORD *)(a2 + 4) = v24;
          goto LABEL_15;
        }
      }
      else if ( i == 63 )
      {
        i = Lexer_PeekChar(a1, v4);
        v15 = i;
        if ( (IsTable[(unsigned __int8)(i + 1)] & 0xC0) != 0 || i == 42 )
        {
          Lexer_SkipChar(i, a1, i);
          *(_DWORD *)(a2 + 4) = Lexer_ReadToken(a1, 0, &v49, v16);
          v18 = *(_DWORD *)(a2 + 4);
          *(_DWORD *)a2 = 15;
          v19 = *(const char **)(v18 + 16);
          if ( *v19 != 42
            || (v17 = strlen(v19), v17 <= 1)
            || (v20 = *(_DWORD *)(a2 + 4),
                v17 = strlen(*(const char **)(v20 + 16)),
                *(_BYTE *)(v17 + *(_DWORD *)(v20 + 16) - 1) != 42) )
          {
            v11 = Str_Concat(aQuestion_LexerSingleFieldVarPrefix, *(const char **)(*(_DWORD *)(a2 + 4) + 16), v17);
            goto LABEL_14;
          }
          v21 = *(_DWORD *)(a2 + 4);
          *(_DWORD *)a2 = 13;
          *(_DWORD *)(a2 + 8) = Str_Concat(aQuestion_LexerSingleFieldVarPrefix, *(const char **)(v21 + 16), v17);
          v22 = strlen((const char *)g_TokenBuf) + 1;
          *(_BYTE *)(v22 - 1 + g_TokenBuf - 1) = 0;
          *(_DWORD *)(a2 + 4) = Str_Intern((char *)(g_TokenBuf + 1), v22 - 1);
          *(_BYTE *)(g_TokenBuf + v23 - 1) = i;
        }
        else
        {
          *(_DWORD *)a2 = 17;
          *(_DWORD *)(a2 + 4) = Str_Intern(aQuestion_LexerSingleFieldVarPrefix, v15);
          Lexer_SkipChar(v39, a1, v39);
          *(_DWORD *)(a2 + 8) = aQuestion_LexerSingleFieldVarPrefix;
        }
        goto LABEL_15;
      }
      goto LABEL_30;
    }
    if ( i >= 45 )
    {
      if ( i > 46 )
        goto LABEL_30;
    }
    else if ( i != 43 )
    {
      goto LABEL_30;
    }
LABEL_37:
    Lexer_SkipChar(i, a1, v4);
    Lexer_ScanNumberToken(a1, (_DWORD *)a2, v14);
    goto LABEL_15;
  }
  if ( i < 34 )
  {
    if ( i >= 0 )
    {
      if ( i > 0 && i != 3 )
        goto LABEL_30;
LABEL_66:
      *(_DWORD *)a2 = 102;
      v36 = Str_Intern(aStop, v4);
      *(_DWORD *)(a2 + 8) = g_Lexer_EmptyQuotedStringBuffer;
      *(_DWORD *)(a2 + 4) = v36;
      goto LABEL_15;
    }
    if ( i == -1 )
      goto LABEL_66;
LABEL_30:
    if ( (IsTable[(unsigned __int8)(i + 1)] & 8) != 0 )
    {
      Lexer_SkipChar(i, a1, v4);
      *(_DWORD *)(a2 + 4) = Lexer_ReadToken(a1, 0, &v49, v47);
      *(_DWORD *)a2 = v49;
      v10 = (signed int *)(uintptr_t)(unsigned int)*(_DWORD *)(a2 + 4);
      goto LABEL_13;
    }
    *(_DWORD *)(a2 + 8) = aUnprintableCha;
    goto LABEL_15;
  }
  if ( i <= 34 )
  {
    *(_DWORD *)(a2 + 4) = Lexer_ReadQuotedString(a1, v4);
    v37 = *(_DWORD *)(a2 + 4);
    *(_DWORD *)a2 = 3;
    v11 = Str_InternQuotedEscapedString(*(int **)(v37 + 16), v38);
    goto LABEL_14;
  }
  if ( i >= 38 )
  {
    if ( i <= 38 )
    {
      *(_DWORD *)a2 = 91;
      v46 = Str_Intern(asc_504D44, v4);
      *(_DWORD *)(a2 + 8) = asc_504D44;
      *(_DWORD *)(a2 + 4) = v46;
      goto LABEL_15;
    }
    if ( i == 40 )
    {
      *(_DWORD *)a2 = 100;
      v35 = Str_Intern(asc_504D34, v4);
      *(_DWORD *)(a2 + 8) = asc_504D34;
      *(_DWORD *)(a2 + 4) = v35;
      goto LABEL_15;
    }
    goto LABEL_30;
  }
  if ( i != 36 )
    goto LABEL_30;
  i = Lexer_PeekChar(a1, v4);
  if ( i != 63 )
  {
    *(_DWORD *)a2 = 2;
    g_TokenBuf = (int)Str_AppendCharEscaping(
                        36,
                        (char *)g_TokenBuf,
                        (unsigned int *)&g_TokenLen,
                        &g_TokenCap,
                        g_TokenLen + 80);
    Lexer_SkipChar(i, a1, v42);
    v9 = 1;
    v8 = a1;
    goto LABEL_12;
  }
  i = Lexer_PeekChar(a1, v25);
  if ( (IsTable[(unsigned __int8)(i + 1)] & 0xC0) != 0 || i == 42 )
  {
    Lexer_SkipChar(i, a1, v26);
    *(_DWORD *)(a2 + 4) = Lexer_ReadToken(a1, 0, &v49, v27);
    v29 = *(_DWORD *)(a2 + 4);
    *(_DWORD *)a2 = 16;
    v30 = *(const char **)(v29 + 16);
    if ( *v30 != 42
      || (v28 = strlen(v30), v28 <= 1)
      || (v31 = *(_DWORD *)(a2 + 4),
          v28 = strlen(*(const char **)(v31 + 16)),
          *(_BYTE *)(v28 + *(_DWORD *)(v31 + 16) - 1) != 42) )
    {
      v11 = Str_Concat(aQuestion_LexerMultiFieldVarPrefix, *(const char **)(*(_DWORD *)(a2 + 4) + 16), v28);
      goto LABEL_14;
    }
    v32 = *(_DWORD *)(a2 + 4);
    *(_DWORD *)a2 = 14;
    *(_DWORD *)(a2 + 8) = Str_Concat(aQuestion_LexerMultiFieldVarPrefix, *(const char **)(v32 + 16), v28);
    v33 = strlen((const char *)g_TokenBuf) + 1;
    *(_BYTE *)(v33 - 1 + g_TokenBuf - 1) = 0;
    *(_DWORD *)(a2 + 4) = Str_Intern((char *)(g_TokenBuf + 1), v33 - 1);
    *(_BYTE *)(v34 + g_TokenBuf - 1) = i;
  }
  else
  {
    *(_DWORD *)a2 = 18;
    *(_DWORD *)(a2 + 4) = Str_Intern(aQuestion_LexerMultiFieldVarPrefix, v26);
    v40 = i;
    *(_DWORD *)(a2 + 8) = aQuestion_LexerMultiFieldVarPrefix;
    Lexer_SkipChar(v40, a1, v41);
  }
LABEL_15:
  if ( *(_DWORD *)a2 == 8 )
  {
    IO_OutWriteToken(asc_504D70);
    IO_OutWriteToken(*(char **)(a2 + 8));
    v12 = asc_504D74;
  }
  else
  {
    v12 = *(char **)(a2 + 8);
  }
  result = IO_OutWriteToken(v12);
  if ( g_TokenBuf )
  {
    result = (char *)Mem_SmallBlockFree((_DWORD *)g_TokenBuf, g_TokenLen);
    g_TokenBuf = 0;
    g_TokenLen = 0;
    g_TokenCap = 0;
  }
  return result;
}
// 493549: simplified comparisons for '%var_18.4': <2E || ==2E became <2F
// 4932C2: variable 'v4' is possibly undefined
// 4932FD: variable 'v7' is possibly undefined
// 49341B: variable 'v14' is possibly undefined
// 493478: variable 'v16' is possibly undefined
// 49350D: variable 'v23' is possibly undefined
// 49358B: variable 'v25' is possibly undefined
// 4935BB: variable 'v26' is possibly undefined
// 4935C4: variable 'v27' is possibly undefined
// 49365D: variable 'v34' is possibly undefined
// 4936D2: variable 'v38' is possibly undefined
// 4936E7: variable 'v17' is possibly undefined
// 493708: variable 'v39' is possibly undefined
// 493724: variable 'v28' is possibly undefined
// 49374E: variable 'v41' is possibly undefined
// 49378B: variable 'v42' is possibly undefined
// 493846: variable 'v47' is possibly undefined
// 493875: variable 'v48' is possibly undefined
// 51AA00: using guessed type int g_TokenBuf;
// 51AA04: using guessed type int g_TokenLen;
// 51AA08: using guessed type int g_TokenCap;

//----- (00493890) --------------------------------------------------------
signed int * Lexer_ReadToken(
        int a1,
        signed int a2,
        _DWORD *a3,
        unsigned int a4)
{
  int v6; // ecx
  unsigned int v7; // ecx
  int v8; // ecx
  signed int *result; // eax
  int i; // [esp+0h] [ebp-14h]

  for ( i = Lexer_PeekChar(a1, a4); i != 60; i = Lexer_PeekChar(a1, v7) )
  {
    if ( i == 34 )
      break;
    if ( i == 40 )
      break;
    if ( i == 41 )
      break;
    if ( i == 38 )
      break;
    if ( i == 124 )
      break;
    if ( i == 126 )
      break;
    if ( i == 32 )
      break;
    if ( i == 59 )
      break;
    if ( (IsTable[(unsigned __int8)(i + 1)] & 8) == 0 )
      break;
    g_TokenBuf = (int)Str_AppendCharEscaping(
                        i,
                        (char *)g_TokenBuf,
                        (unsigned int *)&g_TokenLen,
                        &g_TokenCap,
                        g_TokenLen + 80);
    ++a2;
  }
  Lexer_SkipChar(i, a1, v6);
  if ( a2 > 2 && *(_BYTE *)g_TokenBuf == 91 && *(_BYTE *)(a2 + g_TokenBuf - 1) == 93 )
  {
    *a3 = 8;
    *(_BYTE *)(a2 + g_TokenBuf - 1) = 0;
    result = Str_Intern((char *)(g_TokenBuf + 1), v8);
    *(_BYTE *)(g_TokenBuf + a2 - 1) = 93;
  }
  else
  {
    *a3 = 2;
    return Str_Intern((char *)g_TokenBuf, v8);
  }
  return result;
}
// 493922: variable 'v7' is possibly undefined
// 493938: variable 'v6' is possibly undefined
// 49397A: variable 'v8' is possibly undefined
// 51AA00: using guessed type int g_TokenBuf;
// 51AA04: using guessed type int g_TokenLen;
// 51AA08: using guessed type int g_TokenCap;

//----- (004939B0) --------------------------------------------------------
signed int * Lexer_ReadQuotedString(int a1, unsigned int a2)
{
  char *appended; // edi
  int i; // eax
  unsigned int v6; // ecx
  unsigned int v7; // ecx
  int v9; // ecx
  int v10; // [esp+0h] [ebp-1Ch] BYREF
  unsigned int v11[6]; // [esp+4h] [ebp-18h] BYREF

  v11[4] = a2;
  appended = 0;
  v10 = 0;
  v11[0] = 0;
  for ( i = Lexer_PeekChar(a1, a2); i != 34; i = Lexer_PeekChar(a1, v7) )
  {
    if ( i == -1 )
      break;
    if ( i == 92 )
      i = Lexer_PeekChar(a1, v6);
    appended = Str_AppendCharEscaping(i, appended, v11, &v10, v11[0] + 80);
  }
  if ( i == -1 && !dword_51AA0C )
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aEncounteredEnd, v6);
  if ( !appended )
    return Str_Intern(g_Lexer_EmptyQuotedStringBuffer, v6);
  Str_Intern(appended, v6);
  Mem_SmallBlockFree(appended, v11[0]);
  return (signed int *)v9;
}
// 4939DB: variable 'v6' is possibly undefined
// 4939FB: variable 'v7' is possibly undefined
// 493A51: variable 'v9' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 51AA0C: using guessed type int dword_51AA0C;

//----- (00493A60) --------------------------------------------------------
int  Lexer_ScanNumberToken(int a1, _DWORD *a2, unsigned int a3)
{
  int v3; // ebp
  char v4; // bl
  unsigned int v5; // eax
  int v6; // ecx
  char *v7; // edx
  int v8; // edi
  int v9; // esi
  char *appended; // eax
  unsigned int v11; // ecx
  char *v12; // eax
  int v13; // ecx
  int v14; // eax
  signed int v15; // ecx
  int v16; // ecx
  int *v17; // eax
  int v18; // edx
  int result; // eax
  int v20; // edx
  signed int v21; // edi
  char *v22; // eax
  unsigned int v23; // ecx
  signed int *v24; // eax
  _DWORD *v25; // edx
  char v26; // al
  signed int *v27; // eax
  int v28; // edx
  int v29; // eax
  int v30; // edx
  int v31; // edx
  double v32; // [esp+0h] [ebp-44h]
  int v33; // [esp+8h] [ebp-3Ch] BYREF
  _DWORD *v34; // [esp+Ch] [ebp-38h]
  int v35; // [esp+10h] [ebp-34h]
  int v36; // [esp+14h] [ebp-30h]
  int v37; // [esp+18h] [ebp-2Ch]
  int v38; // [esp+1Ch] [ebp-28h]
  int v39; // [esp+20h] [ebp-24h]
  unsigned __int8 v40; // [esp+24h] [ebp-20h]
  unsigned __int8 v41; // [esp+28h] [ebp-1Ch]
  unsigned __int8 v42; // [esp+2Ch] [ebp-18h]

  v36 = a1;
  v34 = a2;
  v39 = Lexer_PeekChar(a1, a3);
  v3 = 0;
  v37 = 0;
  v35 = 1;
  v4 = IsTable[(unsigned __int8)(v39 + 1)];
  v5 = g_TokenLen + 80;
  if ( (v4 & 0x20) != 0 )
  {
    v3 = 1;
    v8 = v35;
    v7 = (char *)g_TokenBuf;
    goto LABEL_5;
  }
  v6 = v39;
  if ( v39 == 43 || v39 == 45 )
  {
    v7 = (char *)g_TokenBuf;
    v5 = g_TokenLen + 80;
    v8 = 1;
LABEL_5:
    v9 = 0;
    appended = Str_AppendCharEscaping(v39, v7, (unsigned int *)&g_TokenLen, &g_TokenCap, v5);
    goto LABEL_6;
  }
  if ( v39 == 46 )
  {
    v9 = 1;
    v37 = 1;
    v8 = v35;
    appended = Str_AppendCharEscaping(46, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
    goto LABEL_6;
  }
  if ( v39 != 69 && v39 != 101 )
  {
    if ( v39 != 60
      && v39 != 34
      && v39 != 40
      && v39 != 41
      && v39 != 38
      && v39 != 124
      && v39 != 126
      && v39 != 32
      && v39 != 59
      && (v4 & 8) != 0 )
    {
      v21 = v35;
      v22 = Str_AppendCharEscaping(v39, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
      goto LABEL_33;
    }
    goto LABEL_18;
  }
  v37 = 1;
  v9 = 2;
  v8 = 1;
  appended = Str_AppendCharEscaping(v39, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
LABEL_6:
  for ( g_TokenBuf = (int)appended; ; g_TokenBuf = (int)v12 )
  {
    v39 = Lexer_PeekChar(v36, v11);
    v40 = v39 + 1;
    v42 = v39 + 1;
    v41 = v39 + 1;
    switch ( v9 )
    {
      case 0:
        if ( (IsTable[v40] & 0x20) == 0 )
        {
          if ( v39 == 46 )
          {
            v9 = 1;
            v37 = 1;
            ++v8;
            appended = Str_AppendCharEscaping(
                         46,
                         (char *)g_TokenBuf,
                         (unsigned int *)&g_TokenLen,
                         &g_TokenCap,
                         g_TokenLen + 80);
            goto LABEL_6;
          }
          if ( v39 == 69 || v39 == 101 )
          {
            v9 = 2;
            v37 = 1;
            ++v8;
            appended = Str_AppendCharEscaping(
                         v39,
                         (char *)g_TokenBuf,
                         (unsigned int *)&g_TokenLen,
                         &g_TokenCap,
                         g_TokenLen + 80);
            goto LABEL_6;
          }
          if ( v39 != 60
            && v39 != 34
            && v39 != 40
            && v39 != 41
            && v39 != 38
            && v39 != 124
            && v39 != 126
            && v39 != 32
            && v39 != 59
            && (IsTable[(unsigned __int8)(v39 + 1)] & 8) != 0 )
          {
            goto LABEL_68;
          }
          goto LABEL_18;
        }
        goto LABEL_9;
      case 1:
        if ( (IsTable[v42] & 0x20) == 0 )
        {
          if ( v39 == 69 || v39 == 101 )
          {
            v9 = 2;
            ++v8;
            appended = Str_AppendCharEscaping(
                         v39,
                         (char *)g_TokenBuf,
                         (unsigned int *)&g_TokenLen,
                         &g_TokenCap,
                         g_TokenLen + 80);
            goto LABEL_6;
          }
          if ( v39 != 60
            && v39 != 34
            && v39 != 40
            && v39 != 41
            && v39 != 38
            && v39 != 124
            && v39 != 126
            && v39 != 32
            && v39 != 59
            && (IsTable[(unsigned __int8)(v39 + 1)] & 8) != 0 )
          {
            goto LABEL_68;
          }
          goto LABEL_18;
        }
LABEL_9:
        v3 = 1;
        ++v8;
        v12 = Str_AppendCharEscaping(v39, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
        continue;
      case 2:
        if ( (IsTable[v41] & 0x20) == 0 && v39 != 43 && v39 != 45 )
        {
          if ( v39 != 60
            && v39 != 34
            && v39 != 40
            && v39 != 41
            && v39 != 38
            && v39 != 124
            && v39 != 126
            && v39 != 32
            && v39 != 59
            && (IsTable[(unsigned __int8)(v39 + 1)] & 8) != 0 )
          {
LABEL_68:
            v21 = v8 + 1;
            v22 = Str_AppendCharEscaping(
                    v39,
                    (char *)g_TokenBuf,
                    (unsigned int *)&g_TokenLen,
                    &g_TokenCap,
                    g_TokenLen + 80);
            goto LABEL_33;
          }
          v3 = 0;
LABEL_18:
          Lexer_SkipChar(v39, v36, v6);
          if ( v3 )
          {
            if ( v37 )
            {
              v32 = strtod((const char *)(uintptr_t)(unsigned int)g_TokenBuf, 0);
              *v34 = 0;
              v29 = Rules_AddDoubleValue(v32);
              *(_DWORD *)((uintptr_t)v34 + 4) = v29;
              result = Rules_FloatToSymbol(*(_DWORD *)((uintptr_t)(unsigned int)v29 + 16), *(double *)((uintptr_t)(unsigned int)v29 + 16));
              *(_DWORD *)((uintptr_t)v34 + 8) = result;
            }
            else
            {
              v14 = Str_ParseSignedInt((char *)g_TokenBuf);
              v15 = v14;
              if ( v14 == 0x7FFFFFFF || v14 == 0x80000000 )
              {
                Rules_PrintWarningID((int)aScanner, 1, 0);
                Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aOverOrUnderflo, v16);
              }
              *v34 = 1;
              v17 = Rules_AddIntegerValue(v15);
              *(_DWORD *)((uintptr_t)v34 + 4) = v17;
              result = Rules_LongIntegerToSymbol(*(_DWORD *)((uintptr_t)(unsigned int)v17 + 16));
              *(_DWORD *)((uintptr_t)v34 + 8) = result;
            }
          }
          else
          {
            *v34 = 2;
            v27 = Str_Intern((char *)(uintptr_t)(unsigned int)g_TokenBuf, 0);
            *(_DWORD *)((uintptr_t)v34 + 4) = v27;
            result = *(_DWORD *)((uintptr_t)(unsigned int)v27 + 16);
            *(_DWORD *)((uintptr_t)v34 + 8) = result;
          }
          return result;
        }
        v9 = 3;
        ++v8;
        appended = Str_AppendCharEscaping(
                     v39,
                     (char *)g_TokenBuf,
                     (unsigned int *)&g_TokenLen,
                     &g_TokenCap,
                     g_TokenLen + 80);
        goto LABEL_6;
    }
    v38 = v8 + 1;
    if ( (IsTable[v41] & 0x20) == 0 )
      break;
    v8 = v38;
    v12 = Str_AppendCharEscaping(v39, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
  }
  v6 = v39;
  if ( v39 == 60
    || v39 == 34
    || v39 == 40
    || v39 == 41
    || v39 == 38
    || v39 == 124
    || v39 == 126
    || v39 == 32
    || v39 == 59
    || (IsTable[v41] & 8) == 0 )
  {
    v26 = *(_BYTE *)(g_TokenBuf + v8 - 1);
    if ( v26 == 43 || v26 == 45 )
      v3 = 0;
    goto LABEL_18;
  }
  v21 = v38;
  v22 = Str_AppendCharEscaping(v39, (char *)g_TokenBuf, (unsigned int *)&g_TokenLen, &g_TokenCap, g_TokenLen + 80);
LABEL_33:
  g_TokenBuf = (int)v22;
  v24 = Lexer_ReadToken(v36, v21, &v33, v23);
  v25 = v34;
  v34[1] = v24;
  *v25 = v33;
  result = *(_DWORD *)(v25[1] + 16);
  v25[2] = result;
  return result;
}
// 493B07: conditional instruction was optimized away because esi.4<4u
// 493B10: conditional instruction was optimized away because esi.4<4u
// 493B19: conditional instruction was optimized away because esi.4<4u
// 493B6B: conditional instruction was optimized away because esi.4 is in (<2u|==3)
// 493B70: conditional instruction was optimized away because esi.4 is in (<2u|==3)
// 493FEC: conditional instruction was optimized away because esi.4==3
// 493AE9: variable 'v11' is possibly undefined
// 493C13: variable 'v6' is possibly undefined
// 493C5D: variable 'v16' is possibly undefined
// 493C72: variable 'v15' is possibly undefined
// 493C77: variable 'v18' is possibly undefined
// 493C82: variable 'v20' is possibly undefined
// 493D0C: variable 'v23' is possibly undefined
// 4940CB: variable 'v13' is possibly undefined
// 4940D0: variable 'v28' is possibly undefined
// 49410E: variable 'v30' is possibly undefined
// 494122: variable 'v31' is possibly undefined
// 4B6AC6: using guessed type double __fastcall strtod_(_DWORD, _DWORD);
// 51A610: using guessed type char *off_51A610[6];
// 51AA00: using guessed type int g_TokenBuf;
// 51AA04: using guessed type int g_TokenLen;
// 51AA08: using guessed type int g_TokenCap;

//----- (00494160) --------------------------------------------------------
signed int  Rules_ExpressionConstraintsCompatible(__int16 *a1)
{
  _BYTE *v1; // ebx
  _BYTE *v2; // eax
  _DWORD *v3; // ecx
  char *v4; // edx
  _DWORD *v5; // edx

  v1 = Rules_BuildLHSNodeFromToken(a1);
  v2 = Rules_ApplyPatternKeywordFlags();
  Rules_IntersectConstraints((int)v1, (int)v2);
  AST_DecrementNodeRefCount(v1);
  AST_DecrementNodeRefCount(v3);
  if ( Rules_ConstraintIsUnmatchable(v4) )
  {
    AST_DecrementNodeRefCount(v5);
    return 1;
  }
  else
  {
    AST_DecrementNodeRefCount(v5);
    return 0;
  }
}
// 494186: variable 'v3' is possibly undefined
// 49418D: variable 'v4' is possibly undefined
// 494198: variable 'v5' is possibly undefined

//----- (00494230) --------------------------------------------------------
signed int  Rules_TagIsConstantType(int a1)
{
  signed int result; // eax

  switch ( a1 )
  {
    case 0:
    case 1:
    case 2:
    case 3:
    case 7:
    case 8:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

//----- (00494250) --------------------------------------------------------
int  AST_NodeListsEqual(__int16 *a1, __int16 *a2)
{
  __int16 *i; // ecx
  int result; // eax
  int v5; // ecx

  for ( i = a1; i; a2 = *(__int16 **)(a2 + 5) )
  {
    if ( !a2 )
      break;
    if ( *i != *a2 || *(_DWORD *)(i + 1) != *(_DWORD *)(a2 + 1) )
      return 0;
    result = AST_NodeListsEqual(*(_DWORD *)(i + 3), *(_DWORD *)(a2 + 3));
    if ( !result )
      return result;
    i = *(__int16 **)(v5 + 10);
  }
  return i == a2;
}
// 49427F: variable 'v5' is possibly undefined

//----- (004942A0) --------------------------------------------------------
int  AST_CountListNodes(uintptr_t a1)
{
  int i; // edx

  for ( i = 0; a1; ++i )
    a1 = (uintptr_t)(unsigned int)*(_DWORD *)(a1 + 10);
  return i;
}

//----- (004942C0) --------------------------------------------------------
signed int  AST_CloneNodeList(signed int result)
{
  signed int v1; // ebx
  signed int v2; // esi
  int v3; // ecx
  int v4; // ecx
  int i; // ecx
  int v6; // ecx
  signed int v7; // eax
  signed int v8; // edx
  int v9; // ecx

  if ( result )
  {
    v1 = AST_NewNode(*(_WORD *)result, *(_DWORD *)(result + 2));
    v2 = v1;
    *(_DWORD *)(v1 + 6) = AST_CloneNodeList(*(_DWORD *)(v3 + 6));
    for ( i = *(_DWORD *)(v4 + 10); i; v1 = v8 )
    {
      AST_NewNode(*(_WORD *)i, *(_DWORD *)(i + 2));
      v7 = AST_CloneNodeList(*(_DWORD *)(v6 + 6));
      *(_DWORD *)(v8 + 6) = v7;
      *(_DWORD *)(v1 + 10) = v8;
      i = *(_DWORD *)(v9 + 10);
    }
    return v2;
  }
  return result;
}
// 4942DB: variable 'v3' is possibly undefined
// 4942E6: variable 'v4' is possibly undefined
// 4942FA: variable 'v6' is possibly undefined
// 494302: variable 'v8' is possibly undefined
// 494308: variable 'v9' is possibly undefined

//----- (00494330) --------------------------------------------------------
signed int  AST_TreeContainsSpecialTag(int a1, int a2)
{
  int v2; // ecx
  __int16 v4; // dx

  v2 = a1;
  if ( !a1 )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( *(_DWORD *)(v2 + 6) && AST_TreeContainsSpecialTag(*(_DWORD *)(v2 + 6), a2) )
        return 1;
      v4 = *(_WORD *)v2;
      if ( *(_WORD *)v2 == 16 || v4 == 15 || v4 == 6 )
        return 1;
      if ( v4 != 13 && v4 != 14 )
        break;
      if ( a2 == 1 )
        return 1;
      v2 = *(_DWORD *)(v2 + 10);
      if ( !v2 )
        return 0;
    }
    v2 = *(_DWORD *)(v2 + 10);
  }
  while ( v2 );
  return 0;
}
// 494341: variable 'v2' is possibly undefined

//----- (004943A0) --------------------------------------------------------
int  AST_CountTreeNodes(int a1)
{
  int node; // edx
  int count; // ecx
  int child_node; // ebx

  node = a1;
  count = 0;
  if ( !a1 )
    return count;
  while ( node )
  {
    ++count;
    child_node = *(_DWORD *)(node + 6);
    if ( child_node )
      count += AST_CountTreeNodes(child_node);
    node = *(_DWORD *)(node + 10);
  }
  return count;
}

