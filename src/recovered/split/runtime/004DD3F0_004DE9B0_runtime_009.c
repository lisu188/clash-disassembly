/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004DD3F0) --------------------------------------------------------
signed int  Rules_CEFindBoundVariableOccurrence(
        int fieldList,
        int theType,
        int *theReference,
        int theVariable,
        int nandDepth,
        signed int assignReference,
        int allowMixing)
{
  int theField; // esi
  int testExpression; // edx
  _BYTE *newConstraints; // eax
  _DWORD *v12; // ecx
  char nodeFlags; // dl
  int rightField; // eax
  signed int result; // eax

  theField = fieldList;
  if ( fieldList )
  {
    while ( 1 )
    {
      testExpression = *(_DWORD *)(theField + 56);
      if ( testExpression )
      {
        Rules_CEFindBoundVariableOccurrence(testExpression, theType, (int)theReference, theVariable, nandDepth, assignReference, 1);
      }
      else
      {
        if ( (*(_DWORD *)theField == 15 || *(_DWORD *)theField == 16) && theVariable == *(_DWORD *)(theField + 4) )
        {
          if ( !allowMixing && (theType == 15 && *(_DWORD *)theField == 16 || theType == 16 && *(_DWORD *)theField == 15) )
            return 1;
          if ( theReference[4] && (*(_BYTE *)(theField + 8) & 1) == 0 )
          {
            newConstraints = Rules_IntersectConstraints(theReference[4], *(_DWORD *)(theField + 16));
            nodeFlags = *(_BYTE *)(theField + 8);
            *(_DWORD *)(theField + 16) = newConstraints;
            if ( (nodeFlags & 0x10) != 0 )
              AST_DecrementNodeRefCount(v12);
            *(_BYTE *)(theField + 8) |= 0x10u;
          }
          if ( !assignReference || *(_DWORD *)(theField + 20) && theReference[7] != *(_DWORD *)(theField + 28) && theReference[6] != *(_DWORD *)(theField + 24) )
            goto LABEL_18;
        }
        else
        {
          if ( *(_DWORD *)theField != 80 )
            goto LABEL_18;
          if ( theVariable != *(_DWORD *)(theField + 4) )
            goto LABEL_18;
          result = assignReference;
          if ( assignReference != 1 )
            goto LABEL_18;
          if ( theType == 16 )
            return result;
        }
        *(_DWORD *)(theField + 20) = theReference;
      }
LABEL_18:
      rightField = *(_DWORD *)(theField + 64);
      if ( rightField && Rules_CEFindBoundVariableOccurrence(rightField, theType, (int)theReference, theVariable, nandDepth, assignReference, allowMixing) )
        return 1;
      if ( (*(_DWORD *)theField == 80 || *(_DWORD *)theField == 84) && nandDepth > *(_DWORD *)(theField + 48) )
        return 0;
      theField = *(_DWORD *)(theField + 68);
      if ( !theField )
        return 0;
    }
  }
  return 0;
}
// 4DD3F0: could not find valid save-restore pair for ebx
// 4DD472: variable 'v12' is possibly undefined

//----- (004DD580) --------------------------------------------------------
signed int  Rules_CEValidateLiteralAgainstConstraints(int theNode, int whichCE, int a3)
{
  int theField; // esi
  int slotName; // ebp
  unsigned int *andField; // esi
  unsigned int fieldType; // ebx
  signed int violationCode; // eax
  unsigned int *orField; // [esp+0h] [ebp-20h]
  int theConstraints; // [esp+4h] [ebp-1Ch]
  int fieldPosition; // [esp+8h] [ebp-18h]

  if ( (*(_BYTE *)(theNode + 8) & 4) != 0 )
  {
    theField = *(_DWORD *)(theNode + 68);
    if ( theField )
    {
      while ( !Rules_CEValidateLiteralAgainstConstraints(theField, whichCE, a3) )
      {
        theField = *(_DWORD *)(theField + 64);
        if ( !theField )
          return 0;
      }
      return 1;
    }
    return 0;
  }
  fieldPosition = *(_DWORD *)(theNode + 32);
  theConstraints = *(_DWORD *)(theNode + 16);
  slotName = *(_DWORD *)(theNode + 36);
  orField = *(unsigned int **)(theNode + 68);
  if ( !orField )
    return 0;
  while ( 2 )
  {
    andField = orField;
    do
    {
      if ( (*andField == 15 || *andField == 16) && !andField[5] )
      {
        Rules_ReportUnboundVariableUsage(andField[1], 0, slotName, whichCE, fieldPosition);
        return 1;
      }
      fieldType = *andField;
      if ( *andField == 93 || fieldType == 94 )
      {
        if ( Rules_CEFindUnboundVariableReference(andField[14], 0, slotName, whichCE, fieldPosition) )
          return 1;
      }
      else if ( fieldType < 4 || fieldType == 8 )
      {
        if ( Rules_StaticConstraintCheckingEnabled() )
        {
          violationCode = Rules_CheckValueAgainstConstraint(*andField, andField[1], theConstraints);
          if ( violationCode )
          {
            Rules_PrintConstraintViolationMessage((int)aALiteralRestri, 0, whichCE, 0, slotName, fieldPosition, violationCode, theConstraints, 1);
            return 1;
          }
        }
      }
      andField = (unsigned int *)andField[16];
    }
    while ( andField );
    orField = (unsigned int *)orField[17];
    if ( orField )
      continue;
    break;
  }
  return 0;
}
// 4DD5DF: conditional instruction was optimized away because %var_20.4!=0
// 4DD65B: simplified comparisons for 'ebx.4': ==1 || ==0 became <2u
// 4DD65B: simplified comparisons for 'ebx.4': <2u || ==2 became <3u
// 4DD65B: simplified comparisons for 'ebx.4': <3u || ==3 became <4u
// 4DD59D: variable 'a3' is possibly undefined

