/* Generated from src/recovered/rules/clips/004ACB00_compiler.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004B2EB0) --------------------------------------------------------
signed int  Rules_CheckFieldExprListAgainstConstraint(int *theExpression, int theConstraint)
{
  int *exprCursor; // edx
  int minFields; // ecx
  int i; // esi
  int v7; // edx
  int *checkCursor; // ecx
  signed int result; // eax
  int v10; // ecx
  char returnTypeChar; // bl

  exprCursor = theExpression;
  minFields = 0;
  for ( i = 0; exprCursor; exprCursor = *(int **)(v7 + 10) )
  {
    if ( Rules_TagIsConstantType(*(__int16 *)exprCursor)
      || *(_WORD *)v7 == 10 && (returnTypeChar = *(_BYTE *)(*(_DWORD *)(v7 + 2) + 8), returnTypeChar != 109) && returnTypeChar != 117 )
    {
      ++minFields;
    }
    else
    {
      i = -1;
    }
  }
  if ( !i )
    i = minFields;
  if ( !Method_ParamRangeInBounds(minFields, i, theConstraint) )
    return 5;
  checkCursor = theExpression;
  if ( !theExpression )
    return 0;
  while ( 1 )
  {
    result = Rules_CheckValueAgainstConstraint(*(__int16 *)checkCursor, *(int *)((char *)checkCursor + 2), theConstraint);
    if ( result )
      break;
    checkCursor = *(int **)(v10 + 10);
    if ( !checkCursor )
      return 0;
  }
  return result;
}
// 4B2ECF: variable 'v5' is possibly undefined
// 4B2ED0: variable 'v7' is possibly undefined
// 4B2F03: variable 'v10' is possibly undefined

//----- (004B2F40) --------------------------------------------------------
signed int  Rules_CheckExprTreeAgainstConstraint(__int16 *theExpression, int theConstraint)
{
  signed int result; // eax
  int v5; // ecx
  int v6; // ecx

  result = 0;
  if ( theConstraint && theExpression )
  {
    do
    {
      result = Rules_CheckValueAgainstConstraint(*theExpression, *(_DWORD *)(theExpression + 1), theConstraint);
      if ( result )
        break;
      result = Rules_CheckExprTreeAgainstConstraint(*(_DWORD *)(v5 + 6), theConstraint);
      if ( result )
        break;
      theExpression = *(__int16 **)(v6 + 10);
    }
    while ( theExpression );
  }
  return result;
}
// 4B2F68: variable 'v5' is possibly undefined
// 4B2F74: variable 'v6' is possibly undefined

//----- (004B2F80) --------------------------------------------------------
char * Rules_ConstraintIsUnmatchable(char *result)
{
  char typeFlags; // dl
  char highFlags; // dh

  if ( result )
  {
    typeFlags = *result;
    result = (char *)((*result & 1) == 0
                   && (typeFlags & 2) == 0
                   && (typeFlags & 4) == 0
                   && (typeFlags & 8) == 0
                   && (typeFlags & 0x10) == 0
                   && (typeFlags & 0x20) == 0
                   && (typeFlags & 0x40) == 0
                   && (highFlags = result[1], highFlags >= 0)
                   && typeFlags >= 0
                   && (highFlags & 1) == 0);
  }
  return result;
}

//----- (004B2FC7) --------------------------------------------------------
int  IO_ScanfGetChar(int (**streamOps)(void))
{
  return (*streamOps)();
}

//----- (004B2FCE) --------------------------------------------------------
int __fastcall IO_ScanfUngetChar(int ch, int streamOps)
{
  return (*(int (__thiscall **)(int))(streamOps + 4))(ch);
}

//----- (004B2FD6) --------------------------------------------------------
signed int  IO_ScanfParseFormat(int streamContext, unsigned __int8 *formatString, int *argList)
{
  int assignedCount; // ebp
  int charsConsumed; // edi
  unsigned __int8 *formatCharPtr; // ebx
  int formatChar; // ebx
  int v8; // ecx
  unsigned __int8 *specEnd; // eax
  unsigned int convChar; // ebx
  bool isHexConv; // zf
  int radix; // ebx
  int v13; // eax
  int fieldResult; // eax
  unsigned __int8 *formatPtr; // [esp+0h] [ebp-18h] BYREF
  int argCursor[5]; // [esp+4h] [ebp-14h] BYREF

  formatPtr = formatString;
  argCursor[0] = *argList;
  assignedCount = 0;
  charsConsumed = 0;
  *(_BYTE *)(streamContext + 16) &= ~2u;
  while ( 1 )
  {
    formatCharPtr = formatPtr++;
    formatChar = *formatCharPtr;
    if ( !formatChar )
      break;
    if ( (IsTable[(unsigned __int8)(formatChar + 1)] & 2) != 0 )
    {
      charsConsumed += IO_ScanfSkipWhitespace(streamContext);
      goto LABEL_64;
    }
    if ( formatChar != 37 )
    {
      if ( IO_ScanfGetChar((int (**)(void))streamContext) != formatChar )
        goto LABEL_7;
LABEL_63:
      ++charsConsumed;
      goto LABEL_64;
    }
    specEnd = IO_ScanfParseFieldSpec(formatPtr, streamContext);
    formatPtr = specEnd;
    convChar = *specEnd;
    if ( *specEnd )
      formatPtr = specEnd + 1;
    if ( convChar < 0x64 )
    {
      if ( convChar < 0x47 )
      {
        if ( convChar < 0x43 )
        {
          if ( convChar != 37 )
            goto LABEL_64;
          if ( IO_ScanfGetChar((int (**)(void))streamContext) != 37 )
          {
LABEL_7:
            if ( (*(_BYTE *)(streamContext + 16) & 2) == 0 )
              IO_ScanfUngetChar(v8, streamContext);
            break;
          }
          goto LABEL_63;
        }
        if ( convChar <= 0x43 )
        {
          *(_BYTE *)(streamContext + 16) |= 0x20u;
LABEL_57:
          fieldResult = IO_ScanfReadCharField(streamContext, argCursor, (_WORD *)streamContext);
LABEL_58:
          if ( fieldResult <= 0 )
            break;
          charsConsumed += fieldResult;
          if ( (*(_BYTE *)(streamContext + 16) & 1) != 0 )
            ++assignedCount;
          goto LABEL_64;
        }
        if ( convChar == 69 )
        {
LABEL_52:
          IO_ScanfReadFloatField(streamContext, argCursor);
          goto LABEL_58;
        }
      }
      else
      {
        if ( convChar <= 0x47 )
          goto LABEL_52;
        if ( convChar < 0x58 )
        {
          if ( convChar == 83 )
          {
            *(_BYTE *)(streamContext + 16) |= 0x20u;
LABEL_54:
            IO_ScanfReadStringField(streamContext, argCursor, (unsigned __int8 *)streamContext);
            goto LABEL_58;
          }
        }
        else
        {
          if ( convChar <= 0x58 )
          {
LABEL_51:
            radix = 16;
LABEL_46:
            v13 = streamContext;
LABEL_47:
            fieldResult = IO_ScanfReadIntegerField(v13, argCursor, radix);
            goto LABEL_58;
          }
          if ( convChar >= 0x5B )
          {
            if ( convChar <= 0x5B )
            {
              fieldResult = IO_ScanfReadScansetField(argCursor, (int *)&formatPtr, (_BYTE *)streamContext);
              goto LABEL_58;
            }
            if ( convChar == 99 )
              goto LABEL_57;
          }
        }
      }
    }
    else
    {
      if ( convChar <= 0x64 )
      {
        radix = 10;
        goto LABEL_46;
      }
      if ( convChar < 0x6F )
      {
        if ( convChar < 0x69 )
        {
          if ( convChar <= 0x67 )
            goto LABEL_52;
        }
        else
        {
          if ( convChar <= 0x69 )
          {
            v13 = streamContext;
            radix = 0;
            goto LABEL_47;
          }
          if ( convChar == 110 )
            IO_ScanfStoreScanCount(streamContext, argCursor, charsConsumed);
        }
      }
      else
      {
        if ( convChar <= 0x6F )
        {
          radix = 8;
          goto LABEL_46;
        }
        if ( convChar < 0x73 )
        {
          isHexConv = convChar == 112;
        }
        else
        {
          if ( convChar <= 0x73 )
            goto LABEL_54;
          if ( convChar < 0x75 )
            goto LABEL_64;
          if ( convChar <= 0x75 )
          {
            radix = 10;
            v13 = streamContext;
            goto LABEL_47;
          }
          isHexConv = convChar == 120;
        }
        if ( isHexConv )
          goto LABEL_51;
      }
    }
LABEL_64:
    if ( (*(_BYTE *)(streamContext + 16) & 2) != 0 )
    {
      if ( *formatPtr == 37 )
      {
        ++formatPtr;
        formatPtr = IO_ScanfParseFieldSpec(formatPtr, streamContext);
        if ( *formatPtr == 110 )
          IO_ScanfStoreScanCount(streamContext, argCursor, charsConsumed);
      }
      break;
    }
  }
  if ( assignedCount || (*(_BYTE *)(streamContext + 16) & 2) == 0 )
    return assignedCount;
  else
    return -1;
}
// 4B304C: variable 'v8' is possibly undefined
// 4B31CD: variable 'v14' is possibly undefined

//----- (004B324A) --------------------------------------------------------
unsigned __int8 * IO_ScanfParseFieldSpec(unsigned __int8 *result, int streamContext)
{
  char flagsByte; // dl
  int fieldWidth; // edx
  unsigned __int8 sizeChar; // dl
  char newFlags; // dh
  int digitChar; // [esp+0h] [ebp-10h]

  flagsByte = *(_BYTE *)(streamContext + 16) | 1;
  *(_BYTE *)(streamContext + 16) = flagsByte;
  *(_DWORD *)(streamContext + 12) = -1;
  *(_BYTE *)(streamContext + 16) = flagsByte & 3;
  if ( *result == 42 )
  {
    ++result;
    *(_BYTE *)(streamContext + 16) &= ~1u;
  }
  digitChar = *result;
  if ( (IsTable[(unsigned __int8)(digitChar + 1)] & 0x20) != 0 )
  {
    fieldWidth = 0;
    do
    {
      ++result;
      fieldWidth = digitChar - 48 + 10 * fieldWidth;
      digitChar = *result;
    }
    while ( (IsTable[(unsigned __int8)(digitChar + 1)] & 0x20) != 0 );
    *(_DWORD *)(streamContext + 12) = fieldWidth;
  }
  if ( *result == 78 )
  {
    *(_BYTE *)(streamContext + 16) |= 8u;
  }
  else
  {
    if ( *result != 70 )
      goto LABEL_12;
    *(_BYTE *)(streamContext + 16) |= 4u;
  }
  ++result;
LABEL_12:
  sizeChar = *result;
  if ( *result >= 0x68u )
  {
    if ( *result > 0x68u )
    {
      if ( sizeChar >= 0x6Cu && (sizeChar <= 0x6Cu || sizeChar == 119) )
      {
        ++result;
        *(_BYTE *)(streamContext + 16) |= 0x20u;
      }
      return result;
    }
    newFlags = *(_BYTE *)(streamContext + 16) | 0x10;
    ++result;
LABEL_28:
    *(_BYTE *)(streamContext + 16) = newFlags;
    return result;
  }
  if ( sizeChar < 0x49u )
    return result;
  if ( sizeChar <= 0x49u )
  {
    if ( result[1] != 54 || result[2] != 52 )
      return result;
    newFlags = *(_BYTE *)(streamContext + 16) | 0x40;
    result += 3;
    goto LABEL_28;
  }
  if ( sizeChar == 76 )
  {
    ++result;
    *(_BYTE *)(streamContext + 16) |= 0x40u;
  }
  return result;
}

//----- (004B3341) --------------------------------------------------------
int  IO_ScanfSkipWhitespace(int streamContext)
{
  int skippedCount; // esi
  int v3; // ecx

  skippedCount = 0;
  while ( (IsTable[(unsigned __int8)(IO_ScanfGetChar((int (**)(void))streamContext) + 1)] & 2) != 0 )
    ++skippedCount;
  if ( (*(_BYTE *)(streamContext + 16) & 2) == 0 )
    IO_ScanfUngetChar(v3, streamContext);
  return skippedCount;
}
// 4B336D: variable 'v3' is possibly undefined

//----- (004B3378) --------------------------------------------------------
int  IO_ScanfReadCharField(int streamContext, int *argList, _WORD *destBuffer)
{
  int v3; // ecx
  char flagsByte; // bl
  int farArgPtr; // edi
  int nearArgPtr; // esi
  int defaultArgPtr; // ebx
  int fieldWidth; // edi
  int charsRead; // ebp
  unsigned __int8 inputChar; // al
  char statusFlags; // dl
  int wideChar; // [esp+0h] [ebp-20h] BYREF
  unsigned __int8 mbBuffer[28]; // [esp+4h] [ebp-1Ch] BYREF

  v3 = streamContext;
  if ( (*(_BYTE *)(streamContext + 16) & 1) != 0 )
  {
    flagsByte = *(_BYTE *)(streamContext + 16);
    if ( (flagsByte & 4) != 0 )
    {
      farArgPtr = *argList + 8;
      *argList = farArgPtr;
      destBuffer = *(_WORD **)(farArgPtr - 8);
      __ES__ = *(_WORD *)(farArgPtr - 8 + 4);
    }
    else if ( (flagsByte & 8) != 0 )
    {
      nearArgPtr = *argList + 4;
      *argList = nearArgPtr;
      __ES__ = __DS__;
      destBuffer = *(_WORD **)(nearArgPtr - 4);
    }
    else
    {
      defaultArgPtr = *argList + 4;
      *argList = defaultArgPtr;
      __ES__ = __DS__;
      destBuffer = *(_WORD **)(defaultArgPtr - 4);
    }
  }
  fieldWidth = *(_DWORD *)(streamContext + 12);
  charsRead = 0;
  if ( fieldWidth == -1 )
    fieldWidth = 1;
  while ( fieldWidth > 0 )
  {
    inputChar = IO_ScanfGetChar((int (**)(void))v3);
    statusFlags = *(_BYTE *)(v3 + 16);
    if ( (statusFlags & 2) != 0 )
      break;
    ++charsRead;
    --fieldWidth;
    if ( (statusFlags & 1) != 0 )
    {
      if ( (statusFlags & 0x20) != 0 )
      {
        mbBuffer[0] = inputChar;
        if ( g_CRT_MbcsCodePageActive )
        {
          if ( (g_Clips_DbcsLeadByteTable[inputChar] & 1) != 0 )
            mbBuffer[1] = IO_ScanfGetChar((int (**)(void))v3);
        }
        if ( Str_DecodeMultibyteChar(&wideChar, mbBuffer, 2u) == -1 )
          return 0;
        *destBuffer++ = wideChar;
      }
      else
      {
        *(_BYTE *)destBuffer = inputChar;
        destBuffer = (_WORD *)((char *)destBuffer + 1);
      }
    }
  }
  return charsRead;
}
// 4B33D9: variable 'v3' is possibly undefined
// 54E718: using guessed type int dword_54E718;

//----- (004B345A) --------------------------------------------------------
void  IO_ScanfReadStringField(int streamContext, int *argList, unsigned __int8 *destBuffer)
{
  int v3; // ecx
  char flagsByte; // bl
  int farArgPtr; // edi
  int nearArgPtr; // esi
  int defaultArgPtr; // ebx
  int i; // edi
  unsigned __int8 inputChar; // bl
  int fieldWidth; // eax
  int nextChar; // eax
  int wideChar; // [esp+0h] [ebp-24h] BYREF
  unsigned __int8 mbBuffer[4]; // [esp+4h] [ebp-20h] BYREF
  unsigned __int8 charSize; // [esp+8h] [ebp-1Ch]

  v3 = streamContext;
  if ( (*(_BYTE *)(streamContext + 16) & 0x20) != 0 )
    charSize = 2;
  else
    charSize = 1;
  flagsByte = *(_BYTE *)(streamContext + 16);
  if ( (flagsByte & 1) != 0 )
  {
    if ( (flagsByte & 4) != 0 )
    {
      farArgPtr = *argList + 8;
      *argList = farArgPtr;
      destBuffer = *(unsigned __int8 **)(farArgPtr - 8);
      __ES__ = *(_WORD *)(farArgPtr - 8 + 4);
    }
    else if ( (flagsByte & 8) != 0 )
    {
      nearArgPtr = *argList + 4;
      *argList = nearArgPtr;
      __ES__ = __DS__;
      destBuffer = *(unsigned __int8 **)(nearArgPtr - 4);
    }
    else
    {
      defaultArgPtr = *argList + 4;
      *argList = defaultArgPtr;
      __ES__ = __DS__;
      destBuffer = *(unsigned __int8 **)(defaultArgPtr - 4);
    }
  }
  for ( i = 0; ; ++i )
  {
    inputChar = IO_ScanfGetChar((int (**)(void))v3);
    if ( (IsTable[(unsigned __int8)(inputChar + 1)] & 2) == 0 )
      break;
  }
  if ( (*(_BYTE *)(v3 + 16) & 2) != 0 )
  {
    i = 0;
  }
  else
  {
    fieldWidth = *(_DWORD *)(v3 + 12);
    *(_DWORD *)(v3 + 12) = fieldWidth - 1;
    if ( fieldWidth )
    {
      do
      {
        ++i;
        if ( (*(_BYTE *)(v3 + 16) & 1) != 0 )
        {
          if ( charSize == 1 )
          {
            *destBuffer = inputChar;
          }
          else
          {
            mbBuffer[0] = inputChar;
            if ( g_CRT_MbcsCodePageActive && (g_Clips_DbcsLeadByteTable[inputChar] & 1) != 0 )
              mbBuffer[1] = IO_ScanfGetChar((int (**)(void))v3);
            if ( Str_DecodeMultibyteChar(&wideChar, mbBuffer, 2u) == -1 )
              goto LABEL_33;
            *(_WORD *)destBuffer = wideChar;
          }
          destBuffer += charSize;
        }
        nextChar = IO_ScanfNextFieldChar(v3);
        inputChar = nextChar;
        if ( nextChar == -1 )
          goto LABEL_28;
      }
      while ( (IsTable[(unsigned __int8)(nextChar + 1)] & 2) == 0 );
    }
    IO_ScanfUngetChar(v3, v3);
  }
LABEL_28:
  if ( (*(_BYTE *)(v3 + 16) & 1) != 0 && i > 0 )
  {
    if ( charSize == 1 )
      *destBuffer = 0;
    else
      *(_WORD *)destBuffer = 0;
  }
LABEL_33:
  // 4B35A8: jumps to the shared epilogue loc_4B3453 (pop ebp/es/edi/esi/ecx/ebx; retn)
  // shared with sub_4B3378; in C this is the function return.
  return;
}
// 4B35A8: control flows out of bounds to 4B3453
// 4B34BB: variable 'v3' is possibly undefined
// 54E718: using guessed type int dword_54E718;

//----- (004B35AD) --------------------------------------------------------
int  IO_ScanfStoreScanCount(int result, int *argList, int charCount)
{
  char flagsByte; // cl
  int farArgPtr; // edi
  _WORD *destPtr; // edx
  int nearArgPtr; // esi
  int defaultArgPtr; // ecx

  flagsByte = *(_BYTE *)(result + 16);
  if ( (flagsByte & 1) != 0 )
  {
    if ( (flagsByte & 4) != 0 )
    {
      farArgPtr = *argList + 8;
      *argList = farArgPtr;
      destPtr = *(_WORD **)(farArgPtr - 8);
      __ES__ = *(_WORD *)(farArgPtr - 8 + 4);
    }
    else if ( (flagsByte & 8) != 0 )
    {
      nearArgPtr = *argList + 4;
      *argList = nearArgPtr;
      __ES__ = __DS__;
      destPtr = *(_WORD **)(nearArgPtr - 4);
    }
    else
    {
      defaultArgPtr = *argList + 4;
      *argList = defaultArgPtr;
      __ES__ = __DS__;
      destPtr = *(_WORD **)(defaultArgPtr - 4);
    }
    if ( (*(_BYTE *)(result + 16) & 0x10) != 0 )
      *destPtr = charCount;
    else
      *(_DWORD *)destPtr = charCount;
  }
  return result;
}

//----- (004B360B) --------------------------------------------------------
_BYTE * IO_ScanfParseScanset(int a1, int scansetBitmap)
{
  unsigned __int8 *scansetString; // ecx
  int setChar; // eax
  _BYTE *formatCursor; // ecx

  memset_(a1, 0);
  setChar = *scansetString;
  formatCursor = scansetString + 1;
  if ( setChar )
  {
    do
    {
      *(_BYTE *)((setChar >> 3) + scansetBitmap) |= g_BitPositionMaskTable[setChar & 7];
      setChar = (unsigned __int8)*formatCursor;
      if ( !*formatCursor )
        break;
      ++formatCursor;
    }
    while ( setChar != 93 );
  }
  return formatCursor;
}
// 4B3622: variable 'v3' is possibly undefined
// 473FD8: using guessed type int __fastcall memset_(_DWORD, _DWORD);

//----- (004B364E) --------------------------------------------------------
int  IO_ScanfReadScansetField(int *argList, int *formatPtr, _BYTE *destBuffer)
{
  _BYTE *scansetPtr; // eax
  bool v5; // zf
  int streamContext; // ecx
  char flagsByte; // bl
  int farArgPtr; // esi
  int farArgBase; // eoff
  int nearArgPtr; // ebx
  int defaultArgPtr; // edx
  int fieldWidth; // edx
  int i; // edi
  int inputChar; // eax
  int v15; // edx
  char statusFlags; // bl
  char scansetBitmap[32]; // [esp+0h] [ebp-40h] BYREF
  int bitmapByte; // [esp+20h] [ebp-20h]
  BOOL negateSet; // [esp+24h] [ebp-1Ch]
  int savedChar; // [esp+28h] [ebp-18h]

  scansetPtr = (_BYTE *)*formatPtr;
  v5 = *(_BYTE *)*formatPtr != 94;
  negateSet = *(_BYTE *)*formatPtr == 94;
  if ( !v5 )
    *formatPtr = (int)(scansetPtr + 1);
  *formatPtr = (int)IO_ScanfParseScanset(*formatPtr, (int)scansetBitmap);
  flagsByte = *(_BYTE *)(streamContext + 16);
  if ( (flagsByte & 1) != 0 )
  {
    if ( (flagsByte & 4) != 0 )
    {
      farArgPtr = *argList + 8;
      *argList = farArgPtr;
      farArgBase = farArgPtr - 8;
      destBuffer = *(_BYTE **)(farArgPtr - 8);
      __ES__ = *(_WORD *)(farArgBase + 4);
    }
    else if ( (flagsByte & 8) != 0 )
    {
      nearArgPtr = *argList + 4;
      *argList = nearArgPtr;
      __ES__ = __DS__;
      destBuffer = *(_BYTE **)(nearArgPtr - 4);
    }
    else
    {
      defaultArgPtr = *argList + 4;
      *argList = defaultArgPtr;
      __ES__ = __DS__;
      destBuffer = *(_BYTE **)(defaultArgPtr - 4);
    }
  }
  fieldWidth = *(_DWORD *)(streamContext + 12);
  for ( i = 0; fieldWidth; ++i )
  {
    inputChar = IO_ScanfGetChar((int (**)(void))streamContext);
    statusFlags = *(_BYTE *)(streamContext + 16);
    savedChar = inputChar;
    if ( (statusFlags & 2) != 0 )
      break;
    bitmapByte = (unsigned __int8)scansetBitmap[inputChar >> 3];
    if ( ((unsigned __int8)(bitmapByte & g_BitPositionMaskTable[inputChar & 7]) == 0) != negateSet )
    {
      IO_ScanfUngetChar(streamContext, streamContext);
      break;
    }
    fieldWidth = v15 - 1;
    if ( (*(_BYTE *)(streamContext + 16) & 1) != 0 )
      *destBuffer++ = savedChar;
  }
  if ( (*(_BYTE *)(streamContext + 16) & 1) != 0 && i > 0 )
    *destBuffer = 0;
  return i;
}
// 4B367C: variable 'v6' is possibly undefined
// 4B371B: variable 'v15' is possibly undefined

//----- (004B3744) --------------------------------------------------------
void  IO_ScanfReadFloatField(int streamContext, int *argList)
{
  int digitCount; // edi
  char *bufferCursor; // ebx
  int firstChar; // eax
  int inputChar; // ecx
  int fieldWidth; // edx
  int savedIndex; // ebp
  int sawIntegerDigits; // ebp
  int nextChar; // eax
  int dotNextChar; // eax
  char *digitCursor; // ebp
  char fracChar; // al
  int expChar; // eax
  int expDigitChar; // eax
  char flagsByte; // ah
  int farArgPtr; // ecx
  int *destPtr; // ebx
  int nearArgPtr; // ebx
  int defaultArgPtr; // edx
  char sizeFlags; // dh
  int storeValue; // eax
  char numberBuffer; // [esp+0h] [ebp-84h] BYREF
  _BYTE v24[3]; // [esp+1h] [ebp-83h] BYREF
  _DWORD doubleValue[2]; // [esp+50h] [ebp-34h] BYREF
  int *argCursor; // [esp+58h] [ebp-2Ch]
  int v27; // [esp+5Ch] [ebp-28h]
  unsigned int j; // [esp+60h] [ebp-24h]
  int integerValue; // [esp+64h] [ebp-20h]
  int i; // [esp+68h] [ebp-1Ch]

  argCursor = argList;
  digitCount = 0;
  bufferCursor = &numberBuffer;
  for ( i = 0; ; ++i )
  {
    firstChar = IO_ScanfGetChar((int (**)(void))streamContext);
    inputChar = firstChar;
    if ( (IsTable[(unsigned __int8)(firstChar + 1)] & 2) == 0 )
      break;
  }
  if ( (*(_BYTE *)(streamContext + 16) & 2) != 0 )
    goto LABEL_42;
  fieldWidth = *(_DWORD *)(streamContext + 12);
  *(_DWORD *)(streamContext + 12) = fieldWidth - 1;
  if ( fieldWidth )
  {
    if ( firstChar == 43 || firstChar == 45 )
    {
      savedIndex = i;
      numberBuffer = firstChar;
      bufferCursor = v24;
      inputChar = IO_ScanfNextFieldChar(streamContext);
      i = savedIndex + 1;
      if ( inputChar == -1 )
        goto LABEL_42;
    }
    if ( (IsTable[(unsigned __int8)(inputChar + 1)] & 0x20) != 0 || inputChar == 46 )
    {
      integerValue = 0;
      sawIntegerDigits = 0;
      if ( (IsTable[(unsigned __int8)(inputChar + 1)] & 0x20) != 0 )
      {
        sawIntegerDigits = 1;
        while ( 1 )
        {
          *bufferCursor++ = inputChar;
          if ( (*(_BYTE *)(streamContext + 16) & 0x10) != 0 )
            HIWORD(integerValue) = 10 * HIWORD(integerValue) + inputChar - 48;
          ++digitCount;
          nextChar = IO_ScanfNextFieldChar(streamContext);
          inputChar = nextChar;
          if ( nextChar == -1 )
            break;
          if ( (IsTable[(unsigned __int8)(nextChar + 1)] & 0x20) == 0 )
            goto LABEL_17;
        }
LABEL_42:
        if ( digitCount > 0 && (*(_BYTE *)(streamContext + 16) & 1) != 0 )
        {
          *bufferCursor = 0;
          if ( (*(_BYTE *)(streamContext + 16) & 0x10) != 0 )
          {
            if ( numberBuffer == 45 )
              integerValue = -integerValue;
          }
          else
          {
            g_StringToDoubleScanFn(inputChar, doubleValue);
          }
          flagsByte = *(_BYTE *)(streamContext + 16);
          if ( (flagsByte & 4) != 0 )
          {
            farArgPtr = *argCursor + 8;
            *argCursor = farArgPtr;
            destPtr = *(int **)(farArgPtr - 8);
            __ES__ = *(_WORD *)(farArgPtr - 8 + 4);
          }
          else if ( (flagsByte & 8) != 0 )
          {
            nearArgPtr = *argCursor + 4;
            *argCursor = nearArgPtr;
            __ES__ = __DS__;
            destPtr = *(int **)(nearArgPtr - 4);
          }
          else
          {
            defaultArgPtr = *argCursor + 4;
            *argCursor = defaultArgPtr;
            __ES__ = __DS__;
            destPtr = *(int **)(defaultArgPtr - 4);
          }
          sizeFlags = *(_BYTE *)(streamContext + 16);
          if ( (sizeFlags & 0x10) != 0 )
          {
            storeValue = integerValue;
          }
          else
          {
            if ( (sizeFlags & 0x20) != 0 || (sizeFlags & 0x40) != 0 )
            {
              *destPtr = doubleValue[0];
              destPtr[1] = doubleValue[1];
              goto LABEL_60;
            }
            storeValue = _FDFS();
          }
          *destPtr = storeValue;
        }
LABEL_60:
        // 4B3597: jumps to the shared epilogue loc_4B3453 (pop ebp/es/edi/esi/ecx/ebx; retn)
        // shared with sub_4B3378; in C this is the function return.
        return;
      }
LABEL_17:
      if ( inputChar == 46 )
      {
        *bufferCursor = 46;
        dotNextChar = IO_ScanfNextFieldChar(streamContext);
        ++bufferCursor;
        inputChar = dotNextChar;
        if ( dotNextChar == -1 )
          goto LABEL_42;
        if ( !sawIntegerDigits && (IsTable[(unsigned __int8)(dotNextChar + 1)] & 0x20) == 0 )
          goto LABEL_41;
        ++digitCount;
        do
        {
          if ( (IsTable[(unsigned __int8)(inputChar + 1)] & 0x20) == 0 )
            break;
          ++digitCount;
          *bufferCursor++ = inputChar;
          inputChar = IO_ScanfNextFieldChar(streamContext);
        }
        while ( inputChar != -1 );
        if ( (*(_BYTE *)(streamContext + 16) & 0x10) != 0 )
        {
          digitCursor = bufferCursor;
          for ( j = 0; ; j /= 0xAu )
          {
            fracChar = *--digitCursor;
            if ( *digitCursor == 46 )
              break;
            v27 = 10;
            BYTE2(j) = fracChar - 48;
          }
          LOWORD(integerValue) = j;
        }
        if ( inputChar == -1 )
          goto LABEL_42;
      }
      if ( (*(_BYTE *)(streamContext + 16) & 0x10) == 0 && (inputChar == 101 || inputChar == 69) )
      {
        ++digitCount;
        *bufferCursor = inputChar;
        expChar = IO_ScanfNextFieldChar(streamContext);
        ++bufferCursor;
        inputChar = expChar;
        if ( expChar == -1 )
          goto LABEL_42;
        if ( expChar == 43 || expChar == 45 )
        {
          ++digitCount;
          *bufferCursor++ = expChar;
          inputChar = IO_ScanfNextFieldChar(streamContext);
          if ( inputChar == -1 )
            goto LABEL_42;
        }
        if ( (IsTable[(unsigned __int8)(inputChar + 1)] & 0x20) != 0 )
        {
          while ( 1 )
          {
            ++digitCount;
            *bufferCursor = inputChar;
            expDigitChar = IO_ScanfNextFieldChar(streamContext);
            ++bufferCursor;
            inputChar = expDigitChar;
            if ( expDigitChar == -1 )
              goto LABEL_42;
            if ( (IsTable[(unsigned __int8)(expDigitChar + 1)] & 0x20) == 0 )
              goto LABEL_41;
          }
        }
        digitCount = 0;
      }
    }
  }
LABEL_41:
  IO_ScanfUngetChar(inputChar, streamContext);
  goto LABEL_42;
}
// 4B3A15: control flows out of bounds to 4B3453
// 4B398E: variable 'v6' is possibly undefined
// 4D9506: using guessed type int _FDFS(void);
// 51AF08: using guessed type int (__fastcall *off_51AF08)(_DWORD, _DWORD);

//----- (004B3A1A) --------------------------------------------------------
signed int  IO_ScanfReadIntegerField(int streamContext, int *argList, int radix)
{
  int digitCount; // ebp
  int firstChar; // eax
  int v6; // edx
  int v7; // ecx
  int fieldWidth; // ebx
  int autoRadixChar; // eax
  int afterPrefixChar; // eax
  int v11; // edx
  int hexPrefixChar; // eax
  int v13; // ecx
  int digitValue; // eax
  int v15; // edx
  signed int colonNextChar; // eax
  int v17; // edx
  int v18; // ecx
  int colonDigitValue; // eax
  int mainDigitValue; // eax
  signed int colonNextChar32; // eax
  int v22; // edx
  int v23; // ecx
  int colonDigitValue32; // eax
  int v25; // eax
  char flagsByte; // bh
  int farArgPtr; // edx
  __int16 v28; // ax
  int v29; // edi
  int nearArgPtr; // edi
  int defaultArgPtr; // esi
  char flagsByte32; // al
  int farArgPtr32; // ebx
  _WORD *destPtr; // eax
  int nearArgPtr32; // edx
  int defaultArgPtr32; // esi
  __int64 int64Value; // [esp+8h] [ebp-38h]
  int signChar; // [esp+18h] [ebp-28h]
  int i; // [esp+20h] [ebp-20h]
  int intValue; // [esp+24h] [ebp-1Ch]
  signed int inputChar; // [esp+2Ch] [ebp-14h]

  digitCount = 0;
  int64Value = 0LL;
  intValue = 0;
  for ( i = 0; ; ++i )
  {
    firstChar = IO_ScanfGetChar((int (**)(void))streamContext);
    inputChar = firstChar;
    if ( (IsTable[(unsigned __int8)(firstChar + 1)] & 2) == 0 )
      break;
  }
  if ( (*(_BYTE *)(streamContext + 16) & 2) != 0 )
    goto LABEL_44;
  fieldWidth = *(_DWORD *)(streamContext + 12);
  *(_DWORD *)(streamContext + 12) = fieldWidth - 1;
  if ( !fieldWidth )
    goto LABEL_43;
  signChar = 43;
  if ( v7 && (firstChar == 43 || firstChar == 45) )
  {
    signChar = firstChar;
    ++i;
    inputChar = IO_ScanfNextFieldChar(streamContext);
    if ( inputChar == -1 )
      goto LABEL_44;
  }
  if ( radix )
  {
    if ( radix == 16 && inputChar == 48 )
    {
      digitCount = 1;
      hexPrefixChar = IO_ScanfNextFieldChar(streamContext);
      inputChar = hexPrefixChar;
      if ( hexPrefixChar == -1 )
        goto LABEL_44;
      if ( hexPrefixChar == 120 || hexPrefixChar == 88 )
      {
        digitCount = 0;
        inputChar = IO_ScanfNextFieldChar(streamContext);
        i += 2;
        if ( inputChar == -1 )
          goto LABEL_44;
      }
    }
  }
  else if ( inputChar == 48 )
  {
    digitCount = 1;
    autoRadixChar = IO_ScanfNextFieldChar(streamContext);
    inputChar = autoRadixChar;
    if ( autoRadixChar == -1 )
      goto LABEL_44;
    if ( autoRadixChar == 120 || autoRadixChar == 88 )
    {
      afterPrefixChar = IO_ScanfNextFieldChar(streamContext);
      digitCount = 0;
      v6 = v11 + 2;
      inputChar = afterPrefixChar;
      i = v6;
      if ( afterPrefixChar == -1 )
        goto LABEL_44;
      radix = 16;
    }
    else
    {
      radix = 8;
    }
  }
  else
  {
    radix = 10;
  }
  if ( (*(_BYTE *)(streamContext + 16) & 0x40) != 0 )
  {
    v13 = 0;
    while ( 1 )
    {
      digitValue = IO_ScanfDigitValue(inputChar, radix, v13);
      if ( digitValue >= v15 )
        break;
      int64Value = (unsigned int)digitValue + _I8M(0, HIDWORD(int64Value));
      ++digitCount;
      inputChar = IO_ScanfNextFieldChar(streamContext);
      if ( inputChar == -1 )
        goto LABEL_44;
    }
    if ( inputChar == 58 && *(char *)(streamContext + 16) < 0 )
    {
      while ( 1 )
      {
        ++digitCount;
        colonNextChar = IO_ScanfNextFieldChar(streamContext);
        if ( colonNextChar == -1 )
          goto LABEL_44;
        colonDigitValue = IO_ScanfDigitValue(colonNextChar, v17, v18);
        if ( colonDigitValue >= radix )
          break;
        int64Value = (unsigned int)colonDigitValue + _I8M(0, HIDWORD(int64Value));
      }
    }
LABEL_43:
    IO_ScanfUngetChar(v7, streamContext);
    goto LABEL_44;
  }
  while ( 1 )
  {
    mainDigitValue = IO_ScanfDigitValue(inputChar, v6, v7);
    if ( mainDigitValue >= radix )
      break;
    ++digitCount;
    intValue = mainDigitValue + radix * intValue;
    inputChar = IO_ScanfNextFieldChar(streamContext);
    if ( inputChar == -1 )
      goto LABEL_44;
  }
  if ( inputChar != 58 || *(char *)(streamContext + 16) >= 0 )
    goto LABEL_43;
  while ( 1 )
  {
    ++digitCount;
    colonNextChar32 = IO_ScanfNextFieldChar(streamContext);
    if ( colonNextChar32 == -1 )
      break;
    colonDigitValue32 = IO_ScanfDigitValue(colonNextChar32, v22, v23);
    if ( colonDigitValue32 >= v7 )
      goto LABEL_43;
    intValue = colonDigitValue32 + v7 * intValue;
  }
LABEL_44:
  if ( (*(_BYTE *)(streamContext + 16) & 0x40) != 0 )
  {
    if ( signChar == 45 )
    {
      v25 = ~HIDWORD(int64Value);
      LODWORD(int64Value) = -(int)int64Value;
      if ( !(_DWORD)int64Value )
        v25 = -HIDWORD(int64Value);
      HIDWORD(int64Value) = v25;
    }
    if ( digitCount > 0 )
    {
      flagsByte = *(_BYTE *)(streamContext + 16);
      digitCount += i;
      if ( (flagsByte & 1) != 0 )
      {
        if ( (flagsByte & 4) != 0 )
        {
          farArgPtr = *argList + 8;
          *argList = farArgPtr;
          v28 = *(_WORD *)(farArgPtr - 4);
          v29 = *(_DWORD *)(farArgPtr - 8);
        }
        else if ( (flagsByte & 8) != 0 )
        {
          nearArgPtr = *argList + 4;
          *argList = nearArgPtr;
          v28 = __DS__;
          v29 = *(_DWORD *)(nearArgPtr - 4);
        }
        else
        {
          defaultArgPtr = *argList + 4;
          *argList = defaultArgPtr;
          v28 = __DS__;
          v29 = *(_DWORD *)(defaultArgPtr - 4);
        }
        *(__int64 *)MK_FP(v28, v29) = int64Value;
      }
    }
  }
  else
  {
    if ( signChar == 45 )
      intValue = -intValue;
    if ( digitCount > 0 )
    {
      flagsByte32 = *(_BYTE *)(streamContext + 16);
      digitCount += i;
      if ( (flagsByte32 & 1) != 0 )
      {
        if ( (flagsByte32 & 4) != 0 )
        {
          farArgPtr32 = *argList + 8;
          *argList = farArgPtr32;
          destPtr = *(_WORD **)(farArgPtr32 - 8);
          __ES__ = *(_WORD *)(farArgPtr32 - 8 + 4);
        }
        else if ( (flagsByte32 & 8) != 0 )
        {
          nearArgPtr32 = *argList + 4;
          *argList = nearArgPtr32;
          __ES__ = __DS__;
          destPtr = *(_WORD **)(nearArgPtr32 - 4);
        }
        else
        {
          defaultArgPtr32 = *argList + 4;
          *argList = defaultArgPtr32;
          __ES__ = __DS__;
          destPtr = *(_WORD **)(defaultArgPtr32 - 4);
        }
        if ( (*(_BYTE *)(streamContext + 16) & 0x10) != 0 )
          *destPtr = intValue;
        else
          *(_DWORD *)destPtr = intValue;
      }
    }
  }
  return digitCount;
}
// 4B3A8B: variable 'v7' is possibly undefined
// 4B3AFE: variable 'v11' is possibly undefined
// 4B3BA0: variable 'v13' is possibly undefined
// 4B3BA7: variable 'v15' is possibly undefined
// 4B3C34: variable 'v17' is possibly undefined
// 4B3C34: variable 'v18' is possibly undefined
// 4B3C91: variable 'v6' is possibly undefined
// 4B3CDC: variable 'v22' is possibly undefined
// 4B3CDC: variable 'v23' is possibly undefined
// 4B3D0E: variable 'v39' is possibly undefined
// 4D9552: using guessed type __int64 __fastcall _I8M(_DWORD, _DWORD);

//----- (004B3E1F) --------------------------------------------------------
int  IO_ScanfDigitValue(signed int ch, int radix, int a3)
{
  int lowerChar; // eax

  if ( ch >= 48 && ch <= 57 )
    return ch - 48;
  lowerChar = tolower_(a3, radix);
  if ( lowerChar < 97 || lowerChar > 102 )
    return 16;
  else
    return lowerChar - 87;
}
// 4852ED: using guessed type int __fastcall tolower_(_DWORD, _DWORD);

//----- (004B3E46) --------------------------------------------------------
int  IO_ScanfNextFieldChar(int streamContext)
{
  int remainingWidth; // eax
  int result; // eax
  int v4; // edx

  remainingWidth = *(_DWORD *)(streamContext + 12);
  *(_DWORD *)(streamContext + 12) = remainingWidth - 1;
  if ( !remainingWidth )
    return -1;
  result = IO_ScanfGetChar((int (**)(void))streamContext);
  if ( (*(_BYTE *)(v4 + 16) & 2) != 0 )
    return -1;
  return result;
}
// 4B3E5E: variable 'v4' is possibly undefined

//----- (004B4E7A) --------------------------------------------------------
BOOL CRT_HasActiveWindow(void)
{
  HMODULE LibraryA; // eax
  HWND v1; // ebx
  HWND (__stdcall *GetActiveWindow)(); // eax

  LibraryA = LoadLibraryA(LibFileName);
  v1 = 0;
  if ( LibraryA )
  {
    GetActiveWindow = (HWND (__stdcall *)())GetProcAddress(LibraryA, ProcName);
    if ( GetActiveWindow )
      v1 = GetActiveWindow();
  }
  return v1 != 0;
}

//----- (004B4EB4) --------------------------------------------------------
unsigned int  CRT_FormatExceptionMessage(unsigned int result, char *appendText, unsigned int addressValue)
{
  char *hexInsertPos; // ebx
  char *i; // esi
  char srcChar; // cl
  char hexDigit; // dl

  hexInsertPos = 0;
  while ( *(_BYTE *)result )
    ++result;
  for ( i = (char *)(result + 9); ; ++i )
  {
    srcChar = *appendText;
    *(_BYTE *)result = *appendText;
    if ( !srcChar )
      break;
    if ( srcChar == 48 && appendText[1] == 120 )
      hexInsertPos = i;
    ++result;
    ++appendText;
  }
  if ( hexInsertPos )
  {
    for ( result = addressValue; result; result >>= 4 )
    {
      hexDigit = g_HexDigitCharTable[result & 0xF];
      *hexInsertPos-- = hexDigit;
    }
  }
  return result;
}

//----- (004B4F01) --------------------------------------------------------
signed int __stdcall TopLevelExceptionFilter(struct _EXCEPTION_POINTERS *ExceptionInfo)
{
  PCONTEXT ContextRecord; // ebx
  unsigned int *exceptionRecord; // ecx
  unsigned int exceptionCode; // eax
  unsigned int faultAddress; // ebx
  char *messageText; // edx
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  char Buffer[256]; // [esp+0h] [ebp-10Ch] BYREF
  DWORD NumberOfBytesWritten; // [esp+100h] [ebp-Ch] BYREF

  ContextRecord = ExceptionInfo->ContextRecord;
  if ( CRT_HasActiveWindow() || _NTConsoleOutput_() == -1 )
    return 0;
  Buffer[0] = 0;
  exceptionCode = *exceptionRecord;
  if ( *exceptionRecord < 0xC0000090 )
  {
    if ( exceptionCode < 0xC000008D )
    {
      if ( exceptionCode < 0xC0000005 )
        goto LABEL_41;
      if ( exceptionCode <= 0xC0000005 )
      {
        CRT_FormatExceptionMessage((unsigned int)Buffer, aTheInstructi_7, exceptionRecord[3]);
        CRT_FormatExceptionMessage((unsigned int)Buffer, aAt0x00000000_T, *(_DWORD *)(v7 + 24));
        if ( *(_DWORD *)(v8 + 20) )
          messageText = aWritten_;
        else
          messageText = aRead_;
        faultAddress = 0;
        goto LABEL_42;
      }
      if ( exceptionCode != -1073741795 )
        goto LABEL_41;
      messageText = aAnIllegalInstr;
    }
    else if ( exceptionCode <= 0xC000008D )
    {
      messageText = aTheInstructi_1;
    }
    else if ( exceptionCode <= 0xC000008E )
    {
      messageText = aTheInstructi_2;
    }
    else
    {
      messageText = aTheInstructi_3;
    }
  }
  else if ( *exceptionRecord <= 0xC0000090 )
  {
    messageText = aTheInstructi_6;
  }
  else if ( exceptionCode < 0xC0000093 )
  {
    if ( exceptionCode <= 0xC0000091 )
    {
      messageText = aTheInstructi_4;
    }
    else if ( (ContextRecord->FloatSave.StatusWord & 0x200) != 0 )
    {
      messageText = aTheInstruction;
    }
    else
    {
      messageText = aTheInstructi_0;
    }
  }
  else if ( exceptionCode <= 0xC0000093 )
  {
    messageText = aTheInstructi_5;
  }
  else if ( exceptionCode < 0xC0000096 )
  {
    if ( exceptionCode != -1073741676 )
      goto LABEL_41;
    messageText = aAnIntegerDivid;
  }
  else if ( exceptionCode <= 0xC0000096 )
  {
    messageText = aAPrivilegedIns;
  }
  else
  {
    if ( exceptionCode != -1073741571 )
    {
LABEL_41:
      CRT_FormatExceptionMessage((unsigned int)Buffer, aTheProgramEnco, *exceptionRecord);
      messageText = aAddress0x00000;
      faultAddress = *(_DWORD *)(v9 + 12);
      goto LABEL_42;
    }
    messageText = aAStackOverflow;
  }
  faultAddress = exceptionRecord[3];
LABEL_42:
  CRT_FormatExceptionMessage((unsigned int)Buffer, messageText, faultAddress);
  WriteFile(*(HANDLE *)(g_CRT_OsHandleTable + 8), Buffer, strlen(Buffer), &NumberOfBytesWritten, 0);
  return 1;
}
// 4B4F34: variable 'v2' is possibly undefined
// 4B5015: variable 'v7' is possibly undefined
// 4B501D: variable 'v8' is possibly undefined
// 4B506C: variable 'v9' is possibly undefined
// 4B48D9: using guessed type int _NTConsoleOutput_(void);
// 51AED0: using guessed type int dword_51AED0;

//----- (004B50D6) --------------------------------------------------------
signed int __cdecl CRT_FpuExceptionFrameHandler(EXCEPTION_RECORD *exceptionRecord, int establisherFrame, int contextRecord)
{
  int v3; // ecx
  signed int result; // eax
  int retryCount; // ebx
  int handlerResult; // eax
  struct _EXCEPTION_POINTERS exceptionPointers; // [esp+0h] [ebp-14h] BYREF

  if ( (exceptionRecord->ExceptionFlags & 6) != 0 )
    return 1;
  switch ( exceptionRecord->ExceptionCode )
  {
    case 0xC000008D:
    case 0xC000008E:
    case 0xC000008F:
    case 0xC0000090:
    case 0xC0000091:
    case 0xC0000092:
    case 0xC0000093:
      g_CRT_FpuExceptionActiveFlag = 1;
      Fpu_ClearExceptions();
      if ( CRT_DispatchRegisteredFpeHandler() == -1 || !g_CRT_FpuExceptionActiveFlag )
        goto LABEL_15;
      result = 0;
      *(_WORD *)(contextRecord + 32) &= 0x7F00u;
      return result;
    default:
      if ( !g_FpuExceptionResignalFn )
        goto LABEL_15;
      retryCount = 1;
      break;
  }
  while ( 1 )
  {
    handlerResult = g_CRT_ExceptionHandlerCallback(v3, exceptionRecord->ExceptionCode);
    if ( handlerResult )
    {
      if ( handlerResult == 1 || handlerResult == 2 || handlerResult == 3 )
      {
LABEL_15:
        exceptionPointers.ExceptionRecord = exceptionRecord;
        exceptionPointers.ContextRecord = (PCONTEXT)contextRecord;
        if ( UnhandledExceptionFilter(&exceptionPointers) )
          ExitProcess(0xFFFFFFFF);
        return 1;
      }
      g_CRT_FpuExceptionActiveFlag = 1;
      g_FpuExceptionResignalFn();
      if ( g_CRT_FpuExceptionActiveFlag )
        return 0;
    }
    if ( ++retryCount > 12 )
      goto LABEL_15;
  }
}
// 4B517F: conditional instruction was optimized away because dx.2!=F1D9
// 4B51E2: conditional instruction was optimized away because ebx.4 is in (==81|==8D)
// 4B5233: variable 'v3' is possibly undefined
// 4965FF: using guessed type int sub_4965FF(void);
// 51AEDC: using guessed type int (__fastcall *dword_51AEDC)(_DWORD, _DWORD);
// 51AEE0: using guessed type int (*dword_51AEE0)(void);
// 54E710: using guessed type char byte_54E710;
