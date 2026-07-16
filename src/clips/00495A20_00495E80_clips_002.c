/* Generated from src/recovered/rules/clips/004943E0_ast.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "../state/state_shared.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00495A20) --------------------------------------------------------
signed int  Rules_PackConstraintRecord(int *constraints, int bc)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  unsigned int v11; // eax
  unsigned int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  unsigned int v17; // eax
  unsigned int v18; // eax
  unsigned int v19; // eax
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v23; // ecx
  signed int result; // eax

  v3 = *constraints;
  *(_BYTE *)bc &= ~1u;
  *(_DWORD *)bc |= v3 & 1;
  v4 = *constraints;
  *(_BYTE *)bc &= ~2u;
  *(_DWORD *)bc |= v4 & 2;
  v5 = *constraints;
  *(_BYTE *)bc &= ~4u;
  *(_DWORD *)bc |= v5 & 4;
  v6 = *constraints;
  *(_BYTE *)bc &= ~8u;
  *(_DWORD *)bc |= v6 & 8;
  v7 = *constraints;
  *(_BYTE *)bc &= ~0x10u;
  *(_DWORD *)bc |= v7 & 0x10;
  v8 = *constraints;
  *(_BYTE *)bc &= ~0x20u;
  *(_DWORD *)bc |= v8 & 0x20;
  v9 = *constraints;
  *(_BYTE *)bc &= ~0x40u;
  *(_DWORD *)bc |= v9 & 0x40;
  v10 = *constraints;
  *(_BYTE *)bc &= ~0x80u;
  *(_DWORD *)bc |= v10 & 0x80;
  v11 = (unsigned int)(*constraints << 16) >> 31;
  *(_BYTE *)(bc + 2) &= ~1u;
  *(_DWORD *)bc |= (v11 & 1) << 16;
  v12 = (unsigned int)(*constraints << 15) >> 31;
  *(_BYTE *)(bc + 2) &= ~2u;
  *(_DWORD *)bc |= (v12 & 1) << 17;
  v13 = *constraints;
  *(_BYTE *)(bc + 1) &= ~1u;
  *(_DWORD *)bc |= v13 & 0x100;
  v14 = *constraints;
  *(_BYTE *)(bc + 1) &= ~2u;
  *(_DWORD *)bc |= v14 & 0x200;
  v15 = *constraints;
  *(_BYTE *)(bc + 1) &= ~4u;
  *(_DWORD *)bc |= v15 & 0x400;
  v16 = *constraints;
  *(_BYTE *)(bc + 1) &= ~8u;
  *(_DWORD *)bc |= v16 & 0x800;
  v17 = (unsigned int)(*constraints << 19) >> 31;
  *(_BYTE *)(bc + 1) &= ~0x20u;
  *(_DWORD *)bc |= (v17 & 1) << 13;
  v18 = (unsigned int)(*constraints << 18) >> 31;
  *(_BYTE *)(bc + 1) &= ~0x40u;
  *(_DWORD *)bc |= (v18 & 1) << 14;
  v19 = (unsigned int)(*constraints << 17) >> 31;
  *(_BYTE *)(bc + 1) &= ~0x80u;
  *(_DWORD *)bc |= (v19 & 1) << 15;
  *(_DWORD *)(bc + 4) = AST_GetHashedNodeIndex(*(__int16 **)((char *)constraints + 6));
  *(_DWORD *)(bc + 8) = AST_GetHashedNodeIndex(*(__int16 **)(v20 + 10));
  *(_DWORD *)(bc + 12) = AST_GetHashedNodeIndex(*(__int16 **)(v21 + 14));
  *(_DWORD *)(bc + 16) = AST_GetHashedNodeIndex(*(__int16 **)(v22 + 18));
  result = AST_GetHashedNodeIndex(*(__int16 **)(v23 + 22));
  *(_DWORD *)(bc + 20) = result;
  return result;
}
// 495B7D: variable 'v20' is possibly undefined
// 495B88: variable 'v21' is possibly undefined
// 495B93: variable 'v22' is possibly undefined
// 495B9E: variable 'v23' is possibly undefined

//----- (00495BB0) --------------------------------------------------------
int Rules_BloadConstraints(void)
{
  int result; // eax

  result = Rules_BloadReadBlock((uintptr_t)&g_Clips_BloadedConstraintCount, 4u);
  if ( g_Clips_BloadedConstraintCount )
  {
    g_ClipsConstraintRecordArrayBase = Mem_HeapAllocWithRetry((_DWORD *)(42 * g_Clips_BloadedConstraintCount));
    return Rules_BloadAndRefresh(g_Clips_BloadedConstraintCount, 24, (void (__fastcall *)(signed int, signed int))Rules_UpdateBloadedConstraint);
  }
  return result;
}
// 54E68C: using guessed type int dword_54E68C;
// 54E690: using guessed type int dword_54E690;

//----- (00495C00) --------------------------------------------------------
int  Rules_UpdateBloadedConstraint(_DWORD *bsaveConstraint, int constraintIndex)
{
  int result; // eax
  int v4; // ebx
  int v5; // ebx
  int v6; // ebx
  int v7; // ebx
  int v8; // ebx
  int v9; // ebx
  int v10; // ebx
  int v11; // ebx
  int v12; // ebx
  int v13; // ebx
  int v14; // ebx
  int v15; // ebx
  int v16; // ebx
  int v17; // ebx
  int v18; // ebx
  int v19; // ebx
  int v20; // ebx
  int restrictionListIndex; // ebp
  _DWORD *bsaveData; // edx
  int restrictionList; // ecx
  int minValueIndex; // ecx
  int minValue; // ecx
  int maxValueIndex; // ebx
  int maxValue; // ecx
  int minFieldsIndex; // esi
  int minFields; // ecx
  int maxFieldsIndex; // edi
  int maxFields; // edx

  result = g_ClipsConstraintRecordArrayBase + 42 * constraintIndex;
  v4 = *bsaveConstraint;
  *(_BYTE *)result &= ~1u;
  *(_DWORD *)result |= v4 & 1;
  v5 = *bsaveConstraint;
  *(_BYTE *)result &= ~2u;
  *(_DWORD *)result |= v5 & 2;
  v6 = *bsaveConstraint;
  *(_BYTE *)result &= ~4u;
  *(_DWORD *)result |= v6 & 4;
  v7 = *bsaveConstraint;
  *(_BYTE *)result &= ~8u;
  *(_DWORD *)result |= v7 & 8;
  v8 = *bsaveConstraint;
  *(_BYTE *)result &= ~0x10u;
  *(_DWORD *)result |= v8 & 0x10;
  v9 = *bsaveConstraint;
  *(_BYTE *)result &= ~0x20u;
  *(_DWORD *)result |= v9 & 0x20;
  v10 = *bsaveConstraint;
  *(_BYTE *)result &= ~0x40u;
  *(_DWORD *)result |= v10 & 0x40;
  v11 = *bsaveConstraint;
  *(_BYTE *)result &= ~0x80u;
  *(_DWORD *)result |= v11 & 0x80;
  v12 = *bsaveConstraint << 15 >> 31;
  *(_BYTE *)(result + 1) &= ~0x80u;
  *(_DWORD *)result |= (v12 & 1) << 15;
  v13 = *bsaveConstraint << 14 >> 31;
  *(_BYTE *)(result + 2) &= ~1u;
  *(_DWORD *)result |= (v13 & 1) << 16;
  v14 = *bsaveConstraint;
  *(_BYTE *)(result + 1) &= ~1u;
  *(_DWORD *)result |= v14 & 0x100;
  v15 = *bsaveConstraint;
  *(_BYTE *)(result + 1) &= ~2u;
  *(_DWORD *)result |= v15 & 0x200;
  v16 = *bsaveConstraint;
  *(_BYTE *)(result + 1) &= ~4u;
  *(_DWORD *)result |= v16 & 0x400;
  v17 = *bsaveConstraint;
  *(_BYTE *)(result + 1) &= ~8u;
  *(_DWORD *)result |= v17 & 0x800;
  v18 = *bsaveConstraint << 18 >> 31;
  *(_BYTE *)(result + 1) &= ~0x10u;
  *(_DWORD *)result |= (v18 & 1) << 12;
  v19 = *bsaveConstraint << 17 >> 31;
  *(_BYTE *)(result + 1) &= ~0x20u;
  *(_DWORD *)result |= (v19 & 1) << 13;
  v20 = *bsaveConstraint << 16 >> 31;
  *(_BYTE *)(result + 1) &= ~0x40u;
  *(_DWORD *)result |= (v20 & 1) << 14;
  restrictionListIndex = bsaveConstraint[1];
  bsaveData = bsaveConstraint;
  if ( restrictionListIndex == -1 )
    restrictionList = 0;
  else
    restrictionList = g_ClipsPackedExpressionArray + 14 * restrictionListIndex;
  *(_DWORD *)(result + 6) = restrictionList;
  minValueIndex = bsaveData[2];
  if ( minValueIndex == -1 )
    minValue = 0;
  else
    minValue = g_ClipsPackedExpressionArray + 14 * minValueIndex;
  *(_DWORD *)(result + 10) = minValue;
  maxValueIndex = bsaveData[3];
  if ( maxValueIndex == -1 )
    maxValue = 0;
  else
    maxValue = g_ClipsPackedExpressionArray + 14 * maxValueIndex;
  *(_DWORD *)(result + 14) = maxValue;
  minFieldsIndex = bsaveData[4];
  if ( minFieldsIndex == -1 )
    minFields = 0;
  else
    minFields = g_ClipsPackedExpressionArray + 14 * minFieldsIndex;
  *(_DWORD *)(result + 18) = minFields;
  maxFieldsIndex = bsaveData[5];
  if ( maxFieldsIndex == -1 )
  {
    *(_DWORD *)(result + 26) = 0;
    *(_DWORD *)(result + 22) = 0;
  }
  else
  {
    maxFields = 14 * maxFieldsIndex + g_ClipsPackedExpressionArray;
    *(_DWORD *)(result + 26) = 0;
    *(_DWORD *)(result + 22) = maxFields;
  }
  return result;
}
// 54E688: using guessed type int dword_54E688;
// 54E68C: using guessed type int dword_54E68C;

//----- (00495E00) --------------------------------------------------------
signed int Rules_ClearBloadedConstraints(void)
{
  signed int result; // eax

  if ( g_Clips_BloadedConstraintCount )
  {
    result = Mem_ReleasePoolBlock(g_ClipsConstraintRecordArrayBase, 42 * g_Clips_BloadedConstraintCount);
    g_Clips_BloadedConstraintCount = 0;
  }
  return result;
}
// 54E68C: using guessed type int dword_54E68C;
// 54E690: using guessed type int dword_54E690;

//----- (00495E30) --------------------------------------------------------
BOOL  Rules_BsaveCommand(DWORD a1, double a2)
{
  int v2; // ecx
  BOOL result; // eax
  const CHAR *fileName; // eax
  int v5; // ecx

  result = 0;
  if ( Lexer_TokenExpect(1) != -1 )
  {
    fileName = (const CHAR *)Rules_GetFileNameArg(1, v2, a2);
    if ( fileName )
    {
      if ( Rules_PerformBsave(fileName, a1, v5) )
        return 1;
    }
  }
  return result;
}
// 495E57: variable 'v2' is possibly undefined
// 495E60: variable 'v5' is possibly undefined

//----- (00495E80) --------------------------------------------------------
signed int  Rules_PerformBsave(const CHAR *fileName, DWORD a2, int a3)
{
  int v4; // ecx
  int fp; // ebx
  int v6; // edx
  int v7; // edx
  int v8; // ecx
  int i; // esi
  int v10; // ecx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int j; // esi
  int v16; // ecx
  int v17; // ecx
  int v19; // ecx
  _DWORD constructBuffer[9]; // [esp-20h] [ebp-24h] BYREF

  constructBuffer[7] = a3;
  if ( Rules_IsBloaded() )
  {
    Rules_PrintErrorID((int)aBsave_1, 1, 0);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCannotPerformA, v19);
    return 0;
  }
  else
  {
    fp = IO_FOpen(fileName, (unsigned __int8 *)aWb_3, v4, a2);
    if ( fp )
    {
      Module_BeginEnum();
      Rules_BsaveWriteHeader(fp);
      g_ClipsExpressionNodeIndex = v6;
      Event_ClearHandlers();
      Rules_ClearAtomInUseMarks();
      Rules_CountHashedExpressions();
      Event_InitHandlers();
      Rules_SetAtomicValueIndices(0);
      Rules_BsaveWriteFunctionNames(fp);
      Rules_BsaveAtomTables(fp);
      Rules_BsaveWriteBlock(v7, fp, &g_ClipsExpressionNodeIndex);
      for ( i = g_BinaryItemListHead; i; i = *(_DWORD *)(i + 36) )
      {
        if ( *(_DWORD *)(i + 24) )
        {
          strncpy_(v8, *(_DWORD *)i);
          Rules_BsaveWriteBlock(20, v10, constructBuffer);
          (*(void (**)(void))(i + 24))();
        }
      }
      Rules_BsaveWriteEndTag(v8, v8);
      g_ClipsExpressionNodeIndex = 0;
      Rules_AssignHashedExpressionIndices(v11);
      Rules_InvokeConstructCallbacks();
      g_ClipsExpressionNodeIndex = v12;
      Rules_BsaveWriteConstraints(v13);
      for ( j = g_BinaryItemListHead; j; j = *(_DWORD *)(j + 36) )
      {
        if ( *(_DWORD *)(j + 28) )
        {
          strncpy_(v14, *(_DWORD *)j);
          Rules_BsaveWriteBlock(20, v16, constructBuffer);
          (*(void (**)(void))(j + 28))();
        }
      }
      Rules_BsaveWriteEndTag(v14, v14);
      Rules_RestoreAtomicValueBuckets();
      fclose_(v17);
      Module_EndEnum();
      return 1;
    }
    else
    {
      Rules_OpenFileErrorMessage(0, (int)fileName);
      return 0;
    }
  }
}
// 495E9D: variable 'v4' is possibly undefined
// 495EBC: variable 'v6' is possibly undefined
// 495EF5: variable 'v7' is possibly undefined
// 495F13: variable 'v8' is possibly undefined
// 495F21: variable 'v10' is possibly undefined
// 495F43: variable 'v11' is possibly undefined
// 495F57: variable 'v12' is possibly undefined
// 495F5D: variable 'v13' is possibly undefined
// 495F7B: variable 'v14' is possibly undefined
// 495F89: variable 'v16' is possibly undefined
// 495FA8: variable 'v17' is possibly undefined
// 495FDA: variable 'v19' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51AA3C: using guessed type int dword_51AA3C;
// 54E680: using guessed type int dword_54E680;