//----- (004DD6C0) --------------------------------------------------------
int  Rules_CEFindUnboundVariableReference(int exprPtr, int theExpression, int slotName, int whichCE, int theField)
{
  int currentExpr; // esi
  int result; // eax
  int nodeType; // ecx
  int count; // [esp+0h] [ebp-18h] BYREF
  int savedExpression; // [esp+4h] [ebp-14h]
  int argNumber; // [esp+8h] [ebp-10h]

  currentExpr = exprPtr;
  savedExpression = theExpression;
  argNumber = 1;
  if ( !exprPtr )
    return 0;
  while ( 1 )
  {
    if ( *(_DWORD *)currentExpr == 15 )
    {
      if ( !*(_DWORD *)(currentExpr + 20) )
        break;
      if ( Rules_ConstraintIsUnmatchable(*(char **)(currentExpr + 16)) && Rules_StaticConstraintCheckingEnabled() )
      {
        Rules_PrintVariableBindingConstraintViolation(*(_DWORD *)(currentExpr + 4), savedExpression, whichCE, argNumber, slotName, theField);
        return currentExpr;
      }
      goto LABEL_6;
    }
    if ( *(_DWORD *)currentExpr == 16 && !*(_DWORD *)(currentExpr + 20) )
      break;
    nodeType = *(_DWORD *)currentExpr;
    if ( *(_DWORD *)currentExpr == 13 )
    {
      if ( !Rules_FindImportExportConstruct(aDefglobal_6, &count, *(_BYTE **)(*(_DWORD *)(currentExpr + 4) + 16), 1, 0) )
        break;
    }
    else if ( nodeType == 10 || nodeType == 11 || nodeType == 12 )
    {
      if ( *(_DWORD *)(currentExpr + 68) )
      {
        result = Rules_CEFindUnboundVariableReference(*(_DWORD *)(currentExpr + 68), currentExpr, slotName, whichCE, theField);
        if ( result )
          return result;
      }
    }
LABEL_6:
    currentExpr = *(_DWORD *)(currentExpr + 64);
    ++argNumber;
    if ( !currentExpr )
      return 0;
  }
  Rules_ReportUnboundVariableUsage(*(_DWORD *)(currentExpr + 4), savedExpression, slotName, whichCE, theField);
  return currentExpr;
}

//----- (004DD820) --------------------------------------------------------
signed int  Rules_ReportUnboundVariableUsage(int theVariable, int theExpression, int slotName, int whichCE, int theField)
{
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int clonedExpression; // eax
  int v12; // ecx
  __int16 *v13; // ecx
  int v14; // ecx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v19; // ecx
  int v20; // ecx

  Rules_PrintErrorID((int)aAnalysis, 4, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVariable_, v7);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(theVariable + 16), v8);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50DE28, v9);
  if ( theExpression )
  {
    clonedExpression = Rules_CECloneBindingList(theExpression);
    AST_Free(*(_DWORD *)(clonedExpression + 10));
    *(_DWORD *)(v12 + 10) = 0;
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInTheExpr, v12);
    Rules_PrintFieldExprList((signed int)g_IO_LogicalNameTable_WError[0], v13);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50DE48, v14);
    AST_Free(v15);
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aWasReferencedI, v10);
  Rules_PrintLongInteger(v16, whichCE);
  if ( slotName )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_8, v17);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(slotName + 16), v20);
  }
  else if ( theField > 0 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField_1, v17);
    Rules_PrintLongInteger(v19, theField);
  }
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aBeforeBeingDef, v17);
}
// 4DD84D: variable 'v7' is possibly undefined
// 4DD85D: variable 'v8' is possibly undefined
// 4DD86C: variable 'v9' is possibly undefined
// 4DD886: variable 'v12' is possibly undefined
// 4DD8A3: variable 'v13' is possibly undefined
// 4DD8B2: variable 'v14' is possibly undefined
// 4DD8B9: variable 'v15' is possibly undefined
// 4DD8C8: variable 'v10' is possibly undefined
// 4DD8D4: variable 'v16' is possibly undefined
// 4DD906: variable 'v17' is possibly undefined
// 4DD914: variable 'v19' is possibly undefined
// 4DD932: variable 'v20' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DD940) --------------------------------------------------------
signed int Rules_ReportVariableFieldTypeConflict()
{
  int v0; // ecx
  int v1; // ecx
  int v2; // ecx

  Rules_PrintErrorID((int)aAnalysis, 3, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVariable_, v0);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v1 + 16), v1);
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aIsUsedAsBothAS, v2);
}
// 4DD963: variable 'v0' is possibly undefined
// 4DD96D: variable 'v1' is possibly undefined
// 4DD97F: variable 'v2' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DD990) --------------------------------------------------------
int Rules_CheckAndReportUnmatchableFieldConstraint()
{
  int result; // eax
  int v1; // ecx
  int v2; // edx
  int v3; // ecx

  result = Rules_StaticConstraintCheckingEnabled();
  if ( result )
  {
    result = (int)Rules_ConstraintIsUnmatchable(*(char **)(v1 + 16));
    if ( result )
    {
      Rules_ReportConstraintReferenceConflict(*(_DWORD *)(v3 + 4), v2, *(_DWORD *)(v3 + 32));
      return 1;
    }
  }
  return result;
}
// 4DD99E: variable 'v1' is possibly undefined
// 4DD9B2: variable 'v3' is possibly undefined
// 4DD9B9: variable 'v2' is possibly undefined

