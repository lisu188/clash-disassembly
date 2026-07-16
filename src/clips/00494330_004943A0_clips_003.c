/* Generated from src/recovered/rules/clips/00491580_objects.inc.c; original address order retained. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "clips_internal.h"
#include "clips_state.h"
/* CLASH95_GENERATED_INCLUDES_END */

//----- (00494330) --------------------------------------------------------
signed int  AST_TreeContainsSpecialTag(int theExpression, int globalsAreVariables)
{
  int exprPtr; // ecx
  __int16 nodeType; // dx

  exprPtr = theExpression;
  if ( !theExpression )
    return 0;
  do
  {
    while ( 1 )
    {
      if ( *(_DWORD *)(exprPtr + 6) && AST_TreeContainsSpecialTag(*(_DWORD *)(exprPtr + 6), globalsAreVariables) )
        return 1;
      nodeType = *(_WORD *)exprPtr;
      if ( *(_WORD *)exprPtr == 16 || nodeType == 15 || nodeType == 6 )
        return 1;
      if ( nodeType != 13 && nodeType != 14 )
        break;
      if ( globalsAreVariables == 1 )
        return 1;
      exprPtr = *(_DWORD *)(exprPtr + 10);
      if ( !exprPtr )
        return 0;
    }
    exprPtr = *(_DWORD *)(exprPtr + 10);
  }
  while ( exprPtr );
  return 0;
}
// 494341: variable 'v2' is possibly undefined

//----- (004943A0) --------------------------------------------------------
int  AST_CountTreeNodes(int testPtr)
{
  int node; // edx
  int count; // ecx
  int child_node; // ebx

  node = testPtr;
  count = 0;
  if ( !testPtr )
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
