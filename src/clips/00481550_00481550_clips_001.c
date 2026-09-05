/* Generated from src/recovered/rules/clips/00481550_language.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
#include "clips_shared_state.h"
#include "../media/media_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00481550) --------------------------------------------------------
signed int Lexer_ParseValueList(int argumentPosition, _DWORD *returnValue, int expectedType, double a4)
{
  int lexemeType; // ecx
  int instanceType; // ecx
  int instanceRefType; // edx
  char *expectedTypeName; // ebx
  int integerNode; // eax
  int floatNode; // eax
  double floatValue; // st7
  int v17; // [esp+8h] [ebp-10h]
  int v18; // [esp+Ch] [ebp-Ch]

  Rules_RtnUnknown(argumentPosition, returnValue, a4);
  if ( g_ClipsEvaluationError )
    return 0;
  /* 481581: `cmp ebp, [ecx+4]` - ecx is the returnValue DATA_OBJECT that was just
     filled by sub_4813B0; IDA left it as the undefined temp v7. */
  if ( expectedType == (int)returnValue[1] || expectedType == 110 && returnValue[1] < 2u )
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
    returnValue[2] = Rules_AddDoubleValue((double)*(int *)(uintptr_t)(integerNode + 16));
    return 1;   /* loc_48163D: `mov eax, 1` */
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
      Parser_ReportError(argumentPosition, (int)(intptr_t)expectedTypeName);
LABEL_24:
      Rules_SetEvaluationErrorFlag(1);
      Lexer_ErrorRecover(1);
      return 0;
    }
    floatNode = returnValue[2];
    returnValue[1] = 1;
    floatValue = *(double *)(uintptr_t)(floatNode + 16);
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