//----- (004DD9D0) --------------------------------------------------------
signed int  Rules_ReportConstraintReferenceConflict(int theVariable, int whichCE, int theField)
{
  int v5; // ecx
  char *contextText; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v12; // ecx
  int v13; // ecx

  Rules_PrintErrorID((int)aRulecstr, 1, 1);
  if ( theVariable )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aVariable__0, v5);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(theVariable + 16), v12);
    contextText = aInCe;
  }
  else
  {
    contextText = aPattern_0;
  }
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)contextText, v5);
  Rules_PrintLongInteger(v7, whichCE);
  if ( v8 )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_9, v8);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(v13 + 16), v13);
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField_2, 0);
    Rules_PrintLongInteger(v9, theField);
  }
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aHasConstraintC, v10);
}
// 4DD9F8: variable 'v5' is possibly undefined
// 4DDA04: variable 'v7' is possibly undefined
// 4DDA0B: variable 'v8' is possibly undefined
// 4DDA23: variable 'v9' is possibly undefined
// 4DDA32: variable 'v10' is possibly undefined
// 4DDA52: variable 'v12' is possibly undefined
// 4DDA72: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DDA90) --------------------------------------------------------
int  Rules_DeriveCEFieldCardinalityConstraint(int theNode)
{
  int minFields; // ecx
  signed int maxFields; // ebx
  int posInfinity; // esi
  _DWORD *i; // edx
  int constraintNode; // eax
  _DWORD *newConstraint; // edi
  signed int v8; // ecx
  int *minValue; // eax
  __int16 maxType; // ax
  int *maxValueNode; // edx
  char nodeFlags; // bh
  int v13; // edx
  int result; // eax
  char *v15; // edx
  int theConstraint; // edi
  int minBound; // edi
  int j; // eax
  int maxBound; // edi

  minFields = 0;
  maxFields = 0;
  posInfinity = 0;
  if ( (*(_BYTE *)(theNode + 8) & 4) == 0 )
    return 0;
  for ( i = *(_DWORD **)(theNode + 68); i; i = (_DWORD *)i[16] )
  {
    if ( *i == 15 || *i == 17 )
    {
      ++minFields;
      ++maxFields;
    }
    else
    {
      theConstraint = i[4];
      if ( !theConstraint )
        goto LABEL_22;
      minBound = *(_DWORD *)(*(_DWORD *)(theConstraint + 18) + 2);
      if ( minBound != g_Clips_NegativeInfinitySymbol )
        minFields += *(_DWORD *)(minBound + 16);
      for ( j = *(_DWORD *)(i[4] + 22); *(_DWORD *)(j + 10); j = *(_DWORD *)(j + 10) )
        ;
      maxBound = *(_DWORD *)(j + 2);
      if ( maxBound != g_ClipsPositiveInfinitySymbol )
        maxFields += *(_DWORD *)(maxBound + 16);
      else
LABEL_22:
        posInfinity = 1;
    }
  }
  if ( *(_DWORD *)(theNode + 16) )
    constraintNode = Rules_CloneLHSParseNode(*(int **)(theNode + 16));
  else
    constraintNode = Rules_CreateLHSParseNode();
  newConstraint = (_DWORD *)constraintNode;
  AST_Free(*(_DWORD *)(constraintNode + 18));
  AST_Free(*(_DWORD *)((char *)newConstraint + 22));
  minValue = Rules_AddIntegerValue(v8);
  *(_DWORD *)((char *)newConstraint + 18) = AST_NewNode(1, (int)minValue);
  if ( posInfinity )
  {
    maxType = 2;
    maxValueNode = (int *)g_ClipsPositiveInfinitySymbol;
  }
  else
  {
    maxValueNode = Rules_AddIntegerValue(maxFields);
    maxType = 1;
  }
  *(_DWORD *)((char *)newConstraint + 22) = AST_NewNode(maxType, (int)maxValueNode);
  Rules_IntersectConstraints(*(_DWORD *)(theNode + 16), (int)newConstraint);
  if ( (*(_BYTE *)(theNode + 8) & 0x10) != 0 )
    AST_DecrementNodeRefCount(*(_DWORD **)(theNode + 16));
  AST_DecrementNodeRefCount(newConstraint);
  nodeFlags = *(_BYTE *)(theNode + 8);
  *(_DWORD *)(theNode + 16) = v13;
  *(_BYTE *)(theNode + 8) = nodeFlags | 0x10;
  result = Rules_StaticConstraintCheckingEnabled();
  if ( result )
  {
    result = (int)Rules_ConstraintIsUnmatchable(v15);
    if ( result )
      return 1;
  }
  return result;
}
// 4DDAE9: variable 'v8' is possibly undefined
// 4DDB3E: variable 'v13' is possibly undefined
// 4DDBD8: variable 'v15' is possibly undefined
// 54DD60: using guessed type int dword_54DD60;
// 54DD68: using guessed type int dword_54DD68;

