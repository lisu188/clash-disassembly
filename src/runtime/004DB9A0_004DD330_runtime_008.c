/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
#include "../state/state_shared.h"
#include "../clips/clips_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004DB9A0) --------------------------------------------------------
int  Rules_ParseStandardConstraintAttribute(char *readSource, const char *constraintName, _BYTE *parsedConstraints, int constraints, int multipleValuesAllowed)
{
  int v8; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx

  if ( Rules_TestConstraintAttributeParsedFlag((int)constraintName, parsedConstraints) )
  {
    Rules_ReportAlreadyParsed(0, (int)aAttribute);
    return 0;
  }
  else
  {
    if ( !strcmp_(0, aRange_0) || !strcmp_(v8, aCardinality) )
    {
      Rules_ParseRangeOrCardinalityAttribute((int)readSource, constraints, constraintName, parsedConstraints, readSource, multipleValuesAllowed);
    }
    else if ( !strcmp_(v10, aType_0) )
    {
      Rules_ParseTypeAttribute((int)readSource, v11);
    }
    else if ( !strcmp_(v11, aAllowedSymbols)
           || !strcmp_(v12, aAllowedStrings)
           || !strcmp_(v13, aAllowedLexemes)
           || !strcmp_(v14, aAllowedInteg_0)
           || !strcmp_(v15, aAllowedFloats)
           || !strcmp_(v16, aAllowedNumbers)
           || !strcmp_(v17, aAllowedInstanc)
           || !strcmp_(v18, aAllowedValues) )
    {
      Rules_ParseAllowedValuesAttribute((int)readSource, constraintName, (int)parsedConstraints, constraints);
    }
    Rules_MarkConstraintAttributeParsed(parsedConstraints, (int)constraintName);
    return v19;
  }
}
// 4DBA0E: variable 'v8' is possibly undefined
// 4DBA1E: variable 'v10' is possibly undefined
// 4DBA2C: variable 'v11' is possibly undefined
// 4DBA4A: variable 'v12' is possibly undefined
// 4DBA5A: variable 'v13' is possibly undefined
// 4DBA6A: variable 'v14' is possibly undefined
// 4DBA7A: variable 'v15' is possibly undefined
// 4DBA8A: variable 'v16' is possibly undefined
// 4DBA9A: variable 'v17' is possibly undefined
// 4DBABD: variable 'v18' is possibly undefined
// 4DBACF: variable 'v19' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DBAE0) --------------------------------------------------------
int  Rules_OverlayConstraint(int result, int cdst, int *csrc)
{
  char *pc; // edi
  int dst; // ecx
  int v6; // ecx
  signed int clonedMinValue; // eax
  int v8; // ecx
  char parseByte1; // bl
  char parseByte0; // bh
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
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // ecx
  char srcFlags; // bh
  int v28; // ecx
  int v29; // ecx
  signed int clonedMinFields; // eax
  int v31; // ecx
  int v32; // ecx

  pc = (char *)result;
  dst = cdst;
  if ( (*(_BYTE *)result & 1) == 0 )
  {
    v17 = *csrc;
    *(_BYTE *)cdst &= ~1u;
    *(_DWORD *)cdst |= v17 & 1;
    v18 = *csrc;
    *(_BYTE *)cdst &= ~2u;
    *(_DWORD *)cdst |= v18 & 2;
    v19 = *csrc;
    *(_BYTE *)cdst &= ~4u;
    *(_DWORD *)cdst |= v19 & 4;
    v20 = *csrc;
    *(_BYTE *)cdst &= ~8u;
    *(_DWORD *)cdst |= v20 & 8;
    v21 = *csrc;
    *(_BYTE *)cdst &= ~0x10u;
    *(_DWORD *)cdst |= v21 & 0x10;
    v22 = *csrc;
    *(_BYTE *)cdst &= ~0x20u;
    *(_DWORD *)cdst |= v22 & 0x20;
    v23 = *csrc;
    *(_BYTE *)cdst &= ~0x40u;
    *(_DWORD *)cdst |= v23 & 0x40;
    v24 = *csrc;
    *(_BYTE *)cdst &= ~0x80u;
    *(_DWORD *)cdst |= v24 & 0x80;
    v25 = *csrc;
    *(_BYTE *)(cdst + 1) &= ~1u;
    result = v25 & 0x100;
    *(_DWORD *)cdst |= result;
  }
  if ( (*pc & 2) == 0 )
  {
    AST_Free(*(_DWORD *)(cdst + 10));
    AST_Free(*(_DWORD *)(v6 + 14));
    clonedMinValue = AST_CloneNodeList(*(int *)((char *)csrc + 10));
    *(_DWORD *)(v8 + 10) = clonedMinValue;
    result = AST_CloneNodeList(*(int *)((char *)csrc + 14));
    *(_DWORD *)(dst + 14) = result;
  }
  parseByte1 = pc[1];
  if ( (parseByte1 & 1) == 0 )
  {
    parseByte0 = *pc;
    if ( (*pc & 4) != 0
      || (parseByte0 & 8) != 0
      || (parseByte0 & 0x10) != 0
      || (parseByte0 & 0x40) != 0
      || (parseByte0 & 0x20) != 0
      || parseByte0 < 0
      || (parseByte1 & 2) != 0 )
    {
      if ( (*pc & 4) == 0 && (*((_BYTE *)csrc + 1) & 4) != 0 )
      {
        *(_BYTE *)(dst + 1) |= 4u;
        result = Rules_MergeConstraintValueList(2, dst, (int)csrc);
      }
      if ( (*pc & 8) == 0 && (*((_BYTE *)csrc + 1) & 8) != 0 )
      {
        *(_BYTE *)(dst + 1) |= 8u;
        result = Rules_MergeConstraintValueList(3, dst, (int)csrc);
      }
      if ( (*pc & 0x10) == 0 )
      {
        BYTE1(result) = *((_BYTE *)csrc + 1);
        if ( (result & 0x400) != 0 && (result & 0x800) != 0 )
        {
          *(_BYTE *)(dst + 1) |= 0xCu;
          Rules_MergeConstraintValueList(2, dst, (int)csrc);
          result = Rules_MergeConstraintValueList(3, v26, (int)csrc);
        }
      }
      if ( (*pc & 0x40) == 0 && (*((_BYTE *)csrc + 1) & 0x20) != 0 )
      {
        *(_BYTE *)(dst + 1) |= 0x20u;
        result = Rules_MergeConstraintValueList(1, dst, (int)csrc);
      }
      if ( (*pc & 0x20) == 0 && (*((_BYTE *)csrc + 1) & 0x10) != 0 )
      {
        *(_BYTE *)(dst + 1) |= 0x10u;
        result = Rules_MergeConstraintValueList(0, dst, (int)csrc);
      }
      if ( *pc >= 0 )
      {
        srcFlags = *((_BYTE *)csrc + 1);
        if ( (srcFlags & 0x20) != 0 && (srcFlags & 0x10) != 0 )
        {
          *(_BYTE *)(dst + 1) |= 0x30u;
          Rules_MergeConstraintValueList(1, dst, (int)csrc);
          result = Rules_MergeConstraintValueList(0, v28, (int)csrc);
        }
      }
      if ( (pc[1] & 2) == 0 && (*((_BYTE *)csrc + 1) & 0x40) != 0 )
      {
        *(_BYTE *)(dst + 1) |= 0x40u;
        result = Rules_MergeConstraintValueList(8, dst, (int)csrc);
        if ( (pc[1] & 4) != 0 )
          return result;
        goto LABEL_39;
      }
    }
    else
    {
      v11 = *csrc;
      *(_BYTE *)(dst + 1) &= ~2u;
      *(_DWORD *)dst |= v11 & 0x200;
      v12 = *csrc;
      *(_BYTE *)(dst + 1) &= ~4u;
      *(_DWORD *)dst |= v12 & 0x400;
      v13 = *csrc;
      *(_BYTE *)(dst + 1) &= ~8u;
      *(_DWORD *)dst |= v13 & 0x800;
      v14 = *csrc;
      *(_BYTE *)(dst + 1) &= ~0x10u;
      *(_DWORD *)dst |= v14 & 0x1000;
      v15 = *csrc;
      *(_BYTE *)(dst + 1) &= ~0x20u;
      *(_DWORD *)dst |= v15 & 0x2000;
      v16 = *csrc;
      *(_BYTE *)(dst + 1) &= ~0x40u;
      *(_DWORD *)dst |= v16 & 0x4000;
      result = AST_CloneNodeList(*(int *)((char *)csrc + 6));
      *(_DWORD *)(dst + 6) = result;
    }
  }
  if ( (pc[1] & 4) == 0 )
  {
LABEL_39:
    AST_Free(*(_DWORD *)(dst + 18));
    AST_Free(*(_DWORD *)(v29 + 22));
    clonedMinFields = AST_CloneNodeList(*(int *)((char *)csrc + 18));
    *(_DWORD *)(v31 + 18) = clonedMinFields;
    result = AST_CloneNodeList(*(int *)((char *)csrc + 22));
    *(_DWORD *)(v32 + 22) = result;
  }
  return result;
}
// 4DBAFF: variable 'v6' is possibly undefined
// 4DBB0F: variable 'v8' is possibly undefined
// 4DBB1A: variable 'v4' is possibly undefined
// 4DBCEE: variable 'v26' is possibly undefined
// 4DBD62: variable 'v28' is possibly undefined
// 4DBDA4: variable 'v29' is possibly undefined
// 4DBDB4: variable 'v31' is possibly undefined
// 4DBDBF: variable 'v32' is possibly undefined

