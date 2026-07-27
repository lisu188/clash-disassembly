/* Generated from src/recovered/runtime/004D0560_legacy_runtime.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "runtime_internal.h"
#include "runtime_state.h"
#include "../state/state_shared.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (004D4DA0) --------------------------------------------------------
int  Class_PrintSlotBasicInfoTable(
        int logicalName,
        const char *slotNamePrintFormat,
        const char *buf,
        const char *overrideMessagePrintFormat,
        int theDefclass)
{
  char *headerFieldLabels; // esi
  const char *v7; // ecx
  const char *v8; // edi
  unsigned int nameLen; // kr04_4
  char *headerDest; // edi
  char v11; // al
  char v12; // al
  int v13; // ecx
  int v14; // ecx
  int result; // eax
  int slotDesc; // ebx
  char *multiplicityStr; // esi
  char *multiplicityDest; // edi
  char v19; // al
  char v20; // al
  const char *v21; // edi
  char *defaultTypeStr; // esi
  char *defaultTypeDest; // edi
  char v24; // al
  char v25; // al
  char *inheritStr; // esi
  char *inheritDest; // edi
  char v28; // al
  char v29; // al
  char *accessStr; // esi
  char *accessDest; // edi
  char v32; // al
  char v33; // al
  char *storageStr; // esi
  char *storageDest; // edi
  char v36; // al
  char v37; // al
  char *reactiveStr; // esi
  char *reactiveDest; // edi
  char v40; // al
  char v41; // al
  char *compositionStr; // esi
  char *compositionDest; // edi
  char v44; // al
  char v45; // al
  char *visibilityStr; // esi
  char *visibilityDest; // edi
  char v48; // al
  char v49; // al
  char *accessModeStr; // edx
  char *accessPadStr; // esi
  char *accessPadDest; // edi
  char v53; // al
  char v54; // al
  char *v55; // esi
  char *accessModeDest; // edi
  char v57; // al
  char v58; // al
  char *trailPadStr; // esi
  char *trailPadDest; // edi
  char v61; // al
  char v62; // al
  char *finalPadStr; // esi
  unsigned int lineLen; // kr34_4
  char *finalPadDest; // edi
  char v66; // al
  char v67; // al
  char *overrideMessage; // esi
  int v69; // ecx
  int v70; // ecx
  int slotOffset; // [esp+8h] [ebp-18h]
  unsigned int slotIndex; // [esp+Ch] [ebp-14h]

  headerFieldLabels = aFldDefPrpAccSt;
  sprintf_(buf, slotNamePrintFormat, aSlots_0);
  v8 = v7;
  nameLen = strlen(v7) + 1;
  headerDest = (char *)&v8[nameLen - 1];
  do
  {
    v11 = *headerFieldLabels;
    *headerDest = *headerFieldLabels;
    if ( !v11 )
      break;
    v12 = headerFieldLabels[1];
    headerFieldLabels += 2;
    headerDest[1] = v12;
    headerDest += 2;
  }
  while ( v12 );
  Output_Write(logicalName, (int)(intptr_t)buf, ~nameLen);
  sprintf_(buf, overrideMessagePrintFormat, aOvrdMsg);
  Output_Write(logicalName, (int)(intptr_t)buf, v13);
  Output_Write(logicalName, (int)(intptr_t)aSourceS, v14);
  result = theDefclass;
  slotIndex = 0;
  if ( *(_DWORD *)(uintptr_t)(theDefclass + 72) )
  {
    slotOffset = 0;
    do
    {
      slotDesc = *(_DWORD *)(uintptr_t)(slotOffset + *(_DWORD *)(uintptr_t)(theDefclass + 56));
      sprintf_(buf, slotNamePrintFormat, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotDesc + 8) + 12) + 16));
      if ( (*(_BYTE *)(uintptr_t)slotDesc & 2) != 0 )
        multiplicityStr = aMlt;
      else
        multiplicityStr = aSgl;
      multiplicityDest = (char *)&buf[strlen(buf)];
      do
      {
        v19 = *multiplicityStr;
        *multiplicityDest = *multiplicityStr;
        if ( !v19 )
          break;
        v20 = multiplicityStr[1];
        multiplicityStr += 2;
        multiplicityDest[1] = v20;
        multiplicityDest += 2;
      }
      while ( v20 );
      v21 = buf;
      if ( (*(_BYTE *)(uintptr_t)(slotDesc + 1) & 1) != 0 )
      {
        defaultTypeStr = aNil_5;
      }
      else
      {
        if ( (*(_BYTE *)(uintptr_t)slotDesc & 0x40) != 0 )
          defaultTypeStr = aDyn;
        else
          defaultTypeStr = aStc;
        v21 = buf;
      }
      defaultTypeDest = (char *)&v21[strlen(v21)];
      do
      {
        v24 = *defaultTypeStr;
        *defaultTypeDest = *defaultTypeStr;
        if ( !v24 )
          break;
        v25 = defaultTypeStr[1];
        defaultTypeStr += 2;
        defaultTypeDest[1] = v25;
        defaultTypeDest += 2;
      }
      while ( v25 );
      if ( (*(_BYTE *)(uintptr_t)slotDesc & 8) != 0 )
        inheritStr = aNil_5;
      else
        inheritStr = aInh;
      inheritDest = (char *)&buf[strlen(buf)];
      do
      {
        v28 = *inheritStr;
        *inheritDest = *inheritStr;
        if ( !v28 )
          break;
        v29 = inheritStr[1];
        inheritStr += 2;
        inheritDest[1] = v29;
        inheritDest += 2;
      }
      while ( v29 );
      if ( (*(_BYTE *)(uintptr_t)slotDesc & 0x20) != 0 )
      {
        accessStr = aInt_0;
      }
      else if ( (*(_BYTE *)(uintptr_t)slotDesc & 0x10) != 0 )
      {
        accessStr = aR_5;
      }
      else
      {
        accessStr = aRw;
      }
      accessDest = (char *)&buf[strlen(buf)];
      do
      {
        v32 = *accessStr;
        *accessDest = *accessStr;
        if ( !v32 )
          break;
        v33 = accessStr[1];
        accessStr += 2;
        accessDest[1] = v33;
        accessDest += 2;
      }
      while ( v33 );
      if ( (*(_BYTE *)(uintptr_t)slotDesc & 1) != 0 )
        storageStr = aShr;
      else
        storageStr = aLcl;
      storageDest = (char *)&buf[strlen(buf)];
      do
      {
        v36 = *storageStr;
        *storageDest = *storageStr;
        if ( !v36 )
          break;
        v37 = storageStr[1];
        storageStr += 2;
        storageDest[1] = v37;
        storageDest += 2;
      }
      while ( v37 );
      if ( (*(_BYTE *)(uintptr_t)(slotDesc + 1) & 2) != 0 )
        reactiveStr = aRct;
      else
        reactiveStr = aNil_5;
      reactiveDest = (char *)&buf[strlen(buf)];
      do
      {
        v40 = *reactiveStr;
        *reactiveDest = *reactiveStr;
        if ( !v40 )
          break;
        v41 = reactiveStr[1];
        reactiveStr += 2;
        reactiveDest[1] = v41;
        reactiveDest += 2;
      }
      while ( v41 );
      if ( (*(_BYTE *)(uintptr_t)slotDesc & 4) != 0 )
        compositionStr = aCmp;
      else
        compositionStr = aExc;
      compositionDest = (char *)&buf[strlen(buf)];
      do
      {
        v44 = *compositionStr;
        *compositionDest = *compositionStr;
        if ( !v44 )
          break;
        v45 = compositionStr[1];
        compositionStr += 2;
        compositionDest[1] = v45;
        compositionDest += 2;
      }
      while ( v45 );
      if ( (*(_BYTE *)(uintptr_t)(slotDesc + 1) & 4) != 0 )
        visibilityStr = aPub;
      else
        visibilityStr = aPrv;
      visibilityDest = (char *)&buf[strlen(buf)];
      do
      {
        v48 = *visibilityStr;
        *visibilityDest = *visibilityStr;
        if ( !v48 )
          break;
        v49 = visibilityStr[1];
        visibilityStr += 2;
        visibilityDest[1] = v49;
        visibilityDest += 2;
      }
      while ( v49 );
      accessModeStr = Class_SlotAccessModeString(slotDesc);
      if ( !accessModeStr[1] )
      {
        accessPadStr = asc_50CEE8;
        accessPadDest = (char *)&buf[strlen(buf)];
        do
        {
          v53 = *accessPadStr;
          *accessPadDest = *accessPadStr;
          if ( !v53 )
            break;
          v54 = accessPadStr[1];
          accessPadStr += 2;
          accessPadDest[1] = v54;
          accessPadDest += 2;
        }
        while ( v54 );
      }
      v55 = accessModeStr;
      accessModeDest = (char *)&buf[strlen(buf)];
      do
      {
        v57 = *v55;
        *accessModeDest = *v55;
        if ( !v57 )
          break;
        v58 = v55[1];
        v55 += 2;
        accessModeDest[1] = v58;
        accessModeDest += 2;
      }
      while ( v58 );
      if ( !accessModeStr[1] || !accessModeStr[2] )
      {
        trailPadStr = asc_50CEE8;
        trailPadDest = (char *)&buf[strlen(buf)];
        do
        {
          v61 = *trailPadStr;
          *trailPadDest = *trailPadStr;
          if ( !v61 )
            break;
          v62 = trailPadStr[1];
          trailPadStr += 2;
          trailPadDest[1] = v62;
          trailPadDest += 2;
        }
        while ( v62 );
      }
      finalPadStr = asc_50CEE8;
      lineLen = strlen(buf) + 1;
      finalPadDest = (char *)&buf[lineLen - 1];
      do
      {
        v66 = *finalPadStr;
        *finalPadDest = *finalPadStr;
        if ( !v66 )
          break;
        v67 = finalPadStr[1];
        finalPadStr += 2;
        finalPadDest[1] = v67;
        finalPadDest += 2;
      }
      while ( v67 );
      Output_Write(logicalName, (int)(intptr_t)buf, ~lineLen);
      if ( (*(_BYTE *)(uintptr_t)slotDesc & 0x10) != 0 )
        overrideMessage = aNil_6;
      else
        overrideMessage = (char *)(uintptr_t)*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotDesc + 12) + 16);
      sprintf_(buf, overrideMessagePrintFormat, overrideMessage);
      Output_Write(logicalName, (int)(intptr_t)buf, 0);
      Class_PrintSlotSourceClasses(logicalName, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotDesc + 8) + 12), v69, (unsigned __int16 *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotDesc + 4) + 46), 1);
      Output_Write(logicalName, (int)(intptr_t)asc_50CE14, v70);
      slotOffset += 4;
      result = ++slotIndex;
    }
    while ( slotIndex < *(_DWORD *)(uintptr_t)(theDefclass + 72) );
  }
  return result;
}
// 4D4DC7: variable 'v7' is possibly undefined
// 4D4E0B: variable 'v13' is possibly undefined
// 4D4E19: variable 'v14' is possibly undefined
// 4D50F3: variable 'v69' is possibly undefined
// 4D5101: variable 'v70' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004D51D0) --------------------------------------------------------
signed int  Class_PrintSlotSourceClasses(int logicalName, int slotName, int classIndex, unsigned __int16 *precedenceList, int a5 CLASH95_UNUSED)
{
  _BYTE *foundSlot; // eax
  int v9; // ecx
  _BYTE *slotDesc; // edx
  int v12; // ecx

  while ( 1 )
  {
    if ( classIndex == *precedenceList )
      return 0;
    foundSlot = (_BYTE *)(uintptr_t)Class_FindSlotBySymbol(*(_DWORD *)(uintptr_t)(*(_DWORD *)(precedenceList + 1) + 4 * classIndex), slotName);
    slotDesc = foundSlot;
    if ( foundSlot )
    {
      if ( (*foundSlot & 8) == 0 || v9 )
        break;
    }
    ++classIndex;
  }
  if ( (*slotDesc & 4) != 0 )
  {
    if ( Class_PrintSlotSourceClasses(logicalName, slotName, classIndex + 1, (int)(intptr_t)precedenceList, 0) )
      Output_Write(logicalName, (int)(intptr_t)asc_50CEE8, v12);
  }
  Class_PrintName(*(_DWORD *)(uintptr_t)(*(_DWORD *)(precedenceList + 1) + 4 * classIndex), 0);
  return 1;
}
// 4D5240: variable 'v12' is possibly undefined
// 4D5265: variable 'v9' is possibly undefined

//----- (004D5270) --------------------------------------------------------
signed int  Class_PrintSlotConstraintTable(
        int logicalName,
        const char *slotNamePrintFormat,
        int bufferSize,
        const char *buf,
        signed int theDefclass)
{
  char *srcPtr; // esi
  unsigned int bufLen; // kr04_4
  char *dstPtr; // edi
  char v8; // al
  char v9; // al
  signed int result; // eax
  int slotDesc; // eax
  char *theConstraint; // ebp
  int v13; // edx
  int v14; // ecx
  int v15; // ecx
  char *cardinalityMarker; // edx
  int v17; // edx
  int v18; // ecx
  char *v19; // esi
  char *v20; // edi
  char v21; // al
  char v22; // al
  char *v23; // esi
  char *v24; // edi
  char v25; // al
  char v26; // al
  char *v27; // esi
  char *v28; // edi
  char v29; // al
  char v30; // al
  char *v31; // esi
  char *v32; // edi
  char v33; // al
  char v34; // al
  char *v35; // esi
  char *v36; // edi
  char v37; // al
  char v38; // al
  char *v39; // esi
  char *v40; // edi
  char v41; // al
  char v42; // al
  char *v43; // esi
  char *v44; // edi
  char v45; // al
  char v46; // al
  char *v47; // esi
  char *v48; // edi
  char v49; // al
  char v50; // al
  char constraintFlags; // dh
  int v52; // ecx
  int v53; // ecx
  int v54; // ecx
  int slotIndex; // [esp+Ch] [ebp-18h]
  int i; // [esp+10h] [ebp-14h]

  srcPtr = aSymStrInnInaEx;
  sprintf_(buf, slotNamePrintFormat, aSlots_0);
  bufLen = strlen(buf) + 1;
  dstPtr = (char *)&buf[bufLen - 1];
  do
  {
    v8 = *srcPtr;
    *dstPtr = *srcPtr;
    if ( !v8 )
      break;
    v9 = srcPtr[1];
    srcPtr += 2;
    dstPtr[1] = v9;
    dstPtr += 2;
  }
  while ( v9 );
  Output_Write(logicalName, (int)(intptr_t)buf, ~bufLen);
  result = theDefclass;
  slotIndex = 0;
  if ( *(_DWORD *)(uintptr_t)(theDefclass + 72) )
  {
    for ( i = 0; ; i += 4 )
    {
      slotDesc = *(_DWORD *)(uintptr_t)(i + *(_DWORD *)(uintptr_t)(theDefclass + 56));
      theConstraint = (char *)(uintptr_t)*(_DWORD *)(uintptr_t)(slotDesc + 20);
      sprintf_(buf, slotNamePrintFormat, *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotDesc + 8) + 12) + 16));
      if ( theConstraint )
        break;
      IO_OpenStringDestination((int)(intptr_t)aDescribeClas_1, (const void *)(uintptr_t)v13, bufferSize);
      Output_Write((int)(intptr_t)aDescribeClas_1, (int)(intptr_t)aRngOo__Oo, v14);
      if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(i + *(_DWORD *)(uintptr_t)(theDefclass + 56)) & 2) != 0 )
      {
        cardinalityMarker = aCrd0__Oo;
LABEL_9:
        Output_Write((int)(intptr_t)aDescribeClas_1, (int)(intptr_t)cardinalityMarker, v15);
      }
LABEL_10:
      Output_Write((int)(intptr_t)aDescribeClas_1, (int)(intptr_t)asc_50CE14, v15);
      IO_CloseStringRouter((int)(intptr_t)aDescribeClas_1);
      result = Output_Write(logicalName, v17, v18);
      if ( (unsigned int)++slotIndex >= *(_DWORD *)(uintptr_t)(theDefclass + 72) )
        return result;
    }
    v19 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 30 >> 31, *(_DWORD *)theConstraint << 21 >> 31);
    v20 = (char *)&buf[strlen(buf)];
    do
    {
      v21 = *v19;
      *v20 = *v19;
      if ( !v21 )
        break;
      v22 = v19[1];
      v19 += 2;
      v20[1] = v22;
      v20 += 2;
    }
    while ( v22 );
    v23 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 29 >> 31, *(_DWORD *)theConstraint << 20 >> 31);
    v24 = (char *)&buf[strlen(buf)];
    do
    {
      v25 = *v23;
      *v24 = *v23;
      if ( !v25 )
        break;
      v26 = v23[1];
      v23 += 2;
      v24[1] = v26;
      v24 += 2;
    }
    while ( v26 );
    v27 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 26 >> 31, *(_DWORD *)theConstraint << 17 >> 31);
    v28 = (char *)&buf[strlen(buf)];
    do
    {
      v29 = *v27;
      *v28 = *v27;
      if ( !v29 )
        break;
      v30 = v27[1];
      v27 += 2;
      v28[1] = v30;
      v28 += 2;
    }
    while ( v30 );
    v31 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 25 >> 31, 0);
    v32 = (char *)&buf[strlen(buf)];
    do
    {
      v33 = *v31;
      *v32 = *v31;
      if ( !v33 )
        break;
      v34 = v31[1];
      v31 += 2;
      v32[1] = v34;
      v32 += 2;
    }
    while ( v34 );
    v35 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 24 >> 31, 0);
    v36 = (char *)&buf[strlen(buf)];
    do
    {
      v37 = *v35;
      *v36 = *v35;
      if ( !v37 )
        break;
      v38 = v35[1];
      v35 += 2;
      v36[1] = v38;
      v36 += 2;
    }
    while ( v38 );
    v39 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 23 >> 31, 0);
    v40 = (char *)&buf[strlen(buf)];
    do
    {
      v41 = *v39;
      *v40 = *v39;
      if ( !v41 )
        break;
      v42 = v39[1];
      v39 += 2;
      v40[1] = v42;
      v40 += 2;
    }
    while ( v42 );
    v43 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 27 >> 31, *(_DWORD *)theConstraint << 18 >> 31);
    v44 = (char *)&buf[strlen(buf)];
    do
    {
      v45 = *v43;
      *v44 = *v43;
      if ( !v45 )
        break;
      v46 = v43[1];
      v43 += 2;
      v44[1] = v46;
      v44 += 2;
    }
    while ( v46 );
    v47 = Class_ConstraintTypeMarker(theConstraint, *(_DWORD *)theConstraint << 28 >> 31, *(_DWORD *)theConstraint << 19 >> 31);
    v48 = (char *)&buf[strlen(buf)];
    do
    {
      v49 = *v47;
      *v48 = *v47;
      if ( !v49 )
        break;
      v50 = v47[1];
      v47 += 2;
      v48[1] = v50;
      v48 += 2;
    }
    while ( v50 );
    IO_OpenStringDestination((int)(intptr_t)aDescribeClas_1, &buf[strlen(buf)], bufferSize - (strlen(buf) + 1));
    constraintFlags = *theConstraint;
    if ( (*theConstraint & 0x10) != 0 || (constraintFlags & 8) != 0 || (constraintFlags & 1) != 0 )
    {
      Output_Write((int)(intptr_t)aDescribeClas_1, (int)(intptr_t)aRng, v15);
      Rules_PrintFieldExprList((signed int)(intptr_t)aDescribeClas_1, *(__int16 **)(theConstraint + 10));
      Output_Write((int)(intptr_t)aDescribeClas_1, (int)(intptr_t)a___0, v52);
      Rules_PrintFieldExprList((signed int)(intptr_t)aDescribeClas_1, *(__int16 **)(theConstraint + 14));
      Output_Write((int)(intptr_t)aDescribeClas_1, (int)(intptr_t)asc_50CF34, v53);
    }
    if ( (*(_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(i + *(_DWORD *)(uintptr_t)(theDefclass + 56)) & 2) == 0 )
      goto LABEL_10;
    Output_Write((int)(intptr_t)aDescribeClas_1, (int)(intptr_t)aCrd, v15);
    Rules_PrintFieldExprList((signed int)(intptr_t)aDescribeClas_1, *(__int16 **)(theConstraint + 18));
    Output_Write((int)(intptr_t)aDescribeClas_1, (int)(intptr_t)a___0, v54);
    Rules_PrintFieldExprList((signed int)(intptr_t)aDescribeClas_1, *(__int16 **)(theConstraint + 22));
    cardinalityMarker = asc_50CF40;
    goto LABEL_9;
  }
  return result;
}
// 4D5320: variable 'v13' is possibly undefined
// 4D532F: variable 'v14' is possibly undefined
// 4D534E: variable 'v15' is possibly undefined
// 4D537F: variable 'v17' is possibly undefined
// 4D537F: variable 'v18' is possibly undefined
// 4D55DD: variable 'v52' is possibly undefined
// 4D55F9: variable 'v53' is possibly undefined
// 4D563C: variable 'v54' is possibly undefined
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);

//----- (004D5670) --------------------------------------------------------
char * Class_ConstraintTypeMarker(_BYTE *theConstraint, int typeAllowed, int typeRestricted)
{
  if ( !typeAllowed && (*theConstraint & 1) == 0 )
    return asc_50CF94;
  if ( typeRestricted || (theConstraint[1] & 2) != 0 )
    return asc_50CF84;
  return asc_50CF8C;
}

//----- (004D56A0) --------------------------------------------------------
unsigned int  Class_ClassAbstractPCommand(int a1, double a2)
{
  unsigned int result; // eax
  int *theDefclass; // eax
  int v4; // ecx
  int argValue; // [esp-8h] [ebp-24h] BYREF
  int argDataObject; // [esp+0h] [ebp-1Ch]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  v7 = a1;
  result = Lexer_ParseValueList(1, &argValue, 2, a2);
  if ( result )
  {
    theDefclass = Class_LookupByQualifiedName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(argDataObject + 16));
    if ( theDefclass )
    {
      return (unsigned int)(theDefclass[5] << 29) >> 31;
    }
    else
    {
      Class_ReportLookupError(v4, *(_DWORD *)(uintptr_t)(argDataObject + 16));
      return 0;
    }
  }
  return result;
}
// 4D56F3: variable 'v4' is possibly undefined

//----- (004D5710) --------------------------------------------------------
unsigned int  Class_ClassReactivePCommand(int a1, double a2)
{
  unsigned int result; // eax
  int *theDefclass; // eax
  int v4; // ecx
  int argValue; // [esp-8h] [ebp-24h] BYREF
  int argDataObject; // [esp+0h] [ebp-1Ch]
  int v7 CLASH95_UNUSED; // [esp+14h] [ebp-8h]

  v7 = a1;
  result = Lexer_ParseValueList(1, &argValue, 2, a2);
  if ( result )
  {
    theDefclass = Class_LookupByQualifiedName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(argDataObject + 16));
    if ( theDefclass )
    {
      return (unsigned int)(theDefclass[5] << 28) >> 31;
    }
    else
    {
      Class_ReportLookupError(v4, *(_DWORD *)(uintptr_t)(argDataObject + 16));
      return 0;
    }
  }
  return result;
}
// 4D5763: variable 'v4' is possibly undefined

//----- (004D5780) --------------------------------------------------------
int * Class_ParseClassNameAndInheritFlag(int functionName, _DWORD *inheritFlag, double a3)
{
  int *result; // eax
  int v6; // ecx
  int *theDefclass; // ebp
  int secondArgValue; // ecx
  _DWORD argValue[2]; // [esp+0h] [ebp-2Ch] BYREF
  int argDataObject; // [esp+8h] [ebp-24h]

  *inheritFlag = 0;
  if ( Rules_RtnArgCount() )
  {
    result = (int *)(uintptr_t)Lexer_ParseValueList(1, argValue, 2, a3);
    if ( result )
    {
      theDefclass = Class_LookupByQualifiedName((_BYTE *)(uintptr_t)*(_DWORD *)(uintptr_t)(argDataObject + 16));
      if ( theDefclass )
      {
        if ( Rules_RtnArgCount() == 2 )
        {
          result = (int *)(uintptr_t)Lexer_ParseValueList(2, argValue, 2, a3);
          if ( result )
          {
            if ( !strcmp_(secondArgValue, aInherit_1) )
            {
              *inheritFlag = 1;
              return theDefclass;
            }
            else
            {
              Parser_ReportSyntaxError();
              Lexer_ErrorRecover(1);
              return 0;
            }
          }
        }
        else
        {
          return theDefclass;
        }
      }
      else
      {
        Class_ReportLookupError(v6, *(_DWORD *)(uintptr_t)(argDataObject + 16));
        return 0;
      }
    }
  }
  else
  {
    Rules_ExpectedCountError(functionName, 1);
    Lexer_ErrorRecover(1);
    return 0;
  }
  return result;
}
// 4D5807: variable 'v6' is possibly undefined
// 4D5834: variable 'v8' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004D5870) --------------------------------------------------------
_DWORD * Class_ClassSlotsCommand(unsigned int a1, double a2)
{
  int *theDefclass; // eax
  _DWORD *returnValue; // ecx
  unsigned int v5[3]; // [esp+0h] [ebp-Ch] BYREF

  v5[2] = a1;
  theDefclass = Class_ParseClassNameAndInheritFlag((int)(intptr_t)aClassSlots_0, v5, a2);
  if ( theDefclass )
    return Class_SlotsFunction((int)(intptr_t)theDefclass, returnValue, v5[0]);
  else
    return Rules_SetMultifieldErrorValue((int)(intptr_t)returnValue);
}
// 4D5889: variable 'v3' is possibly undefined

//----- (004D58B0) --------------------------------------------------------
__int16  Class_ClassSuperclassesCommand(int a1, double a2)
{
  int *theDefclass; // eax
  _DWORD *returnValue; // ecx
  int v5[3]; // [esp+0h] [ebp-Ch] BYREF

  v5[2] = a1;
  theDefclass = Class_ParseClassNameAndInheritFlag((int)(intptr_t)aClassSupercl_0, v5, a2);
  if ( theDefclass )
    return Class_SuperclassesFunction((int)(intptr_t)theDefclass, returnValue, v5[0]);
  else
    return (unsigned __int16)(intptr_t)Rules_SetMultifieldErrorValue((int)(intptr_t)returnValue);
}
// 4D58C9: variable 'v3' is possibly undefined

//----- (004D58F0) --------------------------------------------------------
void  Class_ClassSubclassesCommand(int a1, double a2)
{
  int *theDefclass; // eax
  int returnValue; // ecx
  int v4[3]; // [esp+0h] [ebp-Ch] BYREF

  v4[2] = a1;
  theDefclass = Class_ParseClassNameAndInheritFlag((int)(intptr_t)aClassSubclas_0, v4, a2);
  if ( theDefclass )
    Class_SubclassesFunction((int)(intptr_t)theDefclass, v4[0]);
  else
    Rules_SetMultifieldErrorValue(returnValue);
}
// 4D5909: variable 'v3' is possibly undefined

//----- (004D5930) --------------------------------------------------------
_DWORD * Class_GetDefmessageHandlerListCommand(int a1, double a2)
{
  int *theDefclass; // eax
  int returnValue; // ecx
  int v6[4]; // [esp+0h] [ebp-10h] BYREF

  v6[2] = a1;
  if ( !Rules_RtnArgCount() )
    return (_DWORD *)(uintptr_t)Class_MessageHandlerListFunction(0, 0);
  theDefclass = Class_ParseClassNameAndInheritFlag((int)(intptr_t)aGetDefmessag_0, v6, a2);
  if ( theDefclass )
    return (_DWORD *)(uintptr_t)Class_MessageHandlerListFunction((int)(intptr_t)theDefclass, v6[0]);
  else
    return Rules_SetMultifieldErrorValue(returnValue);
}
// 4D5953: variable 'v4' is possibly undefined

//----- (004D5980) --------------------------------------------------------
_DWORD * Class_SlotFacetsCommand(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotFacetsQuery, a3);
}

//----- (004D59A0) --------------------------------------------------------
_DWORD * Class_SlotSourcesCommand(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotSourcesQuery, a3);
}

//----- (004D59C0) --------------------------------------------------------
_DWORD * Class_SlotTypesCommand(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotTypesQuery, a3);
}

//----- (004D59E0) --------------------------------------------------------
_DWORD * Class_SlotAllowedValuesFunction(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotAllowedValuesQuery, a3);
}

//----- (004D5A00) --------------------------------------------------------
_DWORD * Class_SlotRangeFunction(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotRangeQuery, a3);
}

//----- (004D5A20) --------------------------------------------------------
_DWORD * Class_SlotCardinalityFunction(int a1, int *result, double a3)
{
  return Class_DispatchSlotQuery(a1, result, (int (*)(void))Class_SlotCardinalityQuery, a3);
}

//----- (004D5A40) --------------------------------------------------------
int  Class_IsAbstract(int theDefclass)
{
  return *(_DWORD *)(uintptr_t)(theDefclass + 20) << 29 >> 31;
}

//----- (004D5A60) --------------------------------------------------------
_DWORD * Class_SlotsFunction(int theDefclass, _DWORD *returnValue, unsigned int inheritFlag)
{
  unsigned int v3; // esi
  signed int slotCount; // ebx
  _DWORD *result; // eax
  int returnObj; // edx
  _DWORD *classPtr; // ecx
  unsigned int templateIndex; // ebx
  int templateOffset; // esi
  int slotTemplate; // edi
  int slotOffset; // ebx
  int slotName; // [esp+0h] [ebp-18h]

  v3 = inheritFlag;
  if ( inheritFlag )
    slotCount = *(_DWORD *)(uintptr_t)(theDefclass + 72);
  else
    slotCount = *(_DWORD *)(uintptr_t)(theDefclass + 64);
  returnValue[1] = 4;
  returnValue[4] = slotCount - 1;
  returnValue[3] = 0;
  result = Rules_CreateEphemeralMultifield(slotCount);
  *(_DWORD *)(uintptr_t)(returnObj + 8) = result;
  if ( slotCount )
  {
    if ( v3 )
    {
      templateIndex = 0;
      if ( classPtr[18] )
      {
        templateOffset = 0;
        result = 0;
        do
        {
          *(_WORD *)((char *)result + *(_DWORD *)(uintptr_t)(returnObj + 8) + 14) = 2;
          slotTemplate = *(_DWORD *)(uintptr_t)(classPtr[14] + templateOffset);
          templateOffset += 4;
          ++templateIndex;
          *(_DWORD *)((char *)result + *(_DWORD *)(uintptr_t)(returnObj + 8) + 16) = *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(slotTemplate + 8) + 12);
          result = (_DWORD *)((char *)result + 6);
        }
        while ( templateIndex < classPtr[18] );
      }
    }
    else if ( classPtr[16] )
    {
      slotOffset = 0;
      result = 0;
      do
      {
        *(_WORD *)((char *)result + *(_DWORD *)(uintptr_t)(returnObj + 8) + 14) = 2;
        slotName = *(_DWORD *)(uintptr_t)(classPtr[13] + slotOffset + 8);
        slotOffset += 44;
        *(_DWORD *)((char *)result + *(_DWORD *)(uintptr_t)(returnObj + 8) + 16) = *(_DWORD *)(uintptr_t)(slotName + 12);
        ++v3;
        result = (_DWORD *)((char *)result + 6);
      }
      while ( v3 < classPtr[16] );
    }
  }
  return result;
}
// 4D5A91: variable 'v6' is possibly undefined
// 4D5A9C: variable 'v7' is possibly undefined

//----- (004D5B40) --------------------------------------------------------
int  Class_MessageHandlerListFunction(int theDefclass, int inheritFlag)
{
  int currentClass; // ebp
  _DWORD *returnValue; // ecx
  int i; // ebx
  int precedenceCount; // edx
  int superclassLimit; // edi
  int superclassIndex; // eax
  int *precedenceList; // edx
  int precClass; // esi
  _DWORD *multifield; // eax
  int v12; // ecx
  int result; // eax
  int superclassLimit2; // eax
  int sourceClass; // ebx
  int destBaseIndex; // edx
  int fieldIndex; // edx
  unsigned int handlerIndex; // edi
  int handlerOffset; // esi
  int classNameSymbol; // eax
  int v21; // ecx
  int v22; // edx
  signed int *handlerTypeSymbol; // eax
  int v24; // edx
  int fieldOffset; // [esp+4h] [ebp-38h]
  int savedNext; // [esp+10h] [ebp-2Ch]
  int firstClass; // [esp+14h] [ebp-28h]
  int fieldCount; // [esp+18h] [ebp-24h]
  int precedenceEnd; // [esp+1Ch] [ebp-20h]
  int j; // [esp+20h] [ebp-1Ch]
  int fieldsFilled; // [esp+24h] [ebp-18h]
  int precedenceOffset; // [esp+28h] [ebp-14h]

  if ( theDefclass )
  {
    currentClass = theDefclass;
    savedNext = Class_GetNextRecord(theDefclass);
    Rules_SetConstructNextInModule(theDefclass, 0);
  }
  else
  {
    inheritFlag = 0;
    currentClass = Class_GetNextRecord(0);
    savedNext = Class_GetNextRecord(currentClass);
  }
  firstClass = currentClass;
  for ( i = 0; currentClass; currentClass = Class_GetNextRecord(currentClass) )
  {
    if ( inheritFlag )
      precedenceCount = *(unsigned __int16 *)(uintptr_t)(currentClass + 46);
    else
      precedenceCount = 1;
    superclassLimit = precedenceCount;
    superclassIndex = 0;
    if ( precedenceCount > 0 )
    {
      precedenceList = (int *)(uintptr_t)*(_DWORD *)(uintptr_t)(currentClass + 48);
      do
      {
        precClass = *precedenceList++;
        ++superclassIndex;
        i += *(_DWORD *)(uintptr_t)(precClass + 96);
      }
      while ( superclassIndex < superclassLimit );
    }
  }
  returnValue[1] = 4;
  returnValue[3] = 0;
  fieldCount = 3 * i;
  returnValue[4] = 3 * i - 1;
  multifield = Rules_CreateEphemeralMultifield(3 * i);
  *(_DWORD *)(uintptr_t)(v12 + 8) = multifield;
  result = firstClass;
  fieldsFilled = 0;
  for ( j = firstClass; result; j = result )
  {
    if ( inheritFlag )
      superclassLimit2 = *(unsigned __int16 *)(uintptr_t)(j + 46);
    else
      superclassLimit2 = 1;
    if ( superclassLimit2 > 0 )
    {
      precedenceOffset = 0;
      precedenceEnd = 4 * superclassLimit2;
      do
      {
        sourceClass = *(_DWORD *)(uintptr_t)(precedenceOffset + *(_DWORD *)(uintptr_t)(j + 48));
        if ( inheritFlag )
          destBaseIndex = fieldCount - 3 * *(_DWORD *)(uintptr_t)(sourceClass + 96) - fieldsFilled;
        else
          destBaseIndex = fieldsFilled;
        fieldIndex = destBaseIndex + 1;
        handlerIndex = 0;
        if ( *(_DWORD *)(uintptr_t)(sourceClass + 96) )
        {
          handlerOffset = 0;
          do
          {
            fieldOffset = 6 * (fieldIndex - 1);
            *(_WORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v12 + 8) + fieldOffset + 14) = 2;
            classNameSymbol = Rules_GetConstructNameSymbol(sourceClass);
            *(_DWORD *)(uintptr_t)(fieldOffset + *(_DWORD *)(uintptr_t)(v21 + 8) + 16) = classNameSymbol;
            *(_WORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(v21 + 8) + 6 * v22 + 14) = 2;
            *(_DWORD *)(uintptr_t)(6 * v22 + *(_DWORD *)(uintptr_t)(v21 + 8) + 16) = *(_DWORD *)(uintptr_t)(handlerOffset + *(_DWORD *)(uintptr_t)(sourceClass + 88) + 8);
            *(_WORD *)(uintptr_t)(6 * (v22 + 1) + *(_DWORD *)(uintptr_t)(v21 + 8) + 14) = 2;
            handlerTypeSymbol = Str_Intern(g_MessageHandlerTypeNames[*(_DWORD *)(uintptr_t)(handlerOffset + *(_DWORD *)(uintptr_t)(sourceClass + 88)) << 29 >> 30], v21);
            ++handlerIndex;
            handlerOffset += 36;
            *(_DWORD *)(uintptr_t)(6 * (v24 - 1) + *(_DWORD *)(uintptr_t)(v12 + 8) + 16) = handlerTypeSymbol;
            fieldIndex = v24 + 1;
          }
          while ( handlerIndex < *(_DWORD *)(uintptr_t)(sourceClass + 96) );
        }
        fieldsFilled += 3 * *(_DWORD *)(uintptr_t)(sourceClass + 96);
        precedenceOffset += 4;
      }
      while ( precedenceOffset < precedenceEnd );
    }
    result = Class_GetNextRecord(j);
  }
  if ( firstClass )
    return Rules_SetConstructNextInModule(firstClass, savedNext);
  return result;
}
// 4D5BB0: variable 'v4' is possibly undefined
// 4D5BD3: variable 'v12' is possibly undefined
// 4D5C61: variable 'v21' is possibly undefined
// 4D5C6F: variable 'v22' is possibly undefined
// 4D5CF4: variable 'v24' is possibly undefined
// 51AD3C: using guessed type char *off_51AD3C[4];

//----- (004D5DC0) --------------------------------------------------------
__int16  Class_SuperclassesFunction(int theDefclass, _DWORD *result, int inheritFlag)
{
  int startOffset; // edx
  unsigned __int16 *classLinks; // edi
  signed int linkCount; // eax
  _DWORD *v7; // eax
  unsigned int v8; // edx
  int lastIndex; // ecx
  unsigned int linkIndex; // ecx
  int linkOffset; // ebx
  int fieldOffset; // edx
  int v13; // edx
  int fieldAddr; // ebp
  int v15; // ecx

  if ( inheritFlag )
  {
    startOffset = 1;
    classLinks = (unsigned __int16 *)(uintptr_t)(theDefclass + 46);
  }
  else
  {
    classLinks = (unsigned __int16 *)(uintptr_t)(theDefclass + 34);
    startOffset = 0;
  }
  result[1] = 4;
  result[3] = 0;
  linkCount = *classLinks - startOffset;
  result[4] = linkCount - 1;
  v7 = Rules_CreateEphemeralMultifield(linkCount);
  lastIndex = result[4];
  result[2] = v7;
  if ( lastIndex != -1 )
  {
    linkIndex = v8;
    linkOffset = 4 * v8;
    fieldOffset = 0;
    LOWORD(v7) = *classLinks;
    if ( linkIndex < *classLinks )
    {
      do
      {
        *(_WORD *)(uintptr_t)(fieldOffset + result[2] + 14) = 2;
        v7 = (_DWORD *)(uintptr_t)Rules_GetConstructNameSymbol(*(_DWORD *)(uintptr_t)(linkOffset + *(_DWORD *)(classLinks + 1)));
        linkOffset += 4;
        fieldAddr = v13 + result[2];
        fieldOffset = v13 + 6;
        *(_DWORD *)(uintptr_t)(fieldAddr + 16) = v7;
        LOWORD(v7) = *classLinks;
      }
      while ( v15 + 1 < (unsigned int)*classLinks );
    }
  }
  return (__int16)(intptr_t)v7;
}
// 4D5DFD: variable 'v8' is possibly undefined
// 4D5E39: variable 'v13' is possibly undefined
// 4D5E3B: variable 'v15' is possibly undefined

//----- (004D5E50) --------------------------------------------------------
void  Class_SubclassesFunction(int theDefclass, int inheritFlag)
{
  signed int traversalID; // eax
  _DWORD *returnValue; // ecx
  signed int subclassCount; // edx
  _DWORD *multifield; // eax
  int v7; // ecx
  int v8; // edx
  signed int secondTraversalID; // eax
  int v10; // ecx

  traversalID = Class_NewTraversalID();
  if ( traversalID != -1 )
  {
    Class_CountSubclasses(theDefclass, inheritFlag, traversalID);
    Class_ReleaseTraversalID();
    returnValue[1] = 4;
    returnValue[4] = subclassCount - 1;
    returnValue[3] = 0;
    multifield = Rules_CreateEphemeralMultifield(subclassCount);
    *(_DWORD *)(uintptr_t)(v7 + 8) = multifield;
    if ( v8 )
    {
      secondTraversalID = Class_NewTraversalID();
      if ( secondTraversalID != -1 )
      {
        Class_CollectSubclassNames(*(_DWORD *)(uintptr_t)(v10 + 8), 1, inheritFlag, theDefclass, secondTraversalID);
        Class_ReleaseTraversalID();
      }
    }
  }
}
// 4D5E7B: variable 'v4' is possibly undefined
// 4D5E82: variable 'v5' is possibly undefined
// 4D5E94: variable 'v7' is possibly undefined
// 4D5E99: variable 'v8' is possibly undefined
// 4D5EAD: variable 'v10' is possibly undefined

//----- (004D5EC0) --------------------------------------------------------
signed int * Class_SlotFacetsQuery(int theDefclass, _BYTE *slotName, int returnValue)
{
  signed int *result; // eax
  _BYTE *slotDesc; // ecx
  int i; // eax
  char *cardinalityStr; // eax
  _BYTE *v7; // ecx
  char *defaultModeStr; // eax
  _BYTE *v9; // ecx
  char *inheritStr; // eax
  _BYTE *v11; // ecx
  char *accessStr; // eax
  _BYTE *v13; // ecx
  char *sharingStr; // eax
  int v15; // ecx
  char *reactiveStr; // eax
  _BYTE *v17; // ecx
  char *compositeStr; // eax
  int v19; // ecx
  char *visibilityStr; // eax
  int v21; // ecx
  char *accessorStr; // eax
  int v23; // ecx
  int v24; // ecx

  result = (signed int *)(uintptr_t)Class_ResolveNamedSlot(returnValue, theDefclass, slotName);
  if ( result )
  {
    *(_DWORD *)(uintptr_t)(returnValue + 16) = 9;
    *(_DWORD *)(uintptr_t)(returnValue + 8) = Rules_CreateEphemeralMultifield(10);
    for ( i = 0; i != 60; *(_WORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + i + 8) = 2 )
      i += 6;
    if ( (*slotDesc & 2) != 0 )
      cardinalityStr = aMlt_0;
    else
      cardinalityStr = aSgl_0;
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + 16) = Str_Intern(cardinalityStr, (int)(intptr_t)slotDesc);
    if ( (v7[1] & 1) != 0 )
    {
      defaultModeStr = aNil_7;
    }
    else if ( (*v7 & 0x40) != 0 )
    {
      defaultModeStr = aDyn_0;
    }
    else
    {
      defaultModeStr = aStc_0;
    }
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + 22) = Str_Intern(defaultModeStr, (int)(intptr_t)v7);
    if ( (*v9 & 8) != 0 )
      inheritStr = aNil_7;
    else
      inheritStr = aInh_0;
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + 28) = Str_Intern(inheritStr, (int)(intptr_t)v9);
    if ( (*v11 & 0x20) != 0 )
    {
      accessStr = aInt_1;
    }
    else if ( (*v11 & 0x10) != 0 )
    {
      accessStr = aR_9;
    }
    else
    {
      accessStr = aRw_1;
    }
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + 34) = Str_Intern(accessStr, (int)(intptr_t)v11);
    if ( (*v13 & 1) != 0 )
      sharingStr = aShr_0;
    else
      sharingStr = aLcl_0;
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + 40) = Str_Intern(sharingStr, (int)(intptr_t)v13);
    if ( (*(_BYTE *)(uintptr_t)(v15 + 1) & 2) != 0 )
      reactiveStr = aRct_0;
    else
      reactiveStr = aNil_7;
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + 46) = Str_Intern(reactiveStr, v15);
    if ( (*v17 & 4) != 0 )
      compositeStr = aCmpFacet;
    else
      compositeStr = aExcFacet;
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + 52) = Str_Intern(compositeStr, (int)(intptr_t)v17);
    if ( (*(_BYTE *)(uintptr_t)(v19 + 1) & 4) != 0 )
      visibilityStr = aPubFacet;
    else
      visibilityStr = aPrvFacet;
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + 58) = Str_Intern(visibilityStr, v19);
    accessorStr = Class_SlotAccessModeString(v21);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + 64) = Str_Intern(accessorStr, v23);
    if ( (*(_BYTE *)(uintptr_t)v24 & 0x10) != 0 )
      result = Str_Intern(aNil_7, v24);
    else
      result = *(signed int **)(uintptr_t)(v24 + 12);
    *(_DWORD *)(uintptr_t)(*(_DWORD *)(uintptr_t)(returnValue + 8) + 70) = result;
  }
  return result;
}
// 4D5F12: variable 'v4' is possibly undefined
// 4D5F2B: variable 'v7' is possibly undefined
// 4D5F45: variable 'v9' is possibly undefined
// 4D5F5E: variable 'v11' is possibly undefined
// 4D5F79: variable 'v13' is possibly undefined
// 4D5F92: variable 'v15' is possibly undefined
// 4D5FAC: variable 'v17' is possibly undefined
// 4D5FC5: variable 'v19' is possibly undefined
// 4D5FE1: variable 'v21' is possibly undefined
// 4D5FE6: variable 'v23' is possibly undefined
// 4D5FF1: variable 'v24' is possibly undefined
// 50D0A0: using guessed type _UNKNOWN *off_50D0A0;

//----- (004D6090) --------------------------------------------------------
_DWORD * Class_SlotSourcesQuery(int theDefclass, _BYTE *slotName, int a3)
{
  _DWORD *result; // eax
  _DWORD *freeNode; // edx
  signed int classCount; // ecx
  int *listNode; // eax
  int ownerClass; // edx
  int precedenceIndex; // esi
  int i; // edi
  int classRecord; // eax
  int sourceClass; // ebx
  _BYTE *foundSlot; // eax
  _BYTE *inheritedSlot; // ebp
  _DWORD *v14; // edx
  int *newNode; // eax
  int *curEntry; // ebx
  _DWORD *multifield; // eax
  int v18; // edx
  int fieldOffset; // edx
  int classNameSymbol; // eax
  int v21; // edx
  _DWORD *slotDesc; // [esp+4h] [ebp-10h]
  int *nameList; // [esp+8h] [ebp-Ch]

  result = (_DWORD *)(uintptr_t)Class_ResolveNamedSlot(a3, theDefclass, slotName);
  slotDesc = result;
  if ( result )
  {
    freeNode = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
    classCount = 1;
    if ( freeNode )
    {
      g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
      *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *freeNode;
      listNode = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
    }
    else
    {
      listNode = (int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
    }
    ownerClass = slotDesc[1];
    listNode[1] = 0;
    nameList = listNode;
    *listNode = ownerClass;
    if ( (*(_BYTE *)slotDesc & 4) != 0 )
    {
      precedenceIndex = 1;
      for ( i = 4; ; i += 4 )
      {
        classRecord = slotDesc[1];
        if ( precedenceIndex >= *(unsigned __int16 *)(uintptr_t)(classRecord + 46) )
          break;
        sourceClass = *(_DWORD *)(uintptr_t)(i + *(_DWORD *)(uintptr_t)(classRecord + 48));
        foundSlot = (_BYTE *)(uintptr_t)Class_FindSlotBySymbol(sourceClass, *(_DWORD *)(uintptr_t)(slotDesc[2] + 12));
        inheritedSlot = foundSlot;
        if ( foundSlot )
        {
          if ( (*foundSlot & 8) == 0 )
          {
            v14 = (_DWORD *)(uintptr_t)*(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
            if ( v14 )
            {
              g_ClipsMemFreeListTemp = *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32);
              *(_DWORD *)(uintptr_t)(g_ClipsMemoryTable + 32) = *v14;
              newNode = (int *)(uintptr_t)g_ClipsMemFreeListTemp;
            }
            else
            {
              newNode = (int *)(uintptr_t)Mem_HeapAllocWithRetry((_DWORD *)8);
            }
            *newNode = sourceClass;
            newNode[1] = (int)(intptr_t)nameList;
            ++classCount;
            nameList = newNode;
            if ( (*inheritedSlot & 4) == 0 )
              break;
          }
        }
        ++precedenceIndex;
      }
    }
    *(_DWORD *)(uintptr_t)(a3 + 16) = classCount - 1;
    curEntry = nameList;
    multifield = Rules_CreateEphemeralMultifield(classCount);
    *(_DWORD *)(uintptr_t)(v18 + 8) = multifield;
    if ( nameList )
    {
      fieldOffset = 0;
      do
      {
        *(_WORD *)(uintptr_t)(fieldOffset + *(_DWORD *)(uintptr_t)(a3 + 8) + 14) = 2;
        classNameSymbol = Rules_GetConstructNameSymbol(*curEntry);
        *(_DWORD *)(uintptr_t)(v21 + *(_DWORD *)(uintptr_t)(a3 + 8) + 16) = classNameSymbol;
        fieldOffset = v21 + 6;
        curEntry = (int *)(uintptr_t)curEntry[1];
      }
      while ( curEntry );
    }
    return Mem_ReturnListToFreePool(nameList);
  }
  return result;
}
// 4D6177: variable 'v5' is possibly undefined
// 4D619E: variable 'v18' is possibly undefined
// 4D61C3: variable 'v21' is possibly undefined
// 54DBA8: using guessed type int dword_54DBA8;
// 54DBAC: using guessed type int dword_54DBAC;
