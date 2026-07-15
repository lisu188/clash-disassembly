/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004C0620) --------------------------------------------------------
_BYTE * Rules_SetLHSParseNodeDefaultFlags(_BYTE *result, int justOne)
{
  char restFlagValue; // cl
  int v3; // edx

  if ( justOne )
  {
    LOBYTE(justOne) = 1;
    restFlagValue = 0;
  }
  else
  {
    restFlagValue = 1;
  }
  *result &= ~1u;
  *(_DWORD *)result |= justOne & 1;
  v3 = restFlagValue & 1;
  *result &= ~2u;
  *(_DWORD *)result |= 2 * v3;
  *result &= ~4u;
  *(_DWORD *)result |= 4 * v3;
  *result &= ~8u;
  *(_DWORD *)result |= 8 * v3;
  *result &= ~0x10u;
  *(_DWORD *)result |= 16 * v3;
  *result &= ~0x20u;
  *(_DWORD *)result |= 32 * v3;
  *result &= ~0x40u;
  *(_DWORD *)result |= v3 << 6;
  *result &= ~0x80u;
  *(_DWORD *)result |= v3 << 7;
  result[1] &= ~1u;
  *(_DWORD *)result |= v3 << 8;
  return result;
}

//----- (004C06C0) --------------------------------------------------------
int  Rules_CloneLHSParseNode(int *theConstraint)
{
  int *sourceNode; // ecx
  _DWORD *freeNode; // ebx
  _BYTE *theCopy; // edx
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  signed int restrictionListCopy; // eax
  int v22; // edx
  int v23; // ecx
  signed int minValueCopy; // eax
  int v25; // edx
  int v26; // ecx
  signed int maxValueCopy; // eax
  int v28; // edx
  int v29; // ecx
  signed int minFieldsCopy; // eax
  int v31; // edx
  int v32; // ecx
  signed int maxFieldsCopy; // eax
  int v34; // edx
  int v35; // ecx
  int multifieldCopy; // eax
  int v37; // edx

  sourceNode = theConstraint;
  if ( !theConstraint )
    return 0;
  freeNode = *(_DWORD **)(g_ClipsMemoryTable + 168);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 168);
    *(_DWORD *)(g_ClipsMemoryTable + 168) = *freeNode;
    theCopy = (_BYTE *)g_ClipsMemFreeListTemp;
  }
  else
  {
    theCopy = (_BYTE *)Mem_HeapAllocWithRetry((_DWORD *)0x2A);
  }
  v4 = *sourceNode;
  *theCopy &= ~1u;
  *(_DWORD *)theCopy |= v4 & 1;
  v5 = *sourceNode;
  *theCopy &= ~2u;
  *(_DWORD *)theCopy |= v5 & 2;
  v6 = *sourceNode;
  *theCopy &= ~4u;
  *(_DWORD *)theCopy |= v6 & 4;
  v7 = *sourceNode;
  *theCopy &= ~8u;
  *(_DWORD *)theCopy |= v7 & 8;
  v8 = *sourceNode;
  *theCopy &= ~0x10u;
  *(_DWORD *)theCopy |= v8 & 0x10;
  v9 = *sourceNode;
  *theCopy &= ~0x20u;
  *(_DWORD *)theCopy |= v9 & 0x20;
  v10 = *sourceNode;
  *theCopy &= ~0x40u;
  *(_DWORD *)theCopy |= v10 & 0x40;
  v11 = *sourceNode;
  *theCopy &= ~0x80u;
  *(_DWORD *)theCopy |= v11 & 0x80;
  v12 = *sourceNode;
  theCopy[1] &= ~0x80u;
  *(_DWORD *)theCopy |= v12 & 0x8000;
  v13 = *sourceNode;
  theCopy[2] &= ~1u;
  *(_DWORD *)theCopy |= v13 & 0x10000;
  v14 = *sourceNode;
  theCopy[1] &= ~1u;
  *(_DWORD *)theCopy |= v14 & 0x100;
  v15 = *sourceNode;
  theCopy[1] &= ~2u;
  *(_DWORD *)theCopy |= v15 & 0x200;
  v16 = *sourceNode;
  theCopy[1] &= ~4u;
  *(_DWORD *)theCopy |= v16 & 0x400;
  v17 = *sourceNode;
  theCopy[1] &= ~8u;
  *(_DWORD *)theCopy |= v17 & 0x800;
  v18 = *sourceNode;
  theCopy[1] &= ~0x10u;
  *(_DWORD *)theCopy |= v18 & 0x1000;
  v19 = *sourceNode;
  theCopy[1] &= ~0x20u;
  *(_DWORD *)theCopy |= v19 & 0x2000;
  v20 = *sourceNode;
  theCopy[1] &= ~0x40u;
  *(_DWORD *)theCopy |= v20 & 0x4000;
  restrictionListCopy = AST_CloneNodeList(*(int *)((char *)sourceNode + 6));
  *(_DWORD *)(v22 + 6) = restrictionListCopy;
  minValueCopy = AST_CloneNodeList(*(_DWORD *)(v23 + 10));
  *(_DWORD *)(v25 + 10) = minValueCopy;
  maxValueCopy = AST_CloneNodeList(*(_DWORD *)(v26 + 14));
  *(_DWORD *)(v28 + 14) = maxValueCopy;
  minFieldsCopy = AST_CloneNodeList(*(_DWORD *)(v29 + 18));
  *(_DWORD *)(v31 + 18) = minFieldsCopy;
  maxFieldsCopy = AST_CloneNodeList(*(_DWORD *)(v32 + 22));
  *(_DWORD *)(v34 + 34) = -1;
  *(_DWORD *)(v34 + 38) = 0;
  *(_DWORD *)(v34 + 22) = maxFieldsCopy;
  multifieldCopy = Rules_CloneLHSParseNode(*(_DWORD *)(v35 + 26));
  *(_DWORD *)(v37 + 30) = 0;
  *(_DWORD *)(v37 + 26) = multifieldCopy;
  return v37;
}
// 4C06FA: variable 'v1' is possibly undefined
// 4C0811: variable 'v22' is possibly undefined
// 4C0814: variable 'v23' is possibly undefined
// 4C081C: variable 'v25' is possibly undefined
// 4C081F: variable 'v26' is possibly undefined
// 4C0827: variable 'v28' is possibly undefined
// 4C082A: variable 'v29' is possibly undefined
// 4C0832: variable 'v31' is possibly undefined
// 4C0835: variable 'v32' is possibly undefined
// 4C083D: variable 'v34' is possibly undefined
// 4C084E: variable 'v35' is possibly undefined
// 4C0856: variable 'v37' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C0880) --------------------------------------------------------
int  Rules_SetLHSParseNodeExtendedFlags(int result, int justOne)
{
  char restFlagValue; // cl

  if ( justOne )
  {
    LOBYTE(justOne) = 1;
    restFlagValue = 0;
  }
  else
  {
    restFlagValue = 1;
  }
  *(_BYTE *)(result + 1) &= ~2u;
  *(_DWORD *)result |= (justOne & 1) << 9;
  *(_BYTE *)(result + 1) &= ~4u;
  *(_DWORD *)result |= (restFlagValue & 1) << 10;
  *(_BYTE *)(result + 1) &= ~8u;
  *(_DWORD *)result |= (restFlagValue & 1) << 11;
  *(_BYTE *)(result + 1) &= ~0x10u;
  *(_DWORD *)result |= (restFlagValue & 1) << 12;
  *(_BYTE *)(result + 1) &= ~0x20u;
  *(_DWORD *)result |= (restFlagValue & 1) << 13;
  *(_BYTE *)(result + 1) &= ~0x40u;
  *(_DWORD *)result |= (restFlagValue & 1) << 14;
  return result;
}