//----- (004DDC00) --------------------------------------------------------
signed int  Rules_ComputeConnectedCEConstraintGroup(int theNode, int *multifieldNodesList, int patternHead)
{
  int andField; // ebx
  int branchConstraint; // ecx
  _BYTE *returnConstraint; // esi
  int v6; // ecx
  _DWORD *oldBranchConstraint; // edi
  _DWORD *mergedBranchConstraint; // ebx
  int cleanupField; // esi
  int branchGroupConstraint; // ecx
  _DWORD *prevAccumConstraints; // ebx
  _DWORD *unionedBranchConstraint; // ecx
  __int16 *constantExpr; // esi
  _BYTE *constantConstraint; // edi
  int v16; // ecx
  _DWORD *prevBranchConstraint; // ebp
  int accumConstraints; // [esp+Ch] [ebp-18h]
  int orField; // [esp+10h] [ebp-14h]

  accumConstraints = 0;
  orField = *(_DWORD *)(theNode + 68);
  if ( !orField )
    goto LABEL_15;
  do
  {
    andField = orField;
    branchConstraint = 0;
    do
    {
      if ( (*(_BYTE *)(andField + 8) & 1) != 0 )
        goto LABEL_8;
      if ( *(_DWORD *)andField == 94 )
      {
        if ( **(_DWORD **)(andField + 56) != 10 )
          goto LABEL_8;
        returnConstraint = Rules_ApplyCEKeywordFlags();
        oldBranchConstraint = (_DWORD *)v6;
        Rules_IntersectConstraints(v6, (int)returnConstraint);
        AST_DecrementNodeRefCount(oldBranchConstraint);
        goto LABEL_7;
      }
      if ( Rules_TagIsConstantType(*(_DWORD *)andField) )
      {
        constantExpr = (__int16 *)AST_NewNode(*(_DWORD *)andField, *(_DWORD *)(andField + 4));
        constantConstraint = Rules_BuildLHSNodeFromToken(constantExpr);
        prevBranchConstraint = (_DWORD *)v16;
        Rules_IntersectConstraints(v16, (int)constantConstraint);
        AST_DecrementNodeRefCount(prevBranchConstraint);
        AST_DecrementNodeRefCount(constantConstraint);
        AST_Free((int)constantExpr);
      }
      else if ( *(_DWORD *)(andField + 16) )
      {
        returnConstraint = (_BYTE *)branchConstraint;
        Rules_IntersectConstraints(branchConstraint, *(_DWORD *)(andField + 16));
LABEL_7:
        AST_DecrementNodeRefCount(returnConstraint);
      }
LABEL_8:
      andField = *(_DWORD *)(andField + 64);
    }
    while ( andField );
    mergedBranchConstraint = (_DWORD *)branchConstraint;
    Rules_IntersectConstraints(branchConstraint, *(_DWORD *)(theNode + 16));
    cleanupField = orField;
    AST_DecrementNodeRefCount(mergedBranchConstraint);
    do
    {
      if ( (*(_BYTE *)(cleanupField + 8) & 1) != 0 && Rules_TagIsConstantType(*(_DWORD *)cleanupField) )
        Rules_RemoveConstantFromConstraint(*(_DWORD *)cleanupField, *(_DWORD *)(cleanupField + 4), branchGroupConstraint);
      cleanupField = *(_DWORD *)(cleanupField + 64);
    }
    while ( cleanupField );
    prevAccumConstraints = (_DWORD *)accumConstraints;
    accumConstraints = Rules_UnionConstraints(accumConstraints, branchGroupConstraint);
    AST_DecrementNodeRefCount(prevAccumConstraints);
    AST_DecrementNodeRefCount(unionedBranchConstraint);
    orField = *(_DWORD *)(orField + 68);
  }
  while ( orField );
LABEL_15:
  if ( accumConstraints )
  {
    if ( (*(_BYTE *)(theNode + 8) & 0x10) != 0 )
      AST_DecrementNodeRefCount(*(_DWORD **)(theNode + 16));
    *(_DWORD *)(theNode + 16) = accumConstraints;
    *(_BYTE *)(theNode + 8) |= 0x10u;
  }
  if ( Rules_CheckAndReportUnmatchableFieldConstraint() )
    return 1;
  if ( !multifieldNodesList || *(_DWORD *)(theNode + 64) || !Rules_DeriveCEFieldCardinalityConstraint((int)multifieldNodesList) )
    return 0;
  Rules_PrintConstraintViolationMessage((int)aTheGroupOfRest, 0, *(_DWORD *)(patternHead + 8) << 19 >> 25, 0, multifieldNodesList[9], multifieldNodesList[8], 5, multifieldNodesList[4], 1);
  return 1;
}
// 4DDC2F: conditional instruction was optimized away because %var_14.4!=0
// 4DDC95: conditional instruction was optimized away because esi.4!=0
// 4DDC58: variable 'v6' is possibly undefined
// 4DDC7F: variable 'v4' is possibly undefined
// 4DDCAF: variable 'v10' is possibly undefined
// 4DDCD5: variable 'v12' is possibly undefined
// 4DDD94: variable 'v16' is possibly undefined

//----- (004DDE10) --------------------------------------------------------
signed int  Rules_PrintVariableBindingConstraintViolation(int theVariable, int theExpression, int whichCE, int whichArgument, int slotName, int theField)
{
  int v8; // ecx
  int v9; // ecx
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  int v13; // ecx
  int clonedExpression; // eax
  int clonedExprNode; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // edx
  int v19; // ecx
  int v20; // ecx
  int v21; // ecx
  int v22; // ecx
  int v24; // ecx
  int v25; // ecx

  Rules_PrintErrorID((int)aRulecstr, 2, 1);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPreviousVariab, v8);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(theVariable + 16), v9);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCausedTheTypeR, v10);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForArgument_0, v11);
  Rules_PrintLongInteger(v12, whichArgument);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfTheExpressio, v13);
  clonedExpression = Rules_CECloneBindingList(theExpression);
  AST_Free(*(_DWORD *)(clonedExpression + 10));
  *(_DWORD *)(clonedExprNode + 10) = 0;
  Rules_PrintFieldExprList((signed int)g_IO_LogicalNameTable_WError[0], (__int16 *)clonedExprNode);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50DFD4, v16);
  AST_Free(v17);
  Output_Write((int)g_IO_LogicalNameTable_WError[0], v18, v19);
  Rules_PrintLongInteger(v20, whichCE);
  if ( slotName )
  {
    Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aSlot_9, v21);
    Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(slotName + 16), v25);
  }
  else
  {
    v22 = theField;
    if ( theField > 0 )
    {
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aField_2, theField);
      Rules_PrintLongInteger(v24, v24);
    }
  }
  return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aToBeViolated_, v22);
}
// 4DDE3D: variable 'v8' is possibly undefined
// 4DDE4D: variable 'v9' is possibly undefined
// 4DDE5C: variable 'v10' is possibly undefined
// 4DDE6B: variable 'v11' is possibly undefined
// 4DDE77: variable 'v12' is possibly undefined
// 4DDE86: variable 'v13' is possibly undefined
// 4DDE9C: variable 'v15' is possibly undefined
// 4DDEB9: variable 'v16' is possibly undefined
// 4DDEC5: variable 'v17' is possibly undefined
// 4DDECF: variable 'v18' is possibly undefined
// 4DDECF: variable 'v19' is possibly undefined
// 4DDEDB: variable 'v20' is possibly undefined
// 4DDF1D: variable 'v24' is possibly undefined
// 4DDEF9: variable 'v22' is possibly undefined
// 4DDF2E: variable 'v21' is possibly undefined
// 4DDF3F: variable 'v25' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DDF50) --------------------------------------------------------
_DWORD * Rules_MergeConstraintListsByFieldIndex(_DWORD *theList, _DWORD *newItems)
{
  _DWORD *theItem; // ebx
  _DWORD *tempList; // ecx
  _DWORD *nextItem; // edi
  int v6; // ecx
  int v7; // edx
  int v8; // ecx

  theItem = newItems;
  if ( newItems )
  {
    do
    {
      tempList = theList;
      nextItem = (_DWORD *)theItem[16];
      theItem[16] = 0;
      if ( theList )
      {
        while ( tempList[1] != theItem[1] )
        {
          tempList = (_DWORD *)tempList[16];
          if ( !tempList )
            goto LABEL_5;
        }
        Rules_IntersectConstraints(tempList[4], theItem[4]);
        AST_DecrementNodeRefCount(*(_DWORD **)(v6 + 16));
        *(_DWORD *)(v8 + 16) = v7;
        AST_FreeNode((int)theItem);
      }
LABEL_5:
      if ( !tempList )
      {
        theItem[16] = theList;
        theList = theItem;
      }
      theItem = nextItem;
    }
    while ( nextItem );
  }
  return theList;
}
// 4DDF81: variable 'v6' is possibly undefined
// 4DDF8B: variable 'v7' is possibly undefined
// 4DDF8B: variable 'v8' is possibly undefined
// 4DDF95: variable 'v4' is possibly undefined