//----- (004DBE40) --------------------------------------------------------
signed int  Rules_MergeConstraintValueList(signed int result, int cdst, int csrc)
{
  signed int theType; // edi
  __int16 *i; // ecx
  int v6; // ecx

  theType = result;
  for ( i = *(__int16 **)(csrc + 6); i; i = *(__int16 **)(v6 + 10) )
  {
    while ( 1 )
    {
      result = *i;
      if ( result == theType )
        break;
      i = *(__int16 **)(i + 5);
      if ( !i )
        return result;
    }
    result = AST_NewNode(result, *(_DWORD *)(i + 1));
    *(_DWORD *)(result + 10) = *(_DWORD *)(cdst + 6);
    *(_DWORD *)(cdst + 6) = result;
  }
  return result;
}
// 4DBE71: variable 'v6' is possibly undefined

//----- (004DBE80) --------------------------------------------------------
signed int  Rules_ParseAllowedValuesAttribute(int readSource, const char *constraintName, int parsedConstraints, int constraints)
{
  char *v5; // ecx
  int error; // edi
  int constantParsed; // esi
  char v8; // ah
  char v9; // al
  _BYTE *v11; // ecx
  int v12; // ecx
  _BYTE *v13; // ecx
  char *conflictingAttribute; // edx
  char *v15; // ecx
  _BYTE *v16; // ecx
  unsigned int restrictionType; // eax
  signed int lastValue; // ebx
  int v19; // edx
  unsigned int variableTokenType; // ecx
  int v21; // ecx
  bool v22; // zf
  bool v23; // zf
  signed int newNode; // eax
  int v25; // ecx
  int v26; // ecx
  int v27; // ecx
  char v28[120]; // [esp+0h] [ebp-20Ch] BYREF
  char v29[120]; // [esp+78h] [ebp-194h] BYREF
  char v30[120]; // [esp+F0h] [ebp-11Ch] BYREF
  char v31[120]; // [esp+168h] [ebp-A4h] BYREF
  _DWORD theToken[2]; // [esp+1E0h] [ebp-2Ch] BYREF
  char *tempPtr; // [esp+1ECh] [ebp-20h]
  const char *v34; // [esp+1F0h] [ebp-1Ch]
  int v35; // [esp+1F4h] [ebp-18h]
  signed int newValue; // [esp+1F8h] [ebp-14h]
  int variableParsed; // [esp+1FCh] [ebp-10h]

  v34 = constraintName;
  v35 = constraints;
  error = 0;
  constantParsed = 0;
  variableParsed = 0;
  if ( !strcmp_(parsedConstraints, aAllowedValues) )
  {
    v8 = *v5;
    if ( (*v5 & 4) != 0
      || (v8 & 8) != 0
      || (v8 & 0x10) != 0
      || (v8 & 0x40) != 0
      || (v8 & 0x20) != 0
      || v8 < 0
      || (v5[1] & 2) != 0 )
    {
      v9 = *v5;
      if ( (*v5 & 4) != 0 )
      {
        tempPtr = aAllowedSymbols;
      }
      else if ( (v9 & 8) != 0 )
      {
        tempPtr = aAllowedStrings;
      }
      else if ( (v9 & 0x10) != 0 )
      {
        tempPtr = aAllowedLexemes;
      }
      else if ( (v9 & 0x40) != 0 )
      {
        tempPtr = aAllowedInteg_0;
      }
      else if ( (v9 & 0x20) != 0 )
      {
        tempPtr = aAllowedFloats;
      }
      else if ( v9 >= 0 )
      {
        if ( (v5[1] & 2) != 0 )
          tempPtr = aAllowedInstanc;
      }
      else
      {
        tempPtr = aAllowedNumbers;
      }
      Rules_ReportAttributeCannotCombine((int)v5, (int)tempPtr);
      return 0;
    }
  }
  if ( (!strcmp_(v5, aAllowedValues)
     || !strcmp_(v11, aAllowedNumbers)
     || !strcmp_(v11, aAllowedInteg_0)
     || !strcmp_(v11, aAllowedFloats))
    && (*v11 & 2) != 0 )
  {
    Rules_ReportAttributeCannotCombine((int)v11, (int)aRange_0);
    return 0;
  }
  if ( strcmp_(v11, aAllowedValues) && (*(_BYTE *)(v12 + 1) & 1) != 0 )
  {
    Rules_ReportAttributeCannotCombine(v12, (int)aAllowedValues);
    return 0;
  }
  if ( !strcmp_(v12, aAllowedNumbers) && ((*v13 & 0x20) != 0 || (*v13 & 0x40) != 0) )
  {
    if ( (*v13 & 0x20) != 0 )
      conflictingAttribute = aAllowedFloats;
    else
      conflictingAttribute = aAllowedInteg_0;
LABEL_20:
    Rules_ReportAttributeCannotCombine((int)v13, (int)conflictingAttribute);
    return 0;
  }
  if ( (!strcmp_(v13, aAllowedInteg_0) || !strcmp_(v15, aAllowedFloats)) && *v15 < 0 )
  {
    Rules_ReportAttributeCannotCombine((int)v15, (int)aAllowedNumber);
    return 0;
  }
  if ( !strcmp_(v15, aAllowedLexemes) && ((*v13 & 4) != 0 || (*v13 & 8) != 0) )
  {
    if ( (*v13 & 4) != 0 )
      conflictingAttribute = aAllowedSymbols;
    else
      conflictingAttribute = aAllowedStrings;
    goto LABEL_20;
  }
  if ( (!strcmp_(v13, aAllowedSymbols) || !strcmp_(v16, aAllowedStrings)) && (*v16 & 0x10) != 0 )
  {
    Rules_ReportAttributeCannotCombine((int)v16, (int)aAllowedLexemes);
    return 0;
  }
  restrictionType = Rules_GetAllowedAttributeTokenCode((int)v34);
  Rules_SetConstraintAllowedTypeFlag(restrictionType, v35, 1);
  lastValue = *(_DWORD *)(v35 + 6);
  if ( lastValue )
  {
    while ( *(_DWORD *)(lastValue + 10) )
      lastValue = *(_DWORD *)(lastValue + 10);
  }
  IO_OutWriteToken(asc_50DB38);
  Parser_NextToken(readSource, v19);
  if ( theToken[0] != 101 )
  {
    while ( 1 )
    {
      IO_OutWriteToken(asc_50DB38);
      if ( theToken[0] < 2u )
        break;
      if ( theToken[0] <= 2u )
      {
        if ( v21 == 103 || v21 == 2 )
          goto LABEL_69;
        v23 = v21 == 111;
        goto LABEL_67;
      }
      if ( theToken[0] < 8u )
      {
        if ( theToken[0] != 3 )
          goto LABEL_101;
        if ( v21 == 103 || v21 == theToken[0] )
          goto LABEL_69;
        v23 = v21 == 111;
        goto LABEL_67;
      }
      if ( theToken[0] <= 8u )
      {
        if ( v21 != 103 )
        {
          v23 = v21 == 8;
          goto LABEL_67;
        }
LABEL_69:
        constantParsed = 1;
        goto LABEL_70;
      }
      if ( theToken[0] != 15 )
      {
LABEL_101:
        sprintf_(v30, "%s attribute", v34);
        Parser_ReportSyntaxError();
        return 0;
      }
      if ( strcmp_(v21, a_variable) )
      {
        sprintf_(v31, "%s attribute", v34);
        Parser_ReportSyntaxError();
        return 0;
      }
      variableParsed = 1;
LABEL_70:
      if ( error )
      {
        Rules_PrintErrorID((int)aCstrnpsr, 4, 1);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aValueDoesNotMa, v25);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)v34, v26);
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttribute_0, v27);
        return 0;
      }
      if ( constantParsed && variableParsed )
      {
        sprintf_(v28, "%s attribute", v34);
        Parser_ReportSyntaxError();
        return 0;
      }
      newNode = AST_NewNode(theToken[0], theToken[1]);
      newValue = newNode;
      if ( lastValue )
        *(_DWORD *)(lastValue + 10) = newNode;
      else
        *(_DWORD *)(v35 + 6) = newNode;
      Parser_NextToken(readSource, (int)theToken);
      lastValue = newValue;
      if ( theToken[0] == 101 )
        goto LABEL_76;
    }
    if ( theToken[0] )
    {
      if ( v21 == 103 )
        goto LABEL_69;
      v22 = v21 == 1;
    }
    else
    {
      if ( v21 == 103 )
        goto LABEL_69;
      v22 = v21 == 0;
    }
    if ( v22 )
      goto LABEL_69;
    v23 = v21 == 110;