//----- (004C0900) --------------------------------------------------------
signed int  Rules_UpdateCETypeFlag(unsigned int theType, int constraints)
{
  int returnValue; // ecx
  int anyAllowedFlag; // ecx

  returnValue = 1;
  if ( theType >= 6 )
  {
    if ( theType > 6 )
    {
      if ( theType >= 0x67 )
      {
        if ( theType <= 0x67 )
        {
          anyAllowedFlag = *(_DWORD *)constraints & 1;
          *(_BYTE *)constraints |= 1u;
          return anyAllowedFlag;
        }
        if ( theType >= 0x6F )
        {
          if ( theType > 0x6F )
          {
            if ( theType == 112 )
            {
              returnValue = (*(_DWORD *)constraints << 26 >> 31) | (*(_DWORD *)constraints << 25 >> 31);
              *(_BYTE *)constraints |= 0x60u;
            }
          }
          else
          {
            returnValue = (*(_DWORD *)constraints << 29 >> 31) | (*(_DWORD *)constraints << 30 >> 31);
            *(_BYTE *)constraints |= 6u;
          }
        }
        else if ( theType == 110 )
        {
          returnValue = (*(_DWORD *)constraints << 28 >> 31) | (*(_DWORD *)constraints << 27 >> 31);
          *(_BYTE *)constraints |= 0x18u;
        }
      }
      else if ( theType > 7 )
      {
        if ( theType == 8 )
        {
          returnValue = *(_DWORD *)constraints << 26 >> 31;
          *(_BYTE *)constraints |= 0x20u;
        }
      }
      else
      {
        returnValue = *(_DWORD *)constraints << 25 >> 31;
        *(_BYTE *)constraints |= 0x40u;
      }
    }
    else
    {
      returnValue = *(_DWORD *)constraints << 23 >> 31;
      *(_BYTE *)(constraints + 1) |= 1u;
    }
  }
  else if ( theType >= 2 )
  {
    if ( theType > 2 )
    {
      if ( theType >= 4 )
      {
        if ( theType > 4 )
        {
          returnValue = *(_DWORD *)constraints << 24 >> 31;
          *(_BYTE *)constraints |= 0x80u;
        }
        else
        {
          returnValue = *(_DWORD *)constraints << 16 >> 31;
          *(_BYTE *)(constraints + 1) |= 0x80u;
        }
      }
      else
      {
        returnValue = *(_DWORD *)constraints << 29 >> 31;
        *(_BYTE *)constraints |= 4u;
      }
    }
    else
    {
      returnValue = *(_DWORD *)constraints << 30 >> 31;
      *(_BYTE *)constraints |= 2u;
    }
  }
  else if ( theType )
  {
    returnValue = *(_DWORD *)constraints << 27 >> 31;
    *(_BYTE *)constraints |= 0x10u;
  }
  else
  {
    returnValue = *(_DWORD *)constraints << 28 >> 31;
    *(_BYTE *)constraints |= 8u;
  }
  *(_BYTE *)constraints &= ~1u;
  return returnValue;
}
// 4C092F: conditional instruction was optimized away because eax.4 is in (==1|9..66|68..6D|>=71u)
// 4C0950: conditional instruction was optimized away because eax.4==6
// 4C097B: conditional instruction was optimized away because eax.4==7
// 4C0997: conditional instruction was optimized away because eax.4==67
// 4C09E9: conditional instruction was optimized away because eax.4==6F
// 4C0A5A: conditional instruction was optimized away because eax.4==2
// 4C0A7C: conditional instruction was optimized away because eax.4==3
// 4C0A99: conditional instruction was optimized away because eax.4==4
// 4C0ACB: conditional instruction was optimized away because eax.4==5