//----- (004DDFC0) --------------------------------------------------------
signed int  Rules_IntersectConstraintListsByFieldIndex(int theList1, int theList2)
{
  int theNode; // ecx
  signed int theHead; // edi
  int otherNode; // edx
  signed int tempNode; // ebx
  int v7; // ecx
  int v8; // edx
  int v9; // edx

  theNode = theList1;
  theHead = 0;
  if ( theList1 )
  {
    do
    {
      otherNode = theList2;
      if ( theList2 )
      {
        while ( *(_DWORD *)(theNode + 4) != *(_DWORD *)(otherNode + 4) )
        {
          otherNode = *(_DWORD *)(otherNode + 64);
          if ( !otherNode )
            goto LABEL_5;
        }
        tempNode = AST_AllocNode();
        *(_BYTE *)(tempNode + 8) |= 0x10u;
        *(_DWORD *)(tempNode + 4) = *(_DWORD *)(v7 + 4);
        *(_DWORD *)(tempNode + 16) = Rules_UnionConstraints(*(_DWORD *)(v7 + 16), *(_DWORD *)(v8 + 16));
        *(_DWORD *)(tempNode + 64) = theHead;
        theHead = tempNode;
      }
LABEL_5:
      *(_DWORD *)(theNode + 64) = 0;
      AST_FreeNode(theNode);
      theNode = v9;
    }
    while ( v9 );
  }
  AST_FreeNode(theList2);
  return theHead;
}
// 4DDFEC: variable 'v7' is possibly undefined
// 4DDFF2: variable 'v8' is possibly undefined
// 4DE00A: variable 'v2' is possibly undefined
// 4DE016: variable 'v9' is possibly undefined

//----- (004DE040) --------------------------------------------------------
_DWORD * Rules_ClonePatternPositionConstraintList(int *theExpression)
{
  int *expPtr; // ecx
  _DWORD *i; // edx
  int nodeType; // esi
  signed int newNode; // eax
  int v5; // ecx
  int *referringNode; // edi
  _DWORD *theConstraint; // ebx
  _DWORD *v8; // edx
  _DWORD *tmpList; // eax
  _DWORD *v11; // edx

  expPtr = theExpression;
  for ( i = 0; expPtr; expPtr = (int *)expPtr[17] )
  {
    if ( expPtr[16] )
    {
      tmpList = (_DWORD *)Rules_ClonePatternPositionConstraintList(expPtr[16]);
      i = Rules_MergeConstraintListsByFieldIndex(tmpList, v11);
    }
    nodeType = *expPtr;
    if ( *expPtr == 15 )
    {
      newNode = AST_AllocNode();
      referringNode = *(int **)(v5 + 20);
      theConstraint = (_DWORD *)newNode;
      if ( referringNode )
        nodeType = *referringNode;
      *(_DWORD *)newNode = nodeType;
      *(_DWORD *)(newNode + 4) = *(_DWORD *)(v5 + 4);
      *(_BYTE *)(newNode + 8) |= 0x10u;
      *(_DWORD *)(newNode + 16) = Rules_CloneLHSParseNode(*(int **)(v5 + 16));
      i = Rules_MergeConstraintListsByFieldIndex(theConstraint, v8);
    }
  }
  return i;
}
// 4DE0A1: variable 'v11' is possibly undefined
// 4DE054: variable 'v1' is possibly undefined
// 4DE060: variable 'v5' is possibly undefined
// 4DE084: variable 'v8' is possibly undefined

//----- (004DE0B0) --------------------------------------------------------
signed int  Rules_IntersectConnectedCEConstraints(int theNode)
{
  int first; // ebp
  int orField; // esi
  int list1; // edi
  int andField; // ecx
  _DWORD *list2; // ebx
  _DWORD *clonedList; // eax
  signed int result; // eax

  first = 1;
  orField = *(_DWORD *)(theNode + 68);
  list1 = 0;
  if ( !orField )
    return list1;
  do
  {
    while ( 1 )
    {
      andField = orField;
      list2 = 0;
      do
      {
        if ( *(_DWORD *)andField == 94 || *(_DWORD *)andField == 93 )
        {
          clonedList = Rules_ClonePatternPositionConstraintList(*(int **)(andField + 56));
          list2 = Rules_MergeConstraintListsByFieldIndex(list2, clonedList);
        }
        andField = *(_DWORD *)(andField + 64);
      }
      while ( andField );
      if ( !first )
        break;
      list1 = (int)list2;
      first = 0;
      orField = *(_DWORD *)(orField + 68);
      if ( !orField )
        return list1;
    }
    result = Rules_IntersectConstraintListsByFieldIndex(list1, (int)list2);
    list1 = result;
    orField = *(_DWORD *)(orField + 68);
  }
  while ( orField );
  return result;
}
// 4DE0CA: conditional instruction was optimized away because esi.4!=0
// 4DE0E6: variable 'v4' is possibly undefined