LABEL_67:
    if ( !v23 )
      error = 1;
    goto LABEL_69;
  }
LABEL_76:
  if ( constantParsed || variableParsed )
  {
    if ( variableParsed )
    {
      if ( variableTokenType >= 3 )
      {
        if ( variableTokenType > 3 )
        {
          if ( variableTokenType >= 0x67 )
          {
            if ( variableTokenType > 0x67 )
            {
              if ( variableTokenType >= 0x6E )
              {
                if ( variableTokenType > 0x6E )
                {
                  if ( variableTokenType == 111 )
                    *(_BYTE *)(v35 + 1) &= 0xF3u;
                }
                else
                {
                  *(_BYTE *)(v35 + 1) &= 0xCFu;
                }
              }
            }
            else
            {
              *(_BYTE *)(v35 + 1) &= ~2u;
            }
          }
          else if ( variableTokenType == 8 )
          {
            *(_BYTE *)(v35 + 1) &= ~0x40u;
          }
        }
        else
        {
          *(_BYTE *)(v35 + 1) &= ~8u;
        }
      }
      else if ( variableTokenType )
      {
        if ( variableTokenType > 1 )
          *(_BYTE *)(v35 + 1) &= ~4u;
        else
          *(_BYTE *)(v35 + 1) &= ~0x20u;
      }
      else
      {
        *(_BYTE *)(v35 + 1) &= ~0x10u;
      }
    }
    IO_OutNewline();
    IO_OutNewline();
    IO_OutWriteToken(asc_50DB94);
    return 1;
  }
  else
  {
    sprintf_(v29, "%s attribute", v34);
    Parser_ReportSyntaxError();
    return 0;
  }
}
// 4DBEB9: variable 'v5' is possibly undefined
// 4DBF2A: variable 'v11' is possibly undefined
// 4DBF48: variable 'v12' is possibly undefined
// 4DBF6B: variable 'v13' is possibly undefined
// 4DC0C0: variable 'v15' is possibly undefined
// 4DC15D: variable 'v16' is possibly undefined
// 4DC1EB: variable 'v19' is possibly undefined
// 4DC223: variable 'v21' is possibly undefined
// 4DC2C3: variable 'v20' is possibly undefined
// 4DC41C: variable 'v25' is possibly undefined
// 4DC42D: variable 'v26' is possibly undefined
// 4DC43C: variable 'v27' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (004DC550) --------------------------------------------------------
signed int __fastcall Rules_ReportAttributeCannotCombine(int attribute1, int attribute2)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  Rules_PrintErrorID((int)aCstrnpsr, 3, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aThe_2, v3);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v4, v4);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttributeCanno, v5);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aInConjunctionW, v6);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], attribute2, v7);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aAttribute_, v8);
}
// 4DC575: variable 'v3' is possibly undefined
// 4DC581: variable 'v4' is possibly undefined
// 4DC590: variable 'v5' is possibly undefined
// 4DC59F: variable 'v6' is possibly undefined
// 4DC5AB: variable 'v7' is possibly undefined
// 4DC5BA: variable 'v8' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DC5D0) --------------------------------------------------------
signed int  Rules_ParseTypeAttribute(int readSource, int constraints)
{
  int typeParsed; // edi
  int v4; // edx
  int variableParsed; // ebx
  int v6; // ecx
  signed int theType; // eax
  int v8; // ecx
  _BYTE *v9; // ecx
  _DWORD theToken[7]; // [esp+0h] [ebp-1Ch] BYREF

  theToken[5] = constraints;
  IO_OutWriteToken(asc_50DB38);
  typeParsed = 0;
  Parser_NextToken(readSource, v4);
  variableParsed = 0;
  while ( theToken[0] != 101 )
  {
    IO_OutWriteToken(asc_50DB38);
    if ( theToken[0] == 2 )
    {
      if ( variableParsed == 1 )
        goto LABEL_11;
      theType = Rules_GetTypeNameTokenCode(*(_DWORD *)(theToken[1] + 16));
      if ( theType < 0 || Rules_UpdateCETypeFlag(theType, v8) )
        goto LABEL_11;
      typeParsed = 1;
      *v9 &= ~1u;
    }
    else
    {
      if ( theToken[0] != 15 || strcmp_(v6, a_variable) || typeParsed || variableParsed )
        goto LABEL_11;
      variableParsed = 1;
    }
    Parser_NextToken(readSource, (int)theToken);
  }
  IO_OutNewline();
  IO_OutNewline();
  IO_OutWriteToken(asc_50DB94);
  if ( typeParsed || variableParsed )
    return 1;
LABEL_11:
  Parser_ReportSyntaxError();
  return 0;
}
// 4DC5EB: variable 'v4' is possibly undefined
// 4DC627: variable 'v8' is possibly undefined
// 4DC630: variable 'v9' is possibly undefined
// 4DC696: variable 'v6' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DC6B0) --------------------------------------------------------
signed int  Rules_ParseRangeOrCardinalityAttribute(
        int readSource,
        int constraints,
        const char *constraintName,
        _BYTE *parsedConstraints,
        char *conflictName,
        int multipleValuesAllowed)
{
  int v8; // ecx
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  char v17; // al
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  _BYTE minMsgBuffer[120]; // [esp+0h] [ebp-10Ch] BYREF
  _BYTE maxMsgBuffer[120]; // [esp+78h] [ebp-94h] BYREF
  int tokenType; // [esp+F0h] [ebp-1Ch] BYREF
  int tokenValue; // [esp+F4h] [ebp-18h]
  const char *tempName; // [esp+FCh] [ebp-10h]

  tempName = constraintName;
  if ( !strcmp_(constraintName, aRange_0) )
  {
    v8 = 1;
    *parsedConstraints |= 2u;
    if ( (parsedConstraints[1] & 1) != 0 || (v17 = *parsedConstraints, (char)*parsedConstraints < 0) || (v17 & 0x40) != 0 || (v17 & 0x20) != 0 )
    {
      if ( (parsedConstraints[1] & 1) != 0 )
      {
        conflictName = aAllowedValues;
      }
      else
      {
        LOBYTE(v8) = *parsedConstraints;
        if ( (*parsedConstraints & 0x40) != 0 )
        {
          conflictName = aAllowedInteg_0;
        }
        else if ( (v8 & 0x20) != 0 )
        {
          conflictName = aAllowedFloats;
        }
        else if ( (v8 & 0x80u) != 0 )
        {
          conflictName = aAllowedNumbers;
        }
      }
      Rules_ReportAttributeCannotCombine(v8, (int)conflictName);
      return 0;
    }
  }
  else
  {
    parsedConstraints[1] |= 4u;
    if ( !multipleValuesAllowed )
    {
      Rules_PrintErrorID((int)aCstrnpsr, 5, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aTheCardinality, v15);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCanOnlyBeUsedW, v16);
      return 0;
    }
  }
  IO_OutWriteToken(asc_50DB38);
  Parser_NextToken(readSource, v10);
  if ( tokenType == 1 || !tokenType && v11 )
  {
    if ( v11 )
    {
      AST_Free(*(_DWORD *)(constraints + 10));
      *(_DWORD *)(constraints + 10) = AST_NewNode(tokenType, tokenValue);
    }
    else
    {
      AST_Free(*(_DWORD *)(constraints + 18));
      *(_DWORD *)(constraints + 18) = AST_NewNode(tokenType, tokenValue);
    }
  }
  else if ( tokenType != 15 || strcmp_(v11, a_variable) )
  {
    sprintf_(minMsgBuffer, "%s attribute", tempName);
    Parser_ReportSyntaxError();
    return 0;
  }
  IO_OutWriteToken(asc_50DB38);
  Parser_NextToken(readSource, v12);
  if ( tokenType == 1 || !tokenType && v13 )
  {
    if ( v13 )
    {
      AST_Free(*(_DWORD *)(constraints + 14));
      *(_DWORD *)(constraints + 14) = AST_NewNode(tokenType, tokenValue);
    }
    else
    {
      AST_Free(*(_DWORD *)(constraints + 22));
      *(_DWORD *)(constraints + 22) = AST_NewNode(tokenType, tokenValue);
    }
  }
  else if ( tokenType != 15 || strcmp_(v13, a_variable) )
  {
    sprintf_(maxMsgBuffer, "%s attribute", tempName);
    Parser_ReportSyntaxError();
    return 0;
  }
  Parser_NextToken(readSource, (int)&tokenType);
  if ( tokenType == 101 )
  {
    if ( v14 )
    {
      if ( Rules_CompareBoundedCEValues(
             **(__int16 **)(constraints + 10),
             *(_DWORD *)(*(_DWORD *)(constraints + 10) + 2),
             *(_DWORD *)(*(_DWORD *)(constraints + 14) + 2),
             **(__int16 **)(constraints + 14)) != 1 )
        return 1;
      Rules_PrintErrorID((int)aCstrnpsr, 2, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMinimumRangeVa, v18);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOrEqualToTheMa, v19);
      return 0;
    }
    else
    {
      if ( Rules_CompareBoundedCEValues(
             **(__int16 **)(constraints + 18),
             *(_DWORD *)(*(_DWORD *)(constraints + 18) + 2),
             *(_DWORD *)(*(_DWORD *)(constraints + 22) + 2),
             **(__int16 **)(constraints + 22)) != 1 )
        return 1;
      Rules_PrintErrorID((int)aCstrnpsr, 2, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aMinimumCardina, v20);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOrEqualToThe_0, v21);
      return 0;
    }
  }
  else
  {
    Parser_ReportSyntaxError();
    return 0;
  }
}
// 4DC745: variable 'v10' is possibly undefined
// 4DC75C: variable 'v11' is possibly undefined
// 4DC793: variable 'v12' is possibly undefined
// 4DC7AA: variable 'v13' is possibly undefined
// 4DC7EC: variable 'v14' is possibly undefined
// 4DC841: variable 'v15' is possibly undefined
// 4DC850: variable 'v16' is possibly undefined
// 4DC9EF: variable 'v18' is possibly undefined
// 4DC9FE: variable 'v19' is possibly undefined
// 4DCA4C: variable 'v20' is possibly undefined
// 4DCA5B: variable 'v21' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51A614: using guessed type char *off_51A614[5];