//----- (004C0AE0) --------------------------------------------------------
signed int  Rules_CompareBoundedCEValues(int type1, int value1, int value2, int type2)
{
  int intValue1; // eax
  int intValue2; // edi
  double convertedValue1; // st7
  double floatValue1; // st7
  double convertedValue2; // [esp+0h] [ebp-18h]

  if ( value1 == value2 )
    return 2;
  if ( value1 == g_ClipsPositiveInfinitySymbol )
    return 1;
  if ( value1 == g_Clips_NegativeInfinitySymbol || value2 == g_ClipsPositiveInfinitySymbol )
    return 0;
  if ( value2 == g_Clips_NegativeInfinitySymbol )
    return 1;
  if ( type1 == 1 && type2 == 1 )
  {
    intValue1 = *(_DWORD *)(value1 + 16);
    intValue2 = *(_DWORD *)(value2 + 16);
    if ( intValue1 >= intValue2 )
    {
      if ( intValue1 > intValue2 )
        return 1;
      return 2;
    }
    return 0;
  }
  if ( !type1 && !type2 )
  {
    if ( *(double *)(value1 + 16) >= *(double *)(value2 + 16) )
    {
      if ( *(double *)(value1 + 16) > *(double *)(value2 + 16) )
        return 1;
      return 2;
    }
    return 0;
  }
  if ( type1 != 1 || type2 )
  {
    if ( type1 || type2 != 1 )
    {
      return -1;
    }
    else
    {
      convertedValue2 = (double)*(int *)(value2 + 16);
      floatValue1 = *(double *)(value1 + 16);
      if ( floatValue1 < convertedValue2 )
        return 0;
      if ( floatValue1 > convertedValue2 )
        return 1;
      return 2;
    }
  }
  else
  {
    convertedValue1 = (double)*(int *)(value1 + 16);
    if ( convertedValue1 < *(double *)(value2 + 16) )
      return 0;
    if ( convertedValue1 <= *(double *)(value2 + 16) )
      return 2;
    return 1;
  }
}
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004C0BC0) --------------------------------------------------------
_BYTE * Rules_BuildLHSNodeFromToken(__int16 *theExpression)
{
  __int16 exprType; // bx
  _BYTE *constraints; // eax
  int tokenPtr; // edx
  char v4; // bl
  __int16 valueType; // si
  _BYTE *v6; // ecx
  char v7; // al
  signed int restrictionExpr; // eax
  int v9; // ecx
  _BYTE *result; // eax

  if ( theExpression )
  {
    exprType = *theExpression;
    if ( *theExpression == 15 || exprType == 16 || exprType == 11 || exprType == 12 || exprType == 13 || exprType == 14 )
    {
      result = (_BYTE *)Rules_CreateLHSParseNode();
      result[1] |= 0x80u;
    }
    else if ( exprType == 10 )
    {
      return Rules_ApplyCEKeywordFlags();
    }
    else
    {
      constraints = (_BYTE *)Rules_CreateLHSParseNode();
      v4 = *constraints & 0xFE;
      *constraints = v4;
      valueType = *(_WORD *)tokenPtr;
      v6 = constraints;
      if ( *(_WORD *)tokenPtr )
      {
        switch ( valueType )
        {
          case 1:
            *(_WORD *)constraints |= 0x2010u;
            break;
          case 2:
            *(_WORD *)constraints |= 0x402u;
            break;
          case 3:
            *(_WORD *)constraints |= 0x804u;
            break;
          case 8:
            *(_WORD *)constraints |= 0x4020u;
            break;
          case 7:
            *constraints = v4 | 0x40;
            break;
        }
      }
      else
      {
        *(_WORD *)constraints |= 0x1008u;
      }
      v7 = *constraints;
      if ( (*v6 & 8) != 0 || (v7 & 0x10) != 0 || (v7 & 2) != 0 || (v7 & 4) != 0 || (v7 & 0x20) != 0 )
      {
        restrictionExpr = AST_NewNode(*(_WORD *)tokenPtr, *(_DWORD *)(tokenPtr + 2));
        *(_DWORD *)(v9 + 6) = restrictionExpr;
        return (_BYTE *)v9;
      }
      else
      {
        return v6;
      }
    }
  }
  else
  {
    result = (_BYTE *)Rules_CreateLHSParseNode();
    *result &= ~1u;
  }
  return result;
}
// 4C0C0F: variable 'v3' is possibly undefined
// 4C0C37: variable 'v9' is possibly undefined

//----- (004C0D30) --------------------------------------------------------
_BYTE *Rules_ApplyCEKeywordFlags()
{
  _BYTE *result; // eax
  int theFunction; // ecx

  result = (_BYTE *)Rules_CreateLHSParseNode();
  *result &= ~1u;
  if ( (unsigned __int8)(*(_BYTE *)(theFunction + 8) - 97) <= 0x17u )
  {
    switch ( *(_BYTE *)(theFunction + 8) )
    {
      case 'a':
        *result |= 0x80u;
        break;
      case 'b':
      case 'c':
      case 'w':
        *result |= 2u;
        break;
      case 'd':
      case 'f':
        *result |= 8u;
        break;
      case 'e':
      case 'g':
      case 'h':
      case 'p':
      case 'q':
      case 'r':
      case 't':
      case 'v':
        return result;
      case 'i':
      case 'l':
        *result |= 0x10u;
        break;
      case 'j':
        *result |= 0x26u;
        break;
      case 'k':
        *result |= 6u;
        break;
      case 'm':
        *(_DWORD *)result &= 0xFFFE7FFF;
        result[1] |= 0x80u;
        break;
      case 'n':
        *result |= 0x18u;
        break;
      case 'o':
        *result |= 0x20u;
        break;
      case 's':
        *result |= 4u;
        break;
      case 'u':
        *(_WORD *)result |= 0x8001u;
        break;
      case 'x':
        *result |= 0x40u;
        break;
    }
  }
  return result;
}
// 4C0D3D: variable 'v1' is possibly undefined

