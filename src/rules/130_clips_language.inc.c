/* CLIPS lexer, parser, expressions, and procedural language support.
 * Original function-marker range: 0x00481550..0x00481550.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00481550) --------------------------------------------------------
signed int Lexer_ParseValueList(int argumentPosition, _DWORD *returnValue, int expectedType, double a4)
{
  int v7; // ecx
  int lexemeType; // ecx
  int instanceType; // ecx
  int instanceRefType; // edx
  char *expectedTypeName; // ebx
  int integerNode; // eax
  int v14; // edx
  int floatNode; // eax
  double floatValue; // st7
  int v17; // [esp+8h] [ebp-10h]
  int v18; // [esp+Ch] [ebp-Ch]

  Rules_RtnUnknown(argumentPosition, returnValue, a4);
  if ( g_ClipsEvaluationError )
    return 0;
  if ( expectedType == *(_DWORD *)(v7 + 4) || expectedType == 110 && returnValue[1] < 2u )
    return 1;
  if ( expectedType == 111 )
  {
    lexemeType = returnValue[1];
    if ( lexemeType == 2 || lexemeType == 3 )
      return 1;
  }
  if ( (expectedType == 111 || expectedType == 2) && returnValue[1] == 8 )
    return 1;
  if ( expectedType == 8 )
  {
    instanceType = returnValue[1];
    if ( instanceType == 8 || instanceType == 2 )
      return 1;
  }
  if ( expectedType == 112 )
  {
    instanceRefType = returnValue[1];
    if ( instanceRefType == 7 || instanceRefType == 8 || instanceRefType == 2 )
      return 1;
  }
  if ( returnValue[1] == 1 && !expectedType )
  {
    integerNode = returnValue[2];
    returnValue[1] = 0;
    returnValue[2] = Rules_AddDoubleValue((double)*(int *)(integerNode + 16));
    return v14;
  }
  else
  {
    if ( returnValue[1] || expectedType != 1 )
    {
      if ( expectedType )
      {
        switch ( expectedType )
        {
          case 1:
            expectedTypeName = aInteger_1;
            break;
          case 2:
            expectedTypeName = aSymbol_2;
            break;
          case 3:
            expectedTypeName = aString_1;
            break;
          case 4:
            expectedTypeName = aMultifield_0;
            break;
          case 110:
            expectedTypeName = aIntegerOrFlo_0;
            break;
          case 111:
            expectedTypeName = aSymbolOrStri_0;
            break;
          case 8:
            expectedTypeName = aInstanceName_1;
            break;
          case 7:
            expectedTypeName = aInstanceAddr_6;
            break;
          case 112:
            expectedTypeName = aInstanceAddr_5;
            break;
          default:
            goto LABEL_24;
        }
      }
      else
      {
        expectedTypeName = aFloat_1;
      }
      Parser_ReportError(argumentPosition, (int)expectedTypeName);
LABEL_24:
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      return 0;
    }
    floatNode = returnValue[2];
    returnValue[1] = 1;
    floatValue = *(double *)(floatNode + 16);
    _CHP(v17, v18);
    returnValue[2] = Rules_AddIntegerValue((int)floatValue);
    return 1;
  }
}
// 481588: simplified comparisons for 'eax.4': ==1 || ==0 became <2u
// 481574: variable 'v7' is possibly undefined
// 481669: variable 'v14' is possibly undefined
// 481676: variable 'v17' is possibly undefined
// 481676: variable 'v18' is possibly undefined
// 51A964: using guessed type int dword_51A964;