//----- (004DCA70) --------------------------------------------------------
int  Rules_GetAllowedAttributeTokenCode(int constraintName)
{
  int v1; // ecx
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx

  if ( !strcmp_(constraintName, aAllowedValues) )
    return 103;
  if ( !strcmp_(v1, aAllowedSymbols) )
    return 2;
  if ( !strcmp_(v3, aAllowedStrings) )
    return 3;
  if ( !strcmp_(v4, aAllowedLexemes) )
    return 111;
  if ( !strcmp_(v5, aAllowedInteg_0) )
    return 1;
  if ( !strcmp_(v6, aAllowedNumbers) )
    return 110;
  if ( !strcmp_(v7, aAllowedInstanc) )
    return 8;
  result = strcmp_(v8, aAllowedFloats);
  if ( result )
    return -1;
  return result;
}
// 4DCA91: variable 'v1' is possibly undefined
// 4DCAA9: variable 'v3' is possibly undefined
// 4DCAC1: variable 'v4' is possibly undefined
// 4DCAD9: variable 'v5' is possibly undefined
// 4DCAF1: variable 'v6' is possibly undefined
// 4DCB09: variable 'v7' is possibly undefined
// 4DCB21: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DCB40) --------------------------------------------------------
int  Rules_GetTypeNameTokenCode(int typeName)
{
  int v1; // ecx
  int result; // eax
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx

  if ( !strcmp_(typeName, aSymbol_7) )
    return 2;
  if ( !strcmp_(v1, aString_3) )
    return 3;
  if ( !strcmp_(v3, aLexeme_1) )
    return 111;
  if ( !strcmp_(v4, aInteger_4) )
    return 1;
  result = strcmp_(v5, aFloat_4);
  if ( result )
  {
    if ( !strcmp_(v6, aNumber_2) )
    {
      return 110;
    }
    else if ( !strcmp_(v7, aInstanceName_4) )
    {
      return 8;
    }
    else if ( !strcmp_(v8, aInstanceAddr_8) )
    {
      return 7;
    }
    else if ( !strcmp_(v9, aInstance_6) )
    {
      return 112;
    }
    else if ( !strcmp_(v10, aExternalAddr_1) )
    {
      return 5;
    }
    else if ( !strcmp_(v11, aFactAddress_2) )
    {
      return 6;
    }
    else
    {
      return -1;
    }
  }
  return result;
}
// 4DCB61: variable 'v1' is possibly undefined
// 4DCB79: variable 'v3' is possibly undefined
// 4DCB91: variable 'v4' is possibly undefined
// 4DCBA9: variable 'v5' is possibly undefined
// 4DCBB9: variable 'v6' is possibly undefined
// 4DCBD1: variable 'v7' is possibly undefined
// 4DCBE9: variable 'v8' is possibly undefined
// 4DCC01: variable 'v9' is possibly undefined
// 4DCC19: variable 'v10' is possibly undefined
// 4DCC31: variable 'v11' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DCC50) --------------------------------------------------------
int  Rules_TestConstraintAttributeParsedFlag(int constraintName, _DWORD *parsedConstraints)
{
  int v3; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx

  if ( !strcmp_(constraintName, aType_0) )
    return *parsedConstraints & 1;
  if ( !strcmp_(v3, aRange_0) )
    return *parsedConstraints << 30 >> 31;
  if ( !strcmp_(v5, aCardinality) )
    return *parsedConstraints << 21 >> 31;
  if ( !strcmp_(v6, aAllowedValues) )
    return *parsedConstraints << 23 >> 31;
  if ( !strcmp_(v7, aAllowedSymbols) )
    return *parsedConstraints << 29 >> 31;
  if ( !strcmp_(v8, aAllowedStrings) )
    return *parsedConstraints << 28 >> 31;
  if ( !strcmp_(v9, aAllowedLexemes) )
    return *parsedConstraints << 27 >> 31;
  if ( !strcmp_(v10, aAllowedInstanc) )
    return *parsedConstraints << 22 >> 31;
  if ( !strcmp_(v11, aAllowedInteg_0) )
    return *parsedConstraints << 25 >> 31;
  if ( !strcmp_(v12, aAllowedFloats) )
    return *parsedConstraints << 26 >> 31;
  if ( !strcmp_(v13, aAllowedNumbers) )
    return *parsedConstraints << 24 >> 31;
  return 1;
}
// 4DCC73: variable 'v3' is possibly undefined
// 4DCC8E: variable 'v5' is possibly undefined
// 4DCCA9: variable 'v6' is possibly undefined
// 4DCCC4: variable 'v7' is possibly undefined
// 4DCCDF: variable 'v8' is possibly undefined
// 4DCCFA: variable 'v9' is possibly undefined
// 4DCD15: variable 'v10' is possibly undefined
// 4DCD30: variable 'v11' is possibly undefined
// 4DCD4B: variable 'v12' is possibly undefined
// 4DCD66: variable 'v13' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DCD90) --------------------------------------------------------
unsigned int  Rules_SetConstraintAllowedTypeFlag(unsigned int result, int constraints, char value)
{
  int flagBit; // ecx
  int v4; // ebp
  int v5; // esi
  int v6; // ebx

  flagBit = value & 1;
  v4 = flagBit << 12;
  v5 = flagBit << 13;
  v6 = flagBit << 10;
  if ( result < 3 )
  {
    if ( result )
    {
      if ( result > 1 )
      {
        *(_BYTE *)(constraints + 1) &= ~4u;
        *(_DWORD *)constraints |= v6;
      }
      else
      {
        *(_BYTE *)(constraints + 1) &= ~0x20u;
        *(_DWORD *)constraints |= v5;
      }
    }
    else
    {
      *(_BYTE *)(constraints + 1) &= ~0x10u;
      *(_DWORD *)constraints |= v4;
    }
    return result;
  }
  if ( result <= 3 )
  {
LABEL_14:
    *(_BYTE *)(constraints + 1) &= ~8u;
    *(_DWORD *)constraints |= flagBit << 11;
    return result;
  }
  if ( result < 0x67 )
  {
    if ( result == 8 )
    {
      *(_BYTE *)(constraints + 1) &= ~0x40u;
      *(_DWORD *)constraints |= flagBit << 14;
    }
    return result;
  }
  if ( result <= 0x67 )
  {
    *(_BYTE *)(constraints + 1) &= ~2u;
    *(_DWORD *)constraints |= flagBit << 9;
    return result;
  }
  if ( result >= 0x6E )
  {
    if ( result <= 0x6E )
    {
      *(_BYTE *)(constraints + 1) &= ~0x20u;
      *(_DWORD *)constraints |= v5;
      *(_BYTE *)(constraints + 1) &= ~0x10u;
      *(_DWORD *)constraints |= v4;
      return result;
    }
    if ( result == 111 )
    {
      *(_BYTE *)(constraints + 1) &= ~4u;
      *(_DWORD *)constraints |= v6;
      goto LABEL_14;
    }
  }
  return result;
}