//----- (004C0E40) --------------------------------------------------------
_BYTE *Rules_ApplyPatternKeywordFlags()
{
  _BYTE *result; // eax
  char clearedFlags; // bl
  int restrictionCode; // ecx

  result = (_BYTE *)Rules_CreateLHSParseNode();
  clearedFlags = *result & 0xFE;
  *result = clearedFlags;
  switch ( restrictionCode )
  {
    case 'a':
      *result = clearedFlags | 0x80;
      break;
    case 'd':
    case 'f':
      *result |= 8u;
      break;
    case 'e':
      *result = clearedFlags | 0x62;
      break;
    case 'g':
      *result = clearedFlags | 0x1A;
      break;
    case 'h':
      *(_WORD *)result |= 0x172u;
      break;
    case 'i':
    case 'l':
      *result |= 0x10u;
      break;
    case 'j':
      *result = clearedFlags | 0x26;
      break;
    case 'k':
      *result = clearedFlags | 6;
      break;
    case 'm':
      *(_DWORD *)result &= 0xFFFE7FFF;
      result[1] |= 0x80u;
      break;
    case 'n':
      *result = clearedFlags | 0x18;
      break;
    case 'o':
      *result = clearedFlags | 0x20;
      break;
    case 'p':
      *result = clearedFlags | 0x22;
      break;
    case 'q':
      *(_WORD *)result |= 0x8006u;
      break;
    case 's':
      *result = clearedFlags | 4;
      break;
    case 'u':
      *(_WORD *)result |= 0x8001u;
      break;
    case 'w':
      *result = clearedFlags | 2;
      break;
    case 'x':
      *result = clearedFlags | 0x40;
      break;
    case 'y':
      result[1] |= 1u;
      break;
    case 'z':
      *(_WORD *)result |= 0x112u;
      break;
    default:
      return result;
  }
  return result;
}
// 4C0E5B: variable 'v2' is possibly undefined

//----- (004C0F50) --------------------------------------------------------
int Module_RegisterDefmoduleCommands()
{
  int v0; // ecx

  Rules_AddClearFunction((int)aDefmodule_0, (int)Module_ClearAllModulesResetToMain, 2000);
  Rules_AddSaveFunction((int)aDefmodule_0, (int)Module_SaveAllPPFormsToFile, 1100);
  Rules_RegisterHostFunction(aGetDefmoduleLi, 109, v0, (int)Module_GetDefmoduleNameListCommand, (int)a00_10);
  Rules_RegisterHostFunction(aListDefmodules, 118, (int)aListdefmodules, (int)Module_ListDefmodulesCommand, (int)a00_10);
  Rules_RegisterHostFunction(aPpdefmodule, 118, (int)aPpdefmodulecom, (int)Module_PPDefmoduleCommand, (int)a11w_9);
  Module_RegisterBsaveBloadHandlers();
  return Compiler_RegisterModuleCodeItem();
}
// 4C0F94: variable 'v0' is possibly undefined
// 4C0FF0: using guessed type int sub_4C0FF0();

//----- (004C0FF0) --------------------------------------------------------
int Module_ClearAllModulesResetToMain()
{
  int result; // eax

  result = Rules_IsBloaded();
  if ( result != 1 )
  {
    Module_RemoveAllModules();
    result = Module_CreateMainModule();
    g_Module_MainRedefinable = 1;
  }
  return result;
}
// 4C0FF0: using guessed type int sub_4C0FF0();
// 51A9C4: using guessed type int dword_51A9C4;

//----- (004C1020) --------------------------------------------------------
int  Module_SaveAllPPFormsToFile(signed int logicalName)
{
  int result; // eax
  int i; // ecx
  char *ppForm; // eax
  int v5; // ecx
  int v6; // ecx

  result = Module_NextEnum(0);
  for ( i = result; result; i = result )
  {
    ppForm = (char *)Module_GetPPForm(i);
    if ( ppForm )
    {
      Output_WriteLongString(logicalName, ppForm);
      Output_Write(logicalName, (int)asc_50ABFC, v6);
    }
    result = Module_NextEnum(v5);
  }
  return result;
}
// 4C104D: variable 'v6' is possibly undefined
// 4C1054: variable 'v5' is possibly undefined

//----- (004C1070) --------------------------------------------------------
_DWORD * Module_GetDefmoduleNameListCommand(_DWORD *returnValue)
{
  return Module_BuildNameListMultifield(returnValue, (int (*)(void))Module_NextEnum, (int (*)(void))Module_GetName);
}

//----- (004C1090) --------------------------------------------------------
_BYTE * Module_PPDefmoduleCommand(int a1, double a2)
{
  _BYTE *result; // eax

  result = (_BYTE *)Rules_GetConstructNameArg((int)aDefmoduleNam_3, a1, a2);
  if ( result )
    return (_BYTE *)Module_PrintPPFormByName(result, (signed int)g_IO_LogicalName_WDisplay);
  return result;
}
// 51A624: using guessed type char *off_51A624;

//----- (004C10C0) --------------------------------------------------------
signed int  Module_PrintPPFormByName(_BYTE *defmoduleName, signed int logicalName)
{
  int *theModule; // eax
  int v4; // ecx
  int v5; // edx
  char *ppForm; // eax

  theModule = Module_FindByName(defmoduleName);
  if ( theModule )
  {
    if ( Module_GetPPForm((int)theModule) )
    {
      ppForm = (char *)Module_GetPPForm(v5);
      Output_WriteLongString(logicalName, ppForm);
    }
    return 1;
  }
  else
  {
    Rules_ReportCantFindItem(v4, v4);
    return 0;
  }
}
// 4C10F5: variable 'v5' is possibly undefined
// 4C10E9: variable 'v4' is possibly undefined

//----- (004C1110) --------------------------------------------------------
int Module_ListDefmodulesCommand()
{
  int result; // eax

  result = Lexer_TokenExpect(0);
  if ( result != -1 )
    return Module_PrintAllNamesWithTally((int)g_IO_LogicalName_WDisplay);
  return result;
}
// 51A624: using guessed type char *off_51A624;