//----- (004DE130) --------------------------------------------------------
signed int  Rules_CheckRHSActionsAgainstCEConstraints(signed int result, int theLHS)
{
  int argNumber; // edi
  int theExpression; // esi
  int nextExpression; // ecx
  signed int exprPtr; // [esp+0h] [ebp-20h]
  int lastOne; // [esp+4h] [ebp-1Ch]
  int theFunction; // [esp+8h] [ebp-18h]

  if ( result )
  {
    exprPtr = result;
    while ( 2 )
    {
      argNumber = 1;
      theExpression = *(_DWORD *)(exprPtr + 6);
      if ( *(_WORD *)exprPtr == 10 )
      {
        lastOne = exprPtr;
        theFunction = *(_DWORD *)(exprPtr + 2);
      }
      else
      {
        theFunction = 0;
      }
      while ( theExpression )
      {
        if ( Rules_CheckFieldRestrictionAgainstRHSAction(theExpression, lastOne, theFunction, argNumber, theLHS) )
          return 1;
        *(_DWORD *)(theExpression + 10) = 0;
        ++argNumber;
        if ( Rules_CheckRHSActionsAgainstCEConstraints(theExpression, theLHS) )
          return 1;
        *(_DWORD *)(theExpression + 10) = nextExpression;
        theExpression = nextExpression;
      }
      exprPtr = *(_DWORD *)(exprPtr + 10);
      if ( exprPtr )
        continue;
      break;
    }
    return 0;
  }
  return result;
}
// 4DE141: conditional instruction was optimized away because eax.4!=0
// 4DE196: variable 'v7' is possibly undefined
// 4DE1B3: variable 'v5' is possibly undefined

//----- (004DE1D0) --------------------------------------------------------
signed int  Rules_CheckFieldRestrictionAgainstRHSAction(int theExpression, int lastOne, int theFunction, int argNumber, int theLHS)
{
  int errorFlag; // ebx
  _DWORD *v10; // ecx
  _DWORD *theCE; // eax
  int newParseNode; // eax
  int namedContextConstraint; // eax
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  int v20; // ecx
  int nextOne; // ebx
  int v22; // ecx
  _DWORD *v23; // ecx
  char *constraint4; // [esp+0h] [ebp-18h]
  _DWORD *constraint3; // [esp+4h] [ebp-14h]
  _BYTE *constraint1; // [esp+8h] [ebp-10h]

  errorFlag = 0;
  if ( *(_WORD *)theExpression != 15 || !theFunction )
    return 0;
  Rules_GetArgRestrictionType(theFunction, argNumber);
  constraint1 = Rules_ApplyPatternKeywordFlags();
  theCE = Rules_FindCEByIndex(*(_DWORD *)(theExpression + 2), v10);
  if ( theCE )
  {
    if ( *theCE == 16 )
    {
      newParseNode = Rules_CreateLHSParseNode();
      Rules_UpdateCETypeFlag(4u, newParseNode);
    }
    else if ( theCE[4] )
    {
      Rules_CloneLHSParseNode((int *)theCE[4]);
    }
    else
    {
      Rules_CreateLHSParseNode();
    }
  }
  namedContextConstraint = Rules_GetNamedContextValue(*(_DWORD *)(theExpression + 2));
  constraint3 = (_DWORD *)Rules_UnionConstraints(namedContextConstraint, v14);
  constraint4 = Rules_IntersectConstraints((int)constraint3, (int)constraint1);
  if ( Rules_ConstraintIsUnmatchable(constraint4) )
  {
    if ( Rules_StaticConstraintCheckingEnabled() )
    {
      Rules_PrintErrorID((int)aRulecstr, 3, 1);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aPreviousVariab, v15);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], *(_DWORD *)(*(_DWORD *)(theExpression + 2) + 16), v16);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aCausedTheTypeR, v17);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aForArgument_0, v18);
      Rules_PrintLongInteger(v19, argNumber);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aOfTheExpressio, v20);
      nextOne = *(_DWORD *)(lastOne + 10);
      *(_DWORD *)(lastOne + 10) = 0;
      Rules_PrintFieldExprList((signed int)g_IO_LogicalNameTable_WError[0], (__int16 *)lastOne);
      *(_DWORD *)(lastOne + 10) = nextOne;
      errorFlag = 1;
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aFoundInTheRule, v22);
    }
  }
  AST_DecrementNodeRefCount(constraint1);
  AST_DecrementNodeRefCount(v23);
  AST_DecrementNodeRefCount(constraint3);
  AST_DecrementNodeRefCount(constraint4);
  return errorFlag;
}
// 4DE212: variable 'v10' is possibly undefined
// 4DE245: variable 'v14' is possibly undefined
// 4DE292: variable 'v15' is possibly undefined
// 4DE2A2: variable 'v16' is possibly undefined
// 4DE2B1: variable 'v17' is possibly undefined
// 4DE2C0: variable 'v18' is possibly undefined
// 4DE2CC: variable 'v19' is possibly undefined
// 4DE2DB: variable 'v20' is possibly undefined
// 4DE308: variable 'v22' is possibly undefined
// 4DE318: variable 'v23' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];