//----- (004DCE50) --------------------------------------------------------
int  Rules_MarkConstraintAttributeParsed(_BYTE *parsedConstraints, int constraintName)
{
  int result; // eax
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx

  result = strcmp_(constraintName, aRange_0);
  if ( result )
  {
    result = strcmp_(v4, aType_0);
    if ( result )
    {
      result = strcmp_(v5, aCardinality);
      if ( result )
      {
        result = strcmp_(v6, aAllowedSymbols);
        if ( result )
        {
          result = strcmp_(v7, aAllowedStrings);
          if ( result )
          {
            result = strcmp_(v8, aAllowedLexemes);
            if ( result )
            {
              result = strcmp_(v9, aAllowedInteg_0);
              if ( result )
              {
                result = strcmp_(v10, aAllowedFloats);
                if ( result )
                {
                  result = strcmp_(v11, aAllowedNumbers);
                  if ( result )
                  {
                    result = strcmp_(v12, aAllowedValues);
                    if ( !result )
                      parsedConstraints[1] |= 1u;
                  }
                  else
                  {
                    *parsedConstraints |= 0x80u;
                  }
                }
                else
                {
                  *parsedConstraints |= 0x20u;
                }
              }
              else
              {
                *parsedConstraints |= 0x40u;
              }
            }
            else
            {
              *parsedConstraints |= 0x10u;
            }
          }
          else
          {
            *parsedConstraints |= 8u;
          }
        }
        else
        {
          *parsedConstraints |= 4u;
        }
      }
      else
      {
        parsedConstraints[1] |= 4u;
      }
    }
    else
    {
      *parsedConstraints |= 1u;
    }
  }
  else
  {
    *parsedConstraints |= 2u;
  }
  return result;
}
// 4DCE73: variable 'v4' is possibly undefined
// 4DCE89: variable 'v5' is possibly undefined
// 4DCEA0: variable 'v6' is possibly undefined
// 4DCEB6: variable 'v7' is possibly undefined
// 4DCECC: variable 'v8' is possibly undefined
// 4DCEE2: variable 'v9' is possibly undefined
// 4DCEF8: variable 'v10' is possibly undefined
// 4DCF0E: variable 'v11' is possibly undefined
// 4DCF24: variable 'v12' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004DCF40) --------------------------------------------------------
signed int  Rules_CEDetectDuplicatePatternBinding(_DWORD *patternPtr)
{
  _DWORD *thePattern; // edi
  int referringNode; // ebp
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int v7; // ecx
  char *errorMsg; // edx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int *theList; // ebp
  int *tempList; // esi
  int v16; // ecx
  int errorFlag; // [esp+4h] [ebp-1Ch]

  thePattern = patternPtr;
  errorFlag = 0;
  if ( !patternPtr )
    return errorFlag;
  while ( *thePattern == 80 )
  {
    if ( thePattern[1] )
    {
      referringNode = thePattern[5];
      if ( referringNode )
      {
        errorFlag = 1;
        if ( *(_DWORD *)(referringNode + 32) == -1 )
        {
          Rules_PrintErrorID((int)aAnalysis, 1, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aDuplicatePatte, v3);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(thePattern[1] + 16), v4);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInCe_0, v5);
          Rules_PrintLongInteger(v6, thePattern[2] << 19 >> 25);
          errorMsg = a__26;
        }
        else
        {
          Rules_PrintErrorID((int)aAnalysis, 2, 1);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPatternAddress, v10);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(thePattern[1] + 16), v11);
          Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUsedInCe, v12);
          Rules_PrintLongInteger(v13, thePattern[2] << 19 >> 25);
          errorMsg = aWasPreviouslyB;
        }
        Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)errorMsg, v7);
      }
    }
    if ( Rules_CEPropagateVariableBindingCheck((int)thePattern) )
      return 1;