//----- (004C1140) --------------------------------------------------------
int  Module_PrintAllNamesWithTally(int logicalName)
{
  int moduleCount; // edi
  int i; // ecx
  int Name; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx

  moduleCount = 0;
  for ( i = Module_NextEnum(0); i; i = Module_NextEnum(v7) )
  {
    Name = Module_GetName(i);
    Output_Write(logicalName, Name, v5);
    Output_Write(logicalName, (int)asc_50ABFC, v6);
    ++moduleCount;
  }
  return Rules_PrintTally(logicalName, moduleCount, (int)aDefmodules_0, (int)aDefmodule_0);
}
// 4C1161: variable 'v5' is possibly undefined
// 4C116D: variable 'v6' is possibly undefined
// 4C1175: variable 'v7' is possibly undefined

//----- (004C11A0) --------------------------------------------------------
int Module_GetModuleCount()
{
  return g_Module_DefModuleCount;
}
// 54E888: using guessed type int dword_54E888;

//----- (004C11B0) --------------------------------------------------------
int  Module_SetModuleCount(int result)
{
  g_Module_DefModuleCount = result;
  return result;
}
// 54E888: using guessed type int dword_54E888;

//----- (004C11C0) --------------------------------------------------------
_DWORD * Module_AddAfterModuleDefinedCallback(int name, int func, int priority)
{
  _DWORD *result; // eax

  result = Rules_InsertPriorityCallbackReturningHead(name, priority, g_Module_AfterDefineCallbackList, func);
  g_Module_AfterDefineCallbackList = (int)result;
  return result;
}
// 51B36C: using guessed type int dword_51B36C;