//----- (004DE370) --------------------------------------------------------
_DWORD * Rules_BuildJoinTestExpressionChain(int logicalJoin, _DWORD *theLHS, _DWORD *lastNode)
{
  _DWORD *lastJoin; // esi
  int v4; // edx
  int currentDepth; // edi
  _DWORD *currentPattern; // ecx
  int depthCursor; // eax
  int patternEntity; // eax
  int logicalJoinCE; // ebx
  __int64 v10; // rax
  int rhsEntry; // ebp
  int existingJoin; // ecx
  int depthOffset; // ebp
  _WORD *newJoin; // eax
  int typeBits; // edx
  int v16; // ecx
  int v18; // ecx
  int joinStack[33]; // [esp+4h] [ebp-BCh] BYREF
  int savedLogicalJoin; // [esp+88h] [ebp-38h]
  BOOL isLogical; // [esp+8Ch] [ebp-34h]
  int entityType; // [esp+90h] [ebp-30h]
  int i; // [esp+94h] [ebp-2Ch]
  int patternDepth; // [esp+98h] [ebp-28h]
  int currentCE; // [esp+9Ch] [ebp-24h]
  int patternDepthOffset; // [esp+A0h] [ebp-20h]
  _DWORD *thePattern; // [esp+A4h] [ebp-1Ch]
  int tryToReuse; // [esp+A8h] [ebp-18h]

  savedLogicalJoin = logicalJoin;
  thePattern = theLHS;
  Rules_MergeRedundantFieldAccessNodes(theLHS, lastNode);
  lastJoin = 0;
  tryToReuse = v4;
  currentCE = v4;
  currentDepth = v4;
  for ( i = 0; thePattern; ++currentCE )
  {
    if ( !thePattern[17] )
      i = 1;
    currentPattern = thePattern;
    depthCursor = currentDepth;
    while ( currentDepth < currentPattern[11] )
    {
      ++depthCursor;
      ++currentDepth;
      joinStack[depthCursor - 1] = (int)lastJoin;
    }
    patternEntity = currentPattern[6];
    entityType = *(_DWORD *)(patternEntity + 8);
    logicalJoinCE = savedLogicalJoin;
    v10 = ((__int64 (*)(void))*(_DWORD *)(patternEntity + 24))();
    rhsEntry = v10;
    isLogical = currentCE == logicalJoinCE;
    if ( HIDWORD(v10) == 1 )
      LODWORD(v10) = *(_DWORD *)(v10 + 8);
    else
      LODWORD(v10) = lastJoin[5];
    patternDepth = thePattern[12];
    if ( tryToReuse == 1
      && Rules_FindExistingJoinTestNode((_DWORD *)v10, rhsEntry, thePattern[2] & 1, SHIDWORD(v10), isLogical, (__int16 *)thePattern[13], patternDepth, currentDepth, i, (int)&joinStack[1]) )
    {
      if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
        Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aJ, existingJoin);
      lastJoin = (_DWORD *)existingJoin;
    }
    else
    {
      joinStack[0] = thePattern[2] & 1;
      tryToReuse = 0;
      newJoin = (_WORD *)Rules_InternJoinTestNode(thePattern[13], lastJoin, 0, rhsEntry, joinStack[0]);
      typeBits = entityType & 7;
      *newJoin &= 0xFE3Fu;
      lastJoin = newJoin;
      *(_DWORD *)newJoin |= typeBits << 6;
    }
    depthOffset = 4 * currentDepth;
    patternDepthOffset = 4 * patternDepth;
    while ( depthOffset > patternDepthOffset )
    {
      depthOffset -= 4;
      --currentDepth;
      if ( !lastJoin[5] )
      {
        tryToReuse = 0;
        goto LABEL_19;
      }
      if ( tryToReuse )
      {
        if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
        {
          Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aJ, v16);
          lastJoin = (_DWORD *)lastJoin[5];
        }
        else
        {
          lastJoin = (_DWORD *)lastJoin[5];
        }
      }
      else
      {
LABEL_19:
        lastJoin = (_DWORD *)Rules_InternJoinTestNode(0, (_DWORD *)joinStack[depthOffset / 4u], 1, (int)lastJoin, 0);
      }
    }
    thePattern = (_DWORD *)thePattern[17];
  }
  if ( Rules_GetWatchItemState((int)aCompilations) != 1 || !Rules_GetLoadInProgress() )
    return lastJoin;
  Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_50E03C, v18);
  return lastJoin;
}
// 4DE3A3: variable 'v4' is possibly undefined
// 4DE4C8: variable 'v12' is possibly undefined
// 4DE5AF: variable 'v16' is possibly undefined
// 4DE616: variable 'v18' is possibly undefined
// 51A61C: using guessed type char *off_51A61C[3];

//----- (004DE630) --------------------------------------------------------
_DWORD * Rules_MergeRedundantFieldAccessNodes(_DWORD *result, _DWORD *lastNode)
{
  _DWORD *i; // ebx
  int scanNode; // ecx
  _DWORD *testCE; // ecx
  int v5; // edx
  int v6; // edx

  for ( i = result; i; i = (_DWORD *)i[17] )
  {
    if ( (i[2] & 1) != 0 )
    {
      scanNode = 0;
    }
    else
    {
      lastNode = i;
      scanNode = i[17];
    }
    while ( scanNode )
    {
      result = *(_DWORD **)(scanNode + 44);
      if ( result != (_DWORD *)i[11] || (*(_DWORD *)(scanNode + 8) & 1) != 0 )
      {
        lastNode = (_DWORD *)scanNode;
        scanNode = *(_DWORD *)(scanNode + 68);
      }
      else
      {
        if ( *(_DWORD *)scanNode == 80 )
          break;
        if ( *(_DWORD *)scanNode == 84 )
        {
          i[13] = AST_MergeFieldAccessNodes((_DWORD *)i[13], *(_DWORD **)(scanNode + 52));
          testCE[13] = 0;
          v5 = testCE[17];
          testCE[17] = 0;
          lastNode[17] = v5;
          lastNode[12] = testCE[12];
          result = (_DWORD *)AST_FreeNode((int)testCE);
          scanNode = v6;
        }
        else
        {
          Rules_ReportSystemError(scanNode, 1);
          result = (_DWORD *)IO_RunRouterExitCallbacks();
        }
      }
    }
  }
  return result;
}
// 4DE64C: variable 'v3' is possibly undefined
// 4DE691: variable 'v4' is possibly undefined
// 4DE6AA: variable 'v6' is possibly undefined

//----- (004DE6D0) --------------------------------------------------------
_DWORD * Rules_FindExistingJoinTestNode(
        _DWORD *listOfJoins,
        int rhsStruct,
        int negatedRHS,
        int firstJoin,
        int a5,
        __int16 *joinTest,
        int endDepth,
        int currentDepth,
        int isLastPattern,
        int joinStack)
{
  _DWORD *theJoin; // esi

  theJoin = listOfJoins;
  if ( !listOfJoins )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( rhsStruct == theJoin[4] && Rules_JoinTestNodeMatches((int)theJoin, firstJoin, a5, negatedRHS, joinTest, endDepth, currentDepth, isLastPattern, joinStack) )
        return theJoin;
      if ( !firstJoin )
        break;
      theJoin = (_DWORD *)theJoin[8];
      if ( !theJoin )
        return 0;
    }
    theJoin = (_DWORD *)theJoin[7];
  }
  while ( theJoin );
  return 0;
}