LABEL_9:
    thePattern = (_DWORD *)thePattern[17];
    if ( !thePattern )
      return errorFlag;
  }
  if ( *thePattern != 84 )
    goto LABEL_9;
  Rules_CEFindUnboundVariableReference(thePattern[14], 0, 0, thePattern[2] << 19 >> 25, 0);
  theList = Rules_ClonePatternPositionConstraintList((int *)thePattern[14]);
  tempList = theList;
  if ( !theList )
  {
LABEL_17:
    AST_FreeNode((int)theList);
    if ( v16 )
      errorFlag = 1;
    else
      thePattern[13] = AST_CloneFieldAccessSubtreePN(thePattern[14]);
    goto LABEL_9;
  }
  while ( !Rules_CEScanBranchesForVariableMatch((int)thePattern, (int)thePattern, 15, 0, tempList[1], tempList, 0) )
  {
    tempList = (int *)tempList[16];
    if ( !tempList )
      goto LABEL_17;
  }
  AST_FreeNode((int)theList);
  return 1;
}
// 4DCFA2: variable 'v3' is possibly undefined
// 4DCFB2: variable 'v4' is possibly undefined
// 4DCFC1: variable 'v5' is possibly undefined
// 4DCFD4: variable 'v6' is possibly undefined
// 4DCFE3: variable 'v7' is possibly undefined
// 4DD027: variable 'v10' is possibly undefined
// 4DD037: variable 'v11' is possibly undefined
// 4DD046: variable 'v12' is possibly undefined
// 4DD059: variable 'v13' is possibly undefined
// 4DD0D8: variable 'v16' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DD110) --------------------------------------------------------
signed int  Rules_CEPropagateVariableBindingCheck(int thePattern)
{
  int theField; // ecx
  int *multifieldHeader; // esi
  int nodeType; // edx
  int *v6; // ecx

  theField = thePattern;
  multifieldHeader = 0;
  if ( !thePattern )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( (*(_BYTE *)(theField + 8) & 4) != 0 )
      {
        multifieldHeader = (int *)theField;
        theField = *(_DWORD *)(theField + 68);
      }
      if ( theField )
      {
        nodeType = *(_DWORD *)theField;
        if ( *(_DWORD *)theField == 15 || nodeType == 16 || nodeType == 80 && *(_DWORD *)(theField + 4) )
        {
          if ( Rules_CEBindPatternAddressVariable(theField, multifieldHeader, thePattern) )
            return 1;
        }
        else if ( Rules_CEValidateFieldConstraintUsage((_DWORD *)theField, multifieldHeader, thePattern) )
        {
          return 1;
        }
      }
      if ( theField )
        break;
      theField = (int)multifieldHeader;
LABEL_10:
      theField = *(_DWORD *)(theField + 64);
      if ( !theField )
        return 0;
    }
    if ( *(_DWORD *)(theField + 64) || !multifieldHeader )
      goto LABEL_10;
    v6 = multifieldHeader;
    multifieldHeader = 0;
    theField = v6[16];
  }
  while ( theField );
  return 0;
}
// 4DD14B: variable 'v1' is possibly undefined