//----- (004C11E0) --------------------------------------------------------
int * Module_RegisterImportExportConstructType(int theName, int theType)
{
  int v2; // ecx
  _DWORD *freeNode; // ebx
  int *result; // eax

  v2 = theName;
  freeNode = *(_DWORD **)(g_ClipsMemoryTable + 48);
  if ( freeNode )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 48);
    *(_DWORD *)(g_ClipsMemoryTable + 48) = *freeNode;
    result = (int *)g_ClipsMemFreeListTemp;
  }
  else
  {
    result = (int *)Mem_HeapAllocWithRetry((_DWORD *)0xC);
  }
  *result = v2;
  result[1] = theType;
  result[2] = g_Module_PortConstructList;
  g_Module_PortConstructList = (int)result;
  return result;
}
// 4C1200: variable 'v2' is possibly undefined
// 51B368: using guessed type int dword_51B368;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C1230) --------------------------------------------------------
signed int  Module_ParseDefmoduleConstruct(int readSource)
{
  int *redefiningMainModule; // ebp
  int moduleNameString; // ecx
  int moduleName; // ebx
  _DWORD *freeNode; // edx
  int *newDefmodule; // eax
  int v7; // ecx
  signed int parseError; // edx
  _DWORD *theDefmodule; // ecx
  _DWORD *importSpec; // eax
  int nextImportSpec; // ebx
  _DWORD *exportSpec; // edx
  int nextExportSpec; // ebx
  _DWORD *i; // eax
  int importTypeSym; // edi
  int importNameSym; // esi
  _DWORD *j; // eax
  int exportTypeSym; // edx
  int exportNameSym; // esi
  int v21; // ecx
  int moduleIndex; // eax
  int k; // edx
  int v24; // edx
  _DWORD *itemsArray; // eax
  int v26; // ecx
  int itemIndex; // esi
  int itemDescriptor; // edx
  int arrayOffset; // ebx
  int newItemHeader; // eax
  _DWORD *itemHeaderPtr; // eax
  char *ppForm; // eax
  _DWORD inputToken[8]; // [esp+0h] [ebp-20h] BYREF

  Rules_SetPPBufferStatus(1);
  Rules_FlushPPBuffer();
  Rules_SetIndentDepth(3);
  redefiningMainModule = 0;
  IO_OutWriteToken(aDefmodule_6);
  if ( Rules_IsBloaded() == 1 )
  {
    Rules_ReportCannotLoadWithBload();
    return 1;
  }
  moduleName = Rules_GetConstructNameAndComment(readSource, (int)inputToken, (int (*)(void))Module_FindByName, aDefmodule_7, (int (*)(void))Module_IsRedefinitionOfExistingName, asc_50AC34, 1, 1, 0);
  if ( !moduleName )
    return 1;
  if ( !strcmp_(moduleNameString, aMain_3) )
    redefiningMainModule = Module_FindByName(aMain_3);
  if ( redefiningMainModule )
  {
    v7 = (int)redefiningMainModule;
  }
  else
  {
    freeNode = *(_DWORD **)(g_ClipsMemoryTable + 128);
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(g_ClipsMemoryTable + 128) = *freeNode;
      newDefmodule = (int *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newDefmodule = (int *)Mem_HeapAllocWithRetry((_DWORD *)0x20);
    }
    newDefmodule[7] = 0;
    v7 = (int)newDefmodule;
    *newDefmodule = moduleName;
  }
  *(_DWORD *)(v7 + 12) = 0;
  *(_DWORD *)(v7 + 16) = 0;
  parseError = Module_ParseImportExportClauseList(readSource, inputToken, v7);
  if ( !parseError )
    parseError = Rules_FindMultiImportConflict((int)theDefmodule);
  if ( parseError )
  {
    while ( 1 )
    {
      importSpec = (_DWORD *)theDefmodule[3];
      if ( !importSpec )
        break;
      nextImportSpec = importSpec[3];
      g_ClipsMemFreeListTemp = theDefmodule[3];
      *importSpec = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
      theDefmodule[3] = nextImportSpec;
    }
    while ( 1 )
    {
      exportSpec = (_DWORD *)theDefmodule[4];
      if ( !exportSpec )
        break;
      nextExportSpec = exportSpec[3];
      g_ClipsMemFreeListTemp = theDefmodule[4];
      *exportSpec = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
      theDefmodule[4] = nextExportSpec;
    }
    if ( !redefiningMainModule )
    {
      g_ClipsMemFreeListTemp = (int)theDefmodule;
      *theDefmodule = *(_DWORD *)(g_ClipsMemoryTable + 128);
      *(_DWORD *)(g_ClipsMemoryTable + 128) = g_ClipsMemFreeListTemp;
      return 1;
    }
    return 1;
  }
  if ( redefiningMainModule )
  {
    if ( theDefmodule[3] || theDefmodule[4] )
      g_Module_MainRedefinable = 0;
  }
  else
  {
    ++*(_DWORD *)(*theDefmodule + 4);
  }
  for ( i = (_DWORD *)theDefmodule[3]; i; i = (_DWORD *)i[3] )
  {
    if ( *i )
      ++*(_DWORD *)(*i + 4);
    importTypeSym = i[1];
    if ( importTypeSym )
      ++*(_DWORD *)(importTypeSym + 4);
    importNameSym = i[2];
    if ( importNameSym )
      ++*(_DWORD *)(importNameSym + 4);
  }
  for ( j = (_DWORD *)theDefmodule[4]; j; j = (_DWORD *)j[3] )
  {
    if ( *j )
      ++*(_DWORD *)(*j + 4);
    exportTypeSym = j[1];
    if ( exportTypeSym )
      ++*(_DWORD *)(exportTypeSym + 4);
    exportNameSym = j[2];
    if ( exportNameSym )
      ++*(_DWORD *)(exportNameSym + 4);
  }
  if ( !redefiningMainModule )
  {
    if ( g_ClipsModuleItemCount )
    {
      itemsArray = Mem_SmallBlockAlloc(4 * g_ClipsModuleItemCount);
      *(_DWORD *)(v26 + 8) = itemsArray;
      itemIndex = 0;
      itemDescriptor = g_ModuleItemDescriptorListHead;
      if ( g_ClipsModuleItemCount > 0 )
      {
        arrayOffset = 0;
        do
        {
          if ( !itemDescriptor )
            break;
          if ( *(_DWORD *)(itemDescriptor + 8) )
          {
            newItemHeader = (*(int (**)(void))(itemDescriptor + 8))();
            *(_DWORD *)(*(_DWORD *)(v26 + 8) + arrayOffset) = newItemHeader;
            itemHeaderPtr = *(_DWORD **)(arrayOffset + *(_DWORD *)(v26 + 8));
            itemHeaderPtr[1] = 0;
            itemHeaderPtr[2] = 0;
            *itemHeaderPtr = v26;
          }
          else
          {
            *(_DWORD *)(arrayOffset + *(_DWORD *)(v26 + 8)) = 0;
          }
          arrayOffset += 4;
          ++itemIndex;
          itemDescriptor = *(_DWORD *)(itemDescriptor + 28);
        }
        while ( itemIndex < g_ClipsModuleItemCount );
      }
    }
    else
    {
      theDefmodule[2] = 0;
    }
  }
  IO_OutWriteToken(asc_50AC40);
  if ( Mem_GetAllocFlag() == 1 )
  {
    *(_DWORD *)(v21 + 4) = 0;
  }
  else
  {
    ppForm = Rules_CopyPPBuffer();
    *(_DWORD *)(v21 + 4) = ppForm;
  }
  if ( !redefiningMainModule )
  {
    if ( g_ClipsDefmoduleListTail )
      *(_DWORD *)(g_ClipsDefmoduleListTail + 28) = v21;
    else
      g_DefmoduleListHead = v21;
    moduleIndex = g_Module_DefModuleCount;
    g_ClipsDefmoduleListTail = v21;
    ++g_Module_DefModuleCount;
    *(_DWORD *)(v21 + 24) = moduleIndex;
  }
  Module_SetCurrent(v21);
  for ( k = g_Module_AfterDefineCallbackList; k; k = *(_DWORD *)(v24 + 12) )
    (*(void (**)(void))(k + 4))();
  return 0;
}
// 4C12A3: variable 'v3' is possibly undefined
// 4C1309: variable 'v9' is possibly undefined
// 4C1466: variable 'v21' is possibly undefined
// 4C14B0: variable 'v24' is possibly undefined
// 4C1507: variable 'v26' is possibly undefined
// 4C1540: variable 'v28' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9AC: using guessed type int dword_51A9AC;
// 51A9B4: using guessed type int dword_51A9B4;
// 51A9B8: using guessed type int dword_51A9B8;
// 51A9BC: using guessed type int dword_51A9BC;
// 51A9C4: using guessed type int dword_51A9C4;
// 51B36C: using guessed type int dword_51B36C;
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
// 54E888: using guessed type int dword_54E888;

//----- (004C1590) --------------------------------------------------------
int  Module_IsRedefinitionOfExistingName(int theDefmodule)
{
  int v1; // edx
  int v2; // ecx

  Module_GetName(theDefmodule);
  if ( !strcmp_(v2, v1) )
    return g_Module_MainRedefinable;
  else
    return 0;
}
// 4C159B: variable 'v2' is possibly undefined
// 4C159B: variable 'v1' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A9C4: using guessed type int dword_51A9C4;