//----- (004DE750) --------------------------------------------------------
BOOL  Rules_JoinTestNodeMatches(
        int theJoin,
        int firstJoin,
        int a3,
        int negatedRHS,
        __int16 *joinTest,
        int endDepth,
        int currentDepth,
        int isLastPattern,
        int joinStack)
{
  int currentJoin; // esi
  int depthCursor; // ecx
  int stackPtr; // eax
  int v13; // eax

  currentJoin = theJoin;
  if ( firstJoin != (*(_DWORD *)theJoin & 1)
    || *(_DWORD *)theJoin << 28 >> 31 != negatedRHS
    || a3 == 1 && (*(_BYTE *)theJoin & 2) == 0 && *(_DWORD *)(theJoin + 8)
    || AST_NodeListsEqual(*(__int16 **)(theJoin + 12), joinTest) != 1 )
  {
    return 0;
  }
  stackPtr = joinStack + 4 * depthCursor;
  while ( endDepth < depthCursor )
  {
    currentJoin = *(_DWORD *)(currentJoin + 20);
    if ( !currentJoin || (*(_BYTE *)currentJoin & 4) == 0 || *(_DWORD *)(stackPtr - 8) != *(_DWORD *)(currentJoin + 24) )
      return 0;
    stackPtr -= 4;
    --depthCursor;
  }
  if ( isLastPattern && (*(_DWORD *)(currentJoin + 36) || *(_DWORD *)(currentJoin + 8)) )
    return 0;
  return isLastPattern || (v13 = *(_DWORD *)(currentJoin + 20)) == 0 || (*(_BYTE *)v13 & 4) == 0 || currentJoin != *(_DWORD *)(v13 + 16);
}
// 4DE79F: variable 'v10' is possibly undefined

//----- (004DE810) --------------------------------------------------------
int  Rules_InternJoinTestNode(int joinTest, _DWORD *lhsEntry, int joinFromTheRight, int rhsEntry, char negatedRHS)
{
  _DWORD *freeListEntry; // ecx
  signed int newJoin; // edx
  int joinNodeInit; // edx
  int v11; // ecx
  int hashedJoinTest; // eax
  int joinNode; // edx
  __int16 firstJoinFlags; // si
  int v16; // ecx
  char joinDepth; // al
  int incrementalResetFlag; // [esp+0h] [ebp-10h]

  if ( Rules_GetWatchItemState((int)aCompilations) == 1 && Rules_GetLoadInProgress() )
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aJ_0, v16);
  freeListEntry = *(_DWORD **)(g_ClipsMemoryTable + 160);
  if ( freeListEntry )
  {
    g_ClipsMemFreeListTemp = *(_DWORD *)(g_ClipsMemoryTable + 160);
    *(_DWORD *)(g_ClipsMemoryTable + 160) = *freeListEntry;
    newJoin = g_ClipsMemFreeListTemp;
  }
  else
  {
    newJoin = Mem_HeapAllocWithRetry(40);
  }
  *(_BYTE *)newJoin &= ~4u;
  *(_DWORD *)newJoin |= 4 * (joinFromTheRight & 1);
  *(_BYTE *)newJoin &= ~8u;
  *(_DWORD *)(newJoin + 8) = 0;
  *(_DWORD *)(newJoin + 20) = 0;
  *(_DWORD *)newJoin |= 8 * (negatedRHS & 1);
  incrementalResetFlag = Rules_GetIncrementalReset() & 1;
  *(_BYTE *)joinNodeInit &= ~0x10u;
  *(_DWORD *)joinNodeInit |= 16 * incrementalResetFlag;
  *(_BYTE *)joinNodeInit &= ~2u;
  *(_DWORD *)(joinNodeInit + 36) = 0;
  hashedJoinTest = AST_AddHashedNodeChain(joinTest, joinNodeInit, v11);
  *(_DWORD *)(joinNode + 12) = hashedJoinTest;
  *(_DWORD *)(joinNode + 24) = lhsEntry;
  if ( lhsEntry )
  {
    *(_BYTE *)joinNode &= ~1u;
    joinDepth = (*lhsEntry << 16 >> 25) + 1;
    *(_BYTE *)(joinNode + 1) &= 1u;
    *(_DWORD *)joinNode |= (joinDepth & 0x7F) << 9;
    *(_DWORD *)(joinNode + 28) = lhsEntry[5];
    lhsEntry[5] = joinNode;
  }
  else
  {
    firstJoinFlags = *(_WORD *)joinNode & 0x1FE;
    *(_DWORD *)(joinNode + 28) = 0;
    *(_WORD *)joinNode = firstJoinFlags;
    *(_WORD *)joinNode = firstJoinFlags | 0x201;
  }
  *(_DWORD *)(joinNode + 16) = rhsEntry;
  if ( joinFromTheRight )
  {
    *(_DWORD *)(joinNode + 32) = 0;
    *(_DWORD *)(rhsEntry + 20) = joinNode;
  }
  else
  {
    *(_DWORD *)(joinNode + 32) = *(_DWORD *)(rhsEntry + 8);
    *(_DWORD *)(rhsEntry + 8) = joinNode;
  }
  return joinNode;
}
// 4DE898: variable 'v10' is possibly undefined
// 4DE8AF: variable 'v11' is possibly undefined
// 4DE8B4: variable 'v13' is possibly undefined
// 4DE911: variable 'v16' is possibly undefined
// 51A61C: using guessed type char *off_51A61C[3];
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;

//----- (004DE9B0) --------------------------------------------------------
int ** Defgeneric_InitializeFromRestrictionString(int theDefgeneric, int a2)
{
  int **result; // eax
  _DWORD *v3; // ecx
  __int16 actionExpr; // [esp+0h] [ebp-14h] BYREF
  int **exprValue; // [esp+2h] [ebp-12h]
  int v6; // [esp+6h] [ebp-Eh]
  int v7; // [esp+Ah] [ebp-Ah]
  int v8; // [esp+10h] [ebp-4h]

  v8 = a2;
  result = Rules_MakeSymbol(*(_BYTE **)(*(_DWORD *)theDefgeneric + 16));
  if ( result )
  {
    actionExpr = 10;
    exprValue = result;
    v7 = 0;
    v6 = 0;
    return (int **)Method_ParseWildcardRestrictionString(v3, *(char **)((char *)result + 17), (int)v3, &actionExpr);
  }
  return result;
}
// 4DE9E9: variable 'v3' is possibly undefined