//----- (004DD1A0) --------------------------------------------------------
signed int  Rules_CEBindPatternAddressVariable(int thePattern, int *multifieldHeader, int patternHead)
{
  _BYTE *theConstraints; // eax
  int theType; // [esp+0h] [ebp-18h]
  int theValue; // [esp+4h] [ebp-14h]

  if ( *(_DWORD *)thePattern == 80 )
  {
    theValue = *(_DWORD *)(thePattern + 4);
    theType = 15;
    if ( (*(_BYTE *)(thePattern + 8) & 0x10) != 0 )
      AST_DecrementNodeRefCount(*(_DWORD **)(thePattern + 16));
    theConstraints = (_BYTE *)Rules_CreateLHSParseNode();
    *(_DWORD *)(thePattern + 16) = theConstraints;
    *theConstraints &= ~1u;
    **(_BYTE **)(thePattern + 16) |= 0x40u;
    *(_BYTE *)(*(_DWORD *)(thePattern + 16) + 1) |= 1u;
    *(_BYTE *)(thePattern + 8) |= 0x10u;
  }
  else
  {
    theType = *(_DWORD *)thePattern;
    theValue = *(_DWORD *)(thePattern + 4);
  }
  if ( *(_DWORD *)thePattern == 80 )
    return Rules_CEScanBranchesForVariableMatch(patternHead, thePattern, theType, (int)multifieldHeader, theValue, (int *)thePattern, 1);
  Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(thePattern + 68), theType, (int *)thePattern, theValue, *(_DWORD *)(patternHead + 44), 1, 0);
  if ( !Rules_CEValidateFieldConstraintUsage((_DWORD *)thePattern, multifieldHeader, patternHead) )
    return Rules_CEScanBranchesForVariableMatch(patternHead, thePattern, theType, (int)multifieldHeader, theValue, (int *)thePattern, 1);
  else
    return 1;
}