//----- (004C15B0) --------------------------------------------------------
signed int  Module_ParseImportExportClauseList(int readSource, _DWORD *theToken, int newModule)
{
  int v5; // ecx
  int v6; // ecx
  int error; // eax
  int v8; // edx
  int v9; // ecx

  *(_DWORD *)(newModule + 12) = 0;
  *(_DWORD *)(newModule + 16) = 0;
  if ( *theToken == 101 )
    return 0;
  while ( *theToken == 100 )
  {
    Parser_NextToken(readSource, (int)theToken);
    if ( *theToken != 2 )
      break;
    if ( !strcmp_(v5, aImport) )
    {
      error = Module_ParseImportClause(readSource, theToken, newModule);
    }
    else
    {
      if ( strcmp_(v6, aExport) )
        break;
      error = Module_ParsePortItemSpecList(readSource, (int)theToken, 0, newModule);
    }
    if ( error )
      return 1;
    AST_Append(v9, v8);
    Parser_NextToken(readSource, (int)theToken);
    if ( *theToken == 101 )
    {
      IO_OutNewline();
      IO_OutNewline();
      IO_OutWriteToken(asc_50AC54);
    }
    if ( *theToken == 101 )
      return 0;
  }
  Parser_ReportSyntaxError();
  return 1;
}
// 4C15EB: variable 'v5' is possibly undefined
// 4C1603: variable 'v9' is possibly undefined
// 4C1603: variable 'v8' is possibly undefined
// 4C1655: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004C1670) --------------------------------------------------------
int  Module_ParseImportClause(int readSource, _DWORD *theToken, int newModule)
{
  int v4; // edx
  int *theModule; // eax
  int v6; // ecx
  int *sourceModule; // esi
  int newImportSpec; // eax
  _DWORD *theExport; // eax
  int found; // edx
  int exportType; // ecx
  int v12; // edx
  char *errorConstructName; // ebx
  int Name; // eax
  int newImport; // esi
  int importConstructName; // ebp
  int exportConstructName; // ecx
  _DWORD *theImport; // esi
  int *importModule; // edi
  _DWORD *v21; // ecx
  char *failedConstructName; // ebx
  int importModuleName; // eax
  int oldImportSpec; // [esp+4h] [ebp-1Ch]
  int *savedModule; // [esp+Ch] [ebp-14h]

  IO_OutWriteToken(asc_50AC58);
  Parser_NextToken(readSource, v4);
  if ( *theToken != 2 )
  {
    Parser_ReportSyntaxError();
    return 1;
  }
  theModule = Module_FindByName(*(_BYTE **)(theToken[1] + 16));
  sourceModule = theModule;
  savedModule = theModule;
  if ( !theModule )
  {
    Rules_ReportCantFindItem(v6, *(_DWORD *)(theToken[1] + 16));
    return 1;
  }
  if ( !theModule[4] )
  {
    errorConstructName = 0;
LABEL_16:
    Name = Module_GetName((int)theModule);
    Rules_ReportConstructNotExported(Name, errorConstructName);
    return 1;
  }
  oldImportSpec = *(_DWORD *)(newModule + 12);
  if ( Module_ParsePortItemSpecList(readSource, (int)theToken, theModule, newModule) )
    return 1;
  newImportSpec = *(_DWORD *)(newModule + 12);
  if ( newImportSpec == oldImportSpec )
    return oldImportSpec ^ newImportSpec;
  if ( *(_DWORD *)(newImportSpec + 4) )
  {
    theExport = (_DWORD *)sourceModule[4];
    found = 0;
    while ( theExport )
    {
      if ( found )
        break;
      exportType = theExport[1];
      if ( exportType )
      {
        newImport = *(_DWORD *)(newModule + 12);
        if ( exportType != *(_DWORD *)(newImport + 4) )
          continue;
        importConstructName = *(_DWORD *)(newImport + 8);
        if ( importConstructName )
        {
          exportConstructName = theExport[2];
          if ( exportConstructName )
          {
            if ( exportConstructName != importConstructName )
              continue;
          }
        }
      }
      found = 1;
      theExport = (_DWORD *)theExport[3];
    }
    if ( !found )
    {
      v12 = *(_DWORD *)(*(_DWORD *)(newModule + 12) + 8);
      if ( v12 )
        errorConstructName = *(char **)(v12 + 16);
      else
        errorConstructName = 0;
      theModule = savedModule;
      goto LABEL_16;
    }
  }
  Module_BeginEnum();
  Module_SetCurrent(newModule);
  theImport = *(_DWORD **)(newModule + 12);
  if ( theImport )
  {
    while ( 1 )
    {
      if ( theImport[1] )
      {
        if ( theImport[2] )
        {
          importModule = Module_FindByName(*(_BYTE **)(*theImport + 16));
          Module_SetCurrent((int)importModule);
          if ( !Rules_FindImportExportConstruct(*(char **)(theImport[1] + 16), v21, *(_BYTE **)(theImport[2] + 16), 1, 0) )
            break;
        }
      }
      theImport = (_DWORD *)theImport[3];
      if ( !theImport )
        goto LABEL_31;
    }
    failedConstructName = *(char **)(theImport[2] + 16);
    importModuleName = Module_GetName((int)importModule);
    Rules_ReportConstructNotExported(importModuleName, failedConstructName);
    Module_EndEnum();
    return 1;
  }
  else
  {
LABEL_31:
    Module_EndEnum();
    return 0;
  }
}
// 4C168D: variable 'v4' is possibly undefined
// 4C1760: variable 'v6' is possibly undefined
// 4C17FA: variable 'v21' is possibly undefined

