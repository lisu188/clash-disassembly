/* CLIPS lexer, parser, expressions, and procedural language support.
 * Original function-marker range: 0x00481550..0x00481550.
 * Included by clash95.c; not a standalone translation unit. */

//----- (00481550) --------------------------------------------------------
signed int Lexer_ParseValueList(int a1, _DWORD *a2, int a3, double a4)
{
  int v7; // ecx
  int v8; // ecx
  int v9; // ecx
  int v10; // edx
  char *v11; // ebx
  int v13; // eax
  int v14; // edx
  int v15; // eax
  double v16; // st7
  int v17; // [esp+8h] [ebp-10h]
  int v18; // [esp+Ch] [ebp-Ch]

  Rules_RtnUnknown(a1, a2, a4);
  if ( g_ClipsEvaluationError )
    return 0;
  if ( a3 == *(_DWORD *)(v7 + 4) || a3 == 110 && a2[1] < 2u )
    return 1;
  if ( a3 == 111 )
  {
    v8 = a2[1];
    if ( v8 == 2 || v8 == 3 )
      return 1;
  }
  if ( (a3 == 111 || a3 == 2) && a2[1] == 8 )
    return 1;
  if ( a3 == 8 )
  {
    v9 = a2[1];
    if ( v9 == 8 || v9 == 2 )
      return 1;
  }
  if ( a3 == 112 )
  {
    v10 = a2[1];
    if ( v10 == 7 || v10 == 8 || v10 == 2 )
      return 1;
  }
  if ( a2[1] == 1 && !a3 )
  {
    v13 = a2[2];
    a2[1] = 0;
    a2[2] = Rules_AddDoubleValue((double)*(int *)(v13 + 16));
    return v14;
  }
  else
  {
    if ( a2[1] || a3 != 1 )
    {
      if ( a3 )
      {
        switch ( a3 )
        {
          case 1:
            v11 = aInteger_1;
            break;
          case 2:
            v11 = aSymbol_2;
            break;
          case 3:
            v11 = aString_1;
            break;
          case 4:
            v11 = aMultifield_0;
            break;
          case 110:
            v11 = aIntegerOrFlo_0;
            break;
          case 111:
            v11 = aSymbolOrStri_0;
            break;
          case 8:
            v11 = aInstanceName_1;
            break;
          case 7:
            v11 = aInstanceAddr_6;
            break;
          case 112:
            v11 = aInstanceAddr_5;
            break;
          default:
            goto LABEL_24;
        }
      }
      else
      {
        v11 = aFloat_1;
      }
      Parser_ReportError(a1, (int)v11);
LABEL_24:
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      return 0;
    }
    v15 = a2[2];
    a2[1] = 1;
    v16 = *(double *)(v15 + 16);
    _CHP(v17, v18);
    a2[2] = Rules_AddIntegerValue((int)v16);
    return 1;
  }
}
// 481588: simplified comparisons for 'eax.4': ==1 || ==0 became <2u
// 481574: variable 'v7' is possibly undefined
// 481669: variable 'v14' is possibly undefined
// 481676: variable 'v17' is possibly undefined
// 481676: variable 'v18' is possibly undefined
// 51A964: using guessed type int dword_51A964;