//----- (004DD260) --------------------------------------------------------
signed int  Rules_CEScanBranchesForVariableMatch(
        int patternHead,
        int theNode,
        int theType,
        int multifieldNodesList,
        int theVariable,
        int *theReference,
        signed int assignReference)
{
  if ( multifieldNodesList && Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(multifieldNodesList + 64), theType, theReference, theVariable, *(_DWORD *)(patternHead + 44), assignReference, 0)
    || Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(theNode + 64), theType, theReference, theVariable, *(_DWORD *)(patternHead + 44), assignReference, 0) )
  {
LABEL_9:
    Rules_ReportVariableFieldTypeConflict();
    return 1;
  }
  if ( *(_DWORD *)patternHead == 80 || *(_DWORD *)patternHead == 84 )
  {
    if ( (*(_BYTE *)(patternHead + 8) & 1) != 0
      || *(_DWORD *)(patternHead + 44) > *(_DWORD *)(patternHead + 48)
      || !Rules_CEFindBoundVariableOccurrence(*(_DWORD *)(patternHead + 68), theType, theReference, theVariable, *(_DWORD *)(patternHead + 44), assignReference, *(_DWORD *)patternHead == 84) )
    {
      return 0;
    }
    goto LABEL_9;
  }
  return 0;
}

//----- (004DD330) --------------------------------------------------------
signed int  Rules_CEValidateFieldConstraintUsage(_DWORD *thePattern, int *multifieldHeader, int patternHead)
{
  int *tempList; // esi
  int v6; // ecx
  signed int theList; // [esp+0h] [ebp-18h]

  if ( *thePattern == 80 )
    return 0;
  theList = Rules_IntersectConnectedCEConstraints((int)thePattern);
  tempList = (int *)theList;
  if ( theList )
  {
    while ( !Rules_CEScanBranchesForVariableMatch(patternHead, (int)thePattern, *tempList, (int)multifieldHeader, tempList[1], tempList, 0) )
    {
      tempList = (int *)tempList[16];
      if ( !tempList )
        goto LABEL_6;
    }
    AST_FreeNode(theList);
    return 1;
  }
  else
  {
LABEL_6:
    AST_FreeNode(theList);
    if ( Rules_CEValidateLiteralAgainstConstraints((int)thePattern, *(_DWORD *)(patternHead + 8) << 19 >> 25, v6) )
    {
      return 1;
    }
    else if ( Rules_ComputeConnectedCEConstraintGroup((int)thePattern, multifieldHeader, patternHead) )
    {
      return 1;
    }
    else
    {
      AST_BuildClassHierarchyFieldAccessTest(thePattern, patternHead);
      return 0;
    }
  }
}
// 4DD390: variable 'v6' is possibly undefined