//----- (004C1830) --------------------------------------------------------
int  Module_ParsePortItemSpecList(int readSource, int theToken, int *importModule, int newModule)
{
  int moduleName; // ebp
  int v7; // ecx
  int v8; // ecx
  _DWORD *v9; // edx
  _DWORD *newPort; // eax
  int v11; // ecx
  _DWORD *v12; // eax
  int v13; // ecx
  int v14; // ecx
  int v16; // ecx
  _DWORD *v17; // eax
  int v18; // ecx
  _DWORD *typePortItem; // [esp+4h] [ebp-1Ch]
  _DWORD *allPortItem; // [esp+8h] [ebp-18h]
  int thePortConstruct; // [esp+Ch] [ebp-14h]
  int constructTypeSym; // [esp+10h] [ebp-10h]

  if ( importModule )
    moduleName = *importModule;
  else
    moduleName = 0;
  IO_OutWriteToken(asc_50AC58);
  Parser_NextToken(readSource, theToken);
  if ( *(_DWORD *)theToken == 15 )
  {
    if ( !strcmp_(v7, aAll) )
    {
      if ( *(_DWORD *)(g_ClipsMemoryTable + 64) )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(g_ClipsMemoryTable + 64) = *(_DWORD *)g_ClipsMemFreeListTemp;
        v12 = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        v12 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
      }
      v12[1] = 0;
      v12[2] = 0;
      v12[3] = 0;
      allPortItem = v12;
      *v12 = moduleName;
    }
    else
    {
      if ( strcmp_(v11, aNone_1) )
        goto LABEL_24;
      allPortItem = 0;
    }
    Parser_NextToken(readSource, theToken);
    if ( *(_DWORD *)theToken == 101 )
    {
      if ( allPortItem )
      {
        if ( !v13 )
        {
          allPortItem[3] = *(_DWORD *)(newModule + 16);
          *(_DWORD *)(newModule + 16) = allPortItem;
          return 0;
        }
        allPortItem[3] = *(_DWORD *)(newModule + 12);
        *(_DWORD *)(newModule + 12) = allPortItem;
      }
      return 0;
    }
    if ( allPortItem )
    {
      g_ClipsMemFreeListTemp = (int)allPortItem;
      *allPortItem = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
    }
    goto LABEL_23;
  }
  if ( *(_DWORD *)theToken != 2 )
    goto LABEL_24;
  constructTypeSym = *(_DWORD *)(theToken + 4);
  thePortConstruct = Rules_ValidPortConstructItem((char *)(uintptr_t)(unsigned int)*(_DWORD *)((uintptr_t)(unsigned int)constructTypeSym + 16));
  if ( !thePortConstruct )
    goto LABEL_24;
  IO_OutWriteToken(asc_50AC58);
  Parser_NextToken(readSource, theToken);
  if ( *(_DWORD *)theToken == 15 )
  {
    if ( !strcmp_(v8, aAll) )
    {
      if ( *(_DWORD *)(g_ClipsMemoryTable + 64) )
      {
        g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
        *(_DWORD *)(g_ClipsMemoryTable + 64) = *(_DWORD *)g_ClipsMemFreeListTemp;
        v17 = (_DWORD *)g_ClipsMemFreeListTemp;
      }
      else
      {
        v17 = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
      }
      v17[2] = 0;
      v17[3] = 0;
      *v17 = moduleName;
      typePortItem = v17;
      v17[1] = constructTypeSym;
    }
    else
    {
      if ( strcmp_(v16, aNone_1) )
        goto LABEL_24;
      typePortItem = 0;
    }
    Parser_NextToken(readSource, theToken);
    if ( *(_DWORD *)theToken == 101 )
    {
      if ( typePortItem )
      {
        if ( !v18 )
        {
          typePortItem[3] = *(_DWORD *)(newModule + 16);
          *(_DWORD *)(newModule + 16) = typePortItem;
          return 0;
        }
        typePortItem[3] = *(_DWORD *)(newModule + 12);
        *(_DWORD *)(newModule + 12) = typePortItem;
      }
      return 0;
    }
    if ( typePortItem )
    {
      g_ClipsMemFreeListTemp = (int)typePortItem;
      *typePortItem = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = g_ClipsMemFreeListTemp;
    }
LABEL_23:
    IO_OutNewline();
    IO_OutWriteToken(asc_50AC58);
    IO_OutWriteToken(*(char **)(theToken + 8));
    goto LABEL_24;
  }
  if ( *(_DWORD *)theToken == 101 )
  {
LABEL_24:
    Parser_ReportSyntaxError();
    return v14;
  }
  while ( *(_DWORD *)theToken != 101 )
  {
    if ( *(_DWORD *)theToken != *(_DWORD *)(thePortConstruct + 4) )
      goto LABEL_24;
    v9 = *(_DWORD **)(g_ClipsMemoryTable + 64);
    if ( v9 )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 64);
      *(_DWORD *)(g_ClipsMemoryTable + 64) = *v9;
      newPort = (_DWORD *)g_ClipsMemFreeListTemp;
    }
    else
    {
      newPort = (_DWORD *)Mem_HeapAllocWithRetry((_DWORD *)0x10);
    }
    *newPort = moduleName;
    newPort[1] = constructTypeSym;
    newPort[2] = *(_DWORD *)(theToken + 4);
    if ( v8 )
    {
      newPort[3] = *(_DWORD *)(newModule + 12);
      *(_DWORD *)(newModule + 12) = newPort;
    }
    else
    {
      newPort[3] = *(_DWORD *)(newModule + 16);
      *(_DWORD *)(newModule + 16) = newPort;
    }
    IO_OutWriteToken(asc_50AC58);
    Parser_NextToken(readSource, theToken);
  }
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50AC54);
  return 0;
}
// 4C18F8: variable 'v8' is possibly undefined
// 4C1935: variable 'v7' is possibly undefined
// 4C19D3: variable 'v14' is possibly undefined
// 4C19FE: variable 'v11' is possibly undefined
// 4C1A1A: variable 'v13' is possibly undefined
// 4C1AE9: variable 'v16' is possibly undefined
// 4C1B06: variable 'v18' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004C1B80) --------------------------------------------------------
int Rules_ValidPortConstructItem(char *theName)
{
  int export_type; // ecx

  export_type = g_Module_PortConstructList;
  while ( export_type )
  {
    if ( !strcmp(theName, (const char *)(uintptr_t)(unsigned int)*(_DWORD *)(uintptr_t)(unsigned int)export_type) )
      return export_type;
    export_type = *(_DWORD *)((uintptr_t)(unsigned int)export_type + 8);
  }
  return 0;
}
// 51B368: using guessed type int dword_51B368;
