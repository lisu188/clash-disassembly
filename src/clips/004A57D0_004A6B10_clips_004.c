/* Generated from src/recovered/rules/clips/004A0080_symbols.inc.c; original address order retained. */
#include "../recovered_internal.h"

//----- (004A57D0) --------------------------------------------------------
signed int  Help_InsertEntryIntoTopicTree(int fileRecord, _DWORD *entry, int errorBuffer, signed int errorBufferSize, int lineNumber)
{
  int currentTopic; // edx
  int v8; // edx
  int v10; // ecx
  int v11; // ecx
  _DWORD *nextTopic; // edx

  if ( !*(_DWORD *)(fileRecord + 80) )
  {
    *(_DWORD *)(fileRecord + 80) = entry;
    goto LABEL_6;
  }
  currentTopic = g_ClipsHelpCurrentTopicNode;
  if ( *entry > *(_DWORD *)g_ClipsHelpCurrentTopicNode )
  {
    if ( *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 4) != -45 )
    {
      Mem_SmallBlockFree(entry, 104);
      fclose_(v10);
      Help_UnloadTopicFile(v11);
      if ( errorBufferSize >= 60 )
        sprintf_(errorBuffer, "Line %d : Non-menu entries cannot have subtopics.", lineNumber);
      return 0;
    }
    entry[24] = g_ClipsHelpCurrentTopicNode;
    goto LABEL_5;
  }
  if ( *entry == *(_DWORD *)g_ClipsHelpCurrentTopicNode )
    goto LABEL_13;
  if ( g_ClipsHelpCurrentTopicNode )
  {
    do
    {
      nextTopic = *(_DWORD **)(g_ClipsHelpCurrentTopicNode + 96);
      g_ClipsHelpCurrentTopicNode = (int)nextTopic;
    }
    while ( nextTopic && *entry < *nextTopic );
  }
  if ( g_ClipsHelpCurrentTopicNode )
  {
    if ( *(_DWORD *)g_ClipsHelpCurrentTopicNode < *entry )
    {
      entry[24] = g_ClipsHelpCurrentTopicNode;
      entry[25] = *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 92);
      currentTopic = g_ClipsHelpCurrentTopicNode;
LABEL_5:
      *(_DWORD *)(currentTopic + 92) = entry;
LABEL_6:
      v8 = 1;
      g_ClipsHelpCurrentTopicNode = (int)entry;
      return v8;
    }
LABEL_13:
    entry[24] = *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 96);
    entry[25] = *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 100);
    *(_DWORD *)(g_ClipsHelpCurrentTopicNode + 100) = entry;
    g_ClipsHelpCurrentTopicNode = (int)entry;
    return 1;
  }
  entry[24] = 0;
  entry[25] = *(_DWORD *)(fileRecord + 80);
  *(_DWORD *)(fileRecord + 80) = entry;
  g_ClipsHelpCurrentTopicNode = (int)entry;
  return 1;
}
// 4A581A: variable 'v10' is possibly undefined
// 4A5825: variable 'v11' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACE4: using guessed type int dword_51ACE4;

//----- (004A5920) --------------------------------------------------------
signed int  Help_FindOrAdvanceTopicEntry(int fileName, _DWORD *menu, _DWORD *status, _BYTE *topicName)
{
  int fileRecord; // ecx
  BOOL noMatch; // eax
  int currentEntry; // ebx
  int parentEntry; // esi
  signed int result; // eax
  int v12; // ecx
  int curEntry; // edx
  int theEntry; // ebx
  BOOL noTopicMatch; // eax
  int fallbackEntry; // eax
  int menuEntry; // ebp

  fileRecord = g_HelpLoadedTopicFileList;
  if ( g_HelpLoadedTopicFileList )
    noMatch = strcmp_(g_HelpLoadedTopicFileList, fileName) != 0;
  else
    noMatch = 0;
  if ( noMatch > 0 )
  {
    do
      fileRecord = *(_DWORD *)(fileRecord + 88);
    while ( fileRecord && strcmp_(fileRecord, fileName) );
  }
  if ( fileRecord )
  {
    if ( topicName )
    {
      Str_UppercaseToDelimiter((int)topicName, fileRecord);
      curEntry = *(_DWORD *)(v12 + 84);
      if ( curEntry )
        theEntry = *(_DWORD *)(curEntry + 92);
      else
        theEntry = *(_DWORD *)(v12 + 80);
      if ( theEntry )
        noTopicMatch = Str_FindSubstringIndex((_BYTE *)(theEntry + 8), topicName) != 0;
      else
        noTopicMatch = 0;
      if ( noTopicMatch > 0 )
      {
        do
          theEntry = *(_DWORD *)(theEntry + 100);
        while ( theEntry && Str_FindSubstringIndex((_BYTE *)(theEntry + 8), topicName) );
      }
      if ( theEntry )
      {
        if ( *(_DWORD *)(theEntry + 4) == -45 )
        {
          *status = -40;
          *(_DWORD *)(v12 + 84) = theEntry;
        }
        else
        {
          *status = 0;
        }
        menuEntry = *(_DWORD *)(v12 + 84);
        if ( menuEntry )
          *menu = menuEntry + 8;
        return *(_DWORD *)(theEntry + 88);
      }
      else
      {
        *status = -25;
        fallbackEntry = *(_DWORD *)(v12 + 84);
        if ( !fallbackEntry )
          return -1;
        *menu = fallbackEntry + 8;
        return *(_DWORD *)(*(_DWORD *)(v12 + 84) + 88);
      }
    }
    else
    {
      currentEntry = *(_DWORD *)(fileRecord + 84);
      if ( currentEntry )
      {
        parentEntry = *(_DWORD *)(currentEntry + 96);
        if ( !parentEntry )
        {
          *status = -30;
          *(_DWORD *)(fileRecord + 84) = 0;
          *menu = 0;
          return -1;
        }
        *(_DWORD *)(fileRecord + 84) = parentEntry;
        *status = -35;
        *menu = *(_DWORD *)(fileRecord + 84) + 8;
        return *(_DWORD *)(*(_DWORD *)(fileRecord + 84) + 88);
      }
      else
      {
        result = -1;
        *status = -30;
      }
    }
  }
  else
  {
    result = -1;
    *status = -10;
  }
  return result;
}
// 4A593F: variable 'v7' is possibly undefined
// 4A59DC: variable 'v12' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51ACE0: using guessed type int dword_51ACE0;

//----- (004A5A80) --------------------------------------------------------
_DWORD * Help_FreeTopicTree(_DWORD *result)
{
  _DWORD *i; // ecx

  for ( i = result; i; result = (_DWORD *)Mem_SmallBlockFree(i, 104) )
  {
    if ( i[23] )
      Help_FreeTopicTree(i[23]);
  }
  return result;
}
// 4A5A88: variable 'i' is possibly undefined

//----- (004A5AB0) --------------------------------------------------------
signed int  Help_RunInteractiveHelpBrowser(int a1, DWORD a2, double a3)
{
  int v3; // ecx
  int v4; // ecx
  int v5; // ecx
  char *mainTopicSrc; // esi
  _BYTE *topicNameDst; // edi
  int topicList; // ebp
  char srcChar; // al
  char srcCharNext; // al
  _DWORD *argTopicList; // eax
  int topicNode; // edx
  int v13; // ecx
  int locatedFp; // eax
  int lineCount; // ecx
  int fp; // esi
  int v17; // ecx
  char *messageText; // edx
  char *routerName; // eax
  signed int result; // eax
  int nodeSize; // ecx
  _DWORD *nodeToFree; // eax
  char *defaultPathSrc; // esi
  _BYTE *helpPathDst; // edi
  char pathChar; // al
  char pathCharNext; // al
  int v27; // ecx
  int v28; // ecx
  int v29; // ecx
  int v30; // ecx
  unsigned int charIndex; // ecx
  char inputChar; // al
  char commandChar; // dl
  int v34; // ecx
  int v35; // ecx
  _BYTE lineBuffer[256]; // [esp+0h] [ebp-120h] BYREF
  _DWORD *status; // [esp+100h] [ebp-20h] BYREF
  int menu[7]; // [esp+104h] [ebp-1Ch] BYREF

  if ( !g_HelpSystemInitialized )
  {
    if ( !g_ClipsHelpFilePath )
    {
      defaultPathSrc = aClips_hlp;
      helpPathDst = Mem_SmallBlockAlloc(strlen(aClips_hlp) + 1);
      g_ClipsHelpFilePath = (int)helpPathDst;
      do
      {
        pathChar = *defaultPathSrc;
        *helpPathDst = *defaultPathSrc;
        if ( !pathChar )
          break;
        pathCharNext = defaultPathSrc[1];
        defaultPathSrc += 2;
        helpPathDst[1] = pathCharNext;
        helpPathDst += 2;
      }
      while ( pathCharNext );
    }
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aLoadingHelpFil, a1);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], g_ClipsHelpFilePath, v3);
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)a_PleaseWait___, v4);
    status = Help_IndexTopicFile((CHAR *)g_ClipsHelpFilePath, lineBuffer, v5, 256, a2);
    if ( !status )
    {
      Rules_PrintErrorID((int)aTextpro, 1, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToAccess, v27);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)lineBuffer, v28);
      return Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50797C, v29);
    }
    IO_AddRouter((int)aWhelp, 10, (int)Rules_HelpRouterPrint, (int)Help_RouterQueryMatchesWhelp, (int)Rules_HelpRouterGetc, (int)Rules_HelpRouterUngetc, 0);
    g_HelpSystemInitialized = 1;
  }
  IO_ActivateRouter((int)aWhelp);
  mainTopicSrc = aMain_2;
  topicNameDst = Mem_SmallBlockAlloc(0x58u);
  topicList = (int)topicNameDst;
  do
  {
    srcChar = *mainTopicSrc;
    *topicNameDst = *mainTopicSrc;
    if ( !srcChar )
      break;
    srcCharNext = mainTopicSrc[1];
    mainTopicSrc += 2;
    topicNameDst[1] = srcCharNext;
    topicNameDst += 2;
  }
  while ( srcCharNext );
  argTopicList = Rules_HelpBuildTopicListFromArgs(a3);
  *(_DWORD *)(topicNode + 80) = 0;
  *(_DWORD *)(topicNode + 84) = argTopicList;
  Output_Write((int)aWhelp, (int)asc_50797C, v13);
  while ( 1 )
  {
    locatedFp = Rules_HelpLocateTopicEntry((const CHAR *)g_ClipsHelpFilePath, topicList, &status, menu);
    fp = locatedFp;
    if ( status == (_DWORD *)-10 )
      break;
    if ( status == (_DWORD *)-30 )
      goto LABEL_12;
    if ( status == (_DWORD *)-25 )
    {
      if ( !locatedFp )
      {
        Output_Write((int)aWhelp, (int)aRootEntryMainN, lineCount);
        Output_Write((int)aWhelp, g_ClipsHelpFilePath, v34);
        messageText = a_SeeExternalDo;
        routerName = aWhelp;
        goto LABEL_11;
      }
      Output_Write((int)aWhelp, (int)aSorryNoInforma, lineCount);
    }
    if ( status != (_DWORD *)-35 )
    {
      while ( 2 )
      {
        if ( !Help_ReadEntryLine(fp, lineBuffer, 256) )
          goto LABEL_43;
        if ( lineCount < 23 )
          goto LABEL_37;
        Output_Write((int)aWhelp, (int)aPressReturnFor, lineCount);
        Output_Write((int)aWhelp, (int)aPressAReturnTo, v30);
        g_Lexer_PendingLineCharIndex = 0;
LABEL_29:
        inputChar = Lexer_PeekChar((int)aWhelp, charIndex);
        commandChar = inputChar;
        switch ( inputChar )
        {
          case 10:
            goto LABEL_34;
          case 97:
            commandChar = 65;
            goto LABEL_32;
          case 8:
            charIndex = g_Lexer_PendingLineCharIndex;
            if ( g_Lexer_PendingLineCharIndex )
              --g_Lexer_PendingLineCharIndex;
            break;
          default:
LABEL_32:
            ++g_Lexer_PendingLineCharIndex;
            break;
        }
        Lexer_PeekChar((int)aWhelp, charIndex);
LABEL_34:
        if ( commandChar == 10 || commandChar == 65 )
        {
          lineCount = 0;
          g_Lexer_PendingLineCharIndex = -1;
          if ( commandChar == 65 )
            goto LABEL_42;
LABEL_37:
          Output_Write((int)aWhelp, (int)lineBuffer, lineCount + 1);
          continue;
        }
        goto LABEL_29;
      }
    }
    if ( fp )
LABEL_42:
      fclose_(lineCount);
LABEL_43:
    topicList = Rules_HelpReadTopicListFromInput(topicList, menu, lineCount);
    if ( g_ClipsHaltExecution )
    {
      while ( status != (_DWORD *)-30 )
      {
        if ( Help_OpenFileAtNavigatedTopic((const CHAR *)g_ClipsHelpFilePath, menu, &status, 0) )
          fclose_(v35);
      }
    }
    if ( status == (_DWORD *)-30 )
      goto LABEL_12;
  }
  Rules_PrintErrorID((int)aTextpro, 1, 0);
  messageText = aUnableToAccess;
  routerName = g_IO_LogicalNameTable_WError[0];
LABEL_11:
  Output_Write((int)routerName, (int)messageText, v17);
LABEL_12:
  result = IO_DeactivateRouter((int)aWhelp);
  if ( topicList )
  {
    nodeSize = 88;
    do
    {
      nodeToFree = (_DWORD *)topicList;
      topicList = *(_DWORD *)(topicList + 84);
      result = Mem_SmallBlockFree(nodeToFree, nodeSize);
    }
    while ( topicList );
  }
  return result;
}
// 4A5AE0: variable 'a1' is possibly undefined
// 4A5AF0: variable 'v3' is possibly undefined
// 4A5B04: variable 'v4' is possibly undefined
// 4A5B10: variable 'v5' is possibly undefined
// 4A5B91: variable 'v12' is possibly undefined
// 4A5BA5: variable 'v13' is possibly undefined
// 4A5BF6: variable 'v17' is possibly undefined
// 4A5C15: variable 'v21' is possibly undefined
// 4A5C8A: variable 'v27' is possibly undefined
// 4A5C96: variable 'v28' is possibly undefined
// 4A5CA5: variable 'v29' is possibly undefined
// 4A5CD4: variable 'v15' is possibly undefined
// 4A5D17: variable 'v30' is possibly undefined
// 4A5D28: variable 'v31' is possibly undefined
// 4A5D8B: variable 'v34' is possibly undefined
// 4A5E02: variable 'v35' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 51A614: using guessed type char *off_51A614[5];
// 51A61C: using guessed type char *off_51A61C[3];
// 51A628: using guessed type int dword_51A628;
// 51A968: using guessed type int dword_51A968;
// 51ACE8: using guessed type int dword_51ACE8;
// 51ACEC: using guessed type int dword_51ACEC;

//----- (004A5E30) --------------------------------------------------------
signed int  Help_SetHelpFilePathCommand(int a1, double a2)
{
  int v2; // ecx
  int v3; // ecx
  int v4; // ecx
  signed int result; // eax
  int v6; // ecx
  char *dialogRouter; // eax
  char *pathToPrint; // edx
  int v9; // ecx
  const char *newPath; // ebx
  const char *srcPtr; // esi
  int v12; // edx
  int v13; // ecx
  _BYTE *dstPtr; // edi
  char v15; // al
  char v16; // al
  int v17; // ecx
  int v18; // ecx
  _DWORD item[11]; // [esp-8h] [ebp-2Ch] BYREF

  item[9] = a1;
  if ( Rules_RtnArgCount() )
  {
    if ( g_ClipsHelpFilePath )
    {
      if ( g_HelpSystemInitialized == 1 )
      {
        Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aReleasingHelpE, v2);
        Output_Write((int)g_IO_LogicalNameTable_WDialog[0], g_ClipsHelpFilePath, v3);
        Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)a___, v4);
        Help_UnloadTopicFile(g_ClipsHelpFilePath);
        IO_DeleteRouter((int)aWhelp);
        g_HelpSystemInitialized = 0;
      }
      Mem_SmallBlockFree((_DWORD *)g_ClipsHelpFilePath, strlen((const char *)g_ClipsHelpFilePath) + 1);
    }
    result = Lexer_ParseValueList(1, item, 111, a2);
    if ( result )
    {
      newPath = *(const char **)(item[2] + 16);
      srcPtr = newPath;
      dstPtr = Mem_SmallBlockAlloc(strlen(newPath) + 1);
      g_ClipsHelpFilePath = (int)dstPtr;
      do
      {
        v15 = *srcPtr;
        *dstPtr = *srcPtr;
        if ( !v15 )
          break;
        v16 = srcPtr[1];
        srcPtr += 2;
        dstPtr[1] = v16;
        dstPtr += 2;
      }
      while ( v16 );
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], v12, v13);
      Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)newPath, v17);
      return Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_50797C, v18);
    }
  }
  else
  {
    Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)aTheCurrentHelp, v2);
    if ( g_ClipsHelpFilePath )
    {
      dialogRouter = g_IO_LogicalNameTable_WDialog[0];
      pathToPrint = (char *)g_ClipsHelpFilePath;
    }
    else
    {
      pathToPrint = aClips_hlp;
      dialogRouter = g_IO_LogicalNameTable_WDialog[0];
    }
    Output_Write((int)dialogRouter, (int)pathToPrint, v6);
    return Output_Write((int)g_IO_LogicalNameTable_WDialog[0], (int)asc_50797C, v9);
  }
  return result;
}
// 4A5E61: variable 'v2' is possibly undefined
// 4A5E71: variable 'v3' is possibly undefined
// 4A5E80: variable 'v4' is possibly undefined
// 4A5F01: variable 'v6' is possibly undefined
// 4A5F10: variable 'v9' is possibly undefined
// 4A5F6B: variable 'v12' is possibly undefined
// 4A5F6B: variable 'v13' is possibly undefined
// 4A5F77: variable 'v17' is possibly undefined
// 4A5F86: variable 'v18' is possibly undefined
// 51A61C: using guessed type char *off_51A61C[3];
// 51ACE8: using guessed type int dword_51ACE8;
// 51ACEC: using guessed type int dword_51ACEC;

//----- (004A5FA0) --------------------------------------------------------
int * Help_LoadHelpFileCommand(DWORD returnValue, double a2)
{
  int *result; // eax
  int v4; // ecx
  CHAR *dstPtr; // edi
  CHAR *srcPtr; // esi
  CHAR v7; // al
  CHAR v8; // al
  _DWORD *entryCount; // eax
  int v10; // ecx
  int v11; // ecx
  char *errorMsg; // edx
  int v13; // ecx
  CHAR fileName[80]; // [esp+0h] [ebp-D0h] BYREF
  _BYTE errorBuffer[80]; // [esp+50h] [ebp-80h] BYREF
  _DWORD item[12]; // [esp+A0h] [ebp-30h] BYREF

  *(_DWORD *)(returnValue + 4) = 2;
  *(_DWORD *)(returnValue + 8) = g_ClipsFalseSymbol;
  result = (int *)Lexer_ParseValueList(1, item, 111, a2);
  if ( result )
  {
    dstPtr = fileName;
    srcPtr = *(CHAR **)(item[2] + 16);
    do
    {
      v7 = *srcPtr;
      *dstPtr = *srcPtr;
      if ( !v7 )
        break;
      v8 = srcPtr[1];
      srcPtr += 2;
      dstPtr[1] = v8;
      dstPtr += 2;
    }
    while ( v8 );
    entryCount = Help_IndexTopicFile(fileName, errorBuffer, v4, 80, returnValue);
    if ( entryCount )
    {
      *(_DWORD *)(returnValue + 4) = 1;
      result = Rules_AddIntegerValue((signed int)entryCount);
      *(_DWORD *)(returnValue + 8) = result;
    }
    else
    {
      Rules_PrintErrorID((int)aTextpro, 2, 0);
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)aUnableToLoadFi, v10);
      if ( errorBuffer[0] )
        errorMsg = errorBuffer;
      else
        errorMsg = aNoEntriesFound;
      Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)errorMsg, v11);
      return (int *)Output_Write((int)g_IO_LogicalNameTable_WError[0], (int)asc_50797C, v13);
    }
  }
  return result;
}
// 4A601A: variable 'v4' is possibly undefined
// 4A603E: variable 'v10' is possibly undefined
// 4A6053: variable 'v11' is possibly undefined
// 4A6062: variable 'v13' is possibly undefined
// 51A614: using guessed type char *off_51A614[5];
// 54DD70: using guessed type int dword_54DD70;

//----- (004A60A0) --------------------------------------------------------
int  Help_PrintRegionCommand(double a1)
{
  _DWORD *topicList; // edi
  _DWORD *topicListHead; // ebp
  int fp; // eax
  int v4; // ecx
  char *lineText; // edx
  int i; // eax
  char *srcPtr; // esi
  char v8; // al
  char v9; // al
  int success; // edi
  int v11; // ecx
  _DWORD *nodeToFree; // eax
  _BYTE lineBuffer[256]; // [esp+4h] [ebp-118h] BYREF
  int menuBuf; // [esp+104h] [ebp-18h] BYREF
  _DWORD statusBuf[5]; // [esp+108h] [ebp-14h] BYREF

  topicList = Rules_HelpBuildTopicListFromArgs(a1);
  topicListHead = topicList;
  fp = Rules_HelpLocateTopicEntry((const CHAR *)topicList[21], *(_DWORD *)(topicList[21] + 84), statusBuf, &menuBuf);
  if ( statusBuf[0] == -10 || statusBuf[0] == -25 || statusBuf[0] == -30 )
  {
    if ( fp )
      fclose_(fp);
    success = 0;
  }
  else
  {
    if ( !strcmp_(fp, aT_1) )
    {
      srcPtr = aStdout_3;
      do
      {
        v8 = *srcPtr;
        *(_BYTE *)topicList = *srcPtr;
        if ( !v8 )
          break;
        v9 = srcPtr[1];
        srcPtr += 2;
        *((_BYTE *)topicList + 1) = v9;
        topicList = (_DWORD *)((char *)topicList + 2);
      }
      while ( v9 );
    }
    lineText = asc_50797C;
    for ( i = (int)topicListHead; ; i = (int)topicListHead )
    {
      Output_Write(i, (int)lineText, v4);
      if ( !Help_ReadEntryLine(fp, lineBuffer, 256) )
        break;
      lineText = lineBuffer;
    }
    success = 1;
  }
  v11 = 88;
  while ( topicListHead )
  {
    nodeToFree = topicListHead;
    topicListHead = (_DWORD *)topicListHead[21];
    Mem_SmallBlockFree(nodeToFree, v11);
  }
  return success;
}
// 4A610D: variable 'v4' is possibly undefined
// 4A6180: variable 'v11' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A6190) --------------------------------------------------------
signed int  Help_UnloadHelpFileCommand(int returnValue, double a2)
{
  signed int result; // eax
  int v4; // ecx
  int fileName; // ebx
  _DWORD theValue[9]; // [esp-8h] [ebp-24h] BYREF

  theValue[7] = returnValue;
  result = Lexer_ParseValueList(1, theValue, 111, a2);
  if ( result )
  {
    fileName = *(_DWORD *)(theValue[2] + 16);
    if ( g_ClipsHelpFilePath && !strcmp_(v4, g_ClipsHelpFilePath) && g_HelpSystemInitialized == 1 )
    {
      Mem_SmallBlockFree((_DWORD *)g_ClipsHelpFilePath, strlen((const char *)g_ClipsHelpFilePath) + 1);
      g_ClipsHelpFilePath = 0;
      g_HelpSystemInitialized = 0;
      IO_DeleteRouter((int)aWhelp);
    }
    return Help_UnloadTopicFile(fileName);
  }
  return result;
}
// 4A61C3: variable 'v4' is possibly undefined
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);
// 51ACE8: using guessed type int dword_51ACE8;
// 51ACEC: using guessed type int dword_51ACEC;

//----- (004A6220) --------------------------------------------------------
BOOL __thiscall Help_RouterQueryMatchesWhelp(void *this)
{
  return strcmp_(this, aWhelp) == 0;
}
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A6240) --------------------------------------------------------
int __fastcall Rules_HelpRouterPrint(int logicalName, int message)
{
  Output_Write((int)aStdout_3, message, logicalName);
  return 1;
}

//----- (004A6250) --------------------------------------------------------
int __thiscall Rules_HelpRouterGetc(void *this)
{
  return Lexer_PeekChar((int)aStdin_3, (unsigned int)this);
}

//----- (004A6260) --------------------------------------------------------
signed int  Rules_HelpRouterUngetc(signed int theChar, int logicalName)
{
  return Lexer_SkipChar(theChar, (int)aStdin_3, logicalName);
}

//----- (004A6270) --------------------------------------------------------
_DWORD * Rules_HelpBuildTopicListFromArgs(double a1)
{
  int theIndex; // edi
  _DWORD *head; // ebp
  _DWORD *theTopic; // esi
  _DWORD *v4; // edx
  int v5; // ecx
  char *topicName; // edx
  _DWORD *i; // eax
  int argType; // [esp+4h] [ebp-30h]
  int argValue; // [esp+8h] [ebp-2Ch]
  int numArgs; // [esp+18h] [ebp-1Ch]

  theIndex = 1;
  numArgs = Rules_RtnArgCount();
  head = 0;
  if ( numArgs >= 1 )
  {
    do
    {
      theTopic = Mem_SmallBlockAlloc(0x58u);
      Rules_RtnUnknown(theIndex, v4, a1);
      if ( argType == 2 || argType == 3 )
      {
        topicName = *(char **)(argValue + 16);
      }
      else if ( argType )
      {
        if ( argType == 1 )
          topicName = (char *)Rules_LongIntegerToSymbol(*(_DWORD *)(argValue + 16));
        else
          topicName = aError_4;
      }
      else
      {
        topicName = (char *)Rules_FloatToSymbol(v5, *(double *)(argValue + 16));
      }
      strncpy_(v5, topicName);
      theTopic[21] = 0;
      theTopic[20] = 0;
      if ( head )
      {
        for ( i = head; i[21]; i = (_DWORD *)i[21] )
          ;
        i[21] = theTopic;
      }
      else
      {
        head = theTopic;
      }
      ++theIndex;
    }
    while ( theIndex <= numArgs );
  }
  return head;
}
// 4A629F: variable 'v4' is possibly undefined
// 4A62AB: variable 'v9' is possibly undefined
// 4A62BD: variable 'v10' is possibly undefined
// 4A62C0: variable 'v5' is possibly undefined
// 48521A: using guessed type int __fastcall strncpy_(_DWORD, _DWORD);

//----- (004A6350) --------------------------------------------------------
int  Rules_HelpReadTopicListFromInput(int topicList, int *menu, int a3)
{
  int v4; // ecx
  int charIndex; // edx
  unsigned int peekOffset; // ecx
  char inputChar; // al
  int wordLength; // ecx
  int scanIndex; // edx
  char ch; // bl
  int resultList; // esi
  char scanChar; // bh
  char *wordSrc; // esi
  char *newTopic; // ebx
  char *topicDst; // edi
  char newNodeByte; // al
  char newNodeNextByte; // al
  int tailNode; // esi
  char *copySrc; // esi
  char *copyDst; // edi
  char nodeByte; // al
  char nodeNextByte; // al
  char v24; // [esp-1h] [ebp-16Dh]
  _BYTE lineBuffer[256]; // [esp+0h] [ebp-16Ch]
  char wordBuffer[80]; // [esp+100h] [ebp-6Ch] BYREF
  char *newTopicPtr; // [esp+150h] [ebp-1Ch]
  int listHead; // [esp+154h] [ebp-18h]

  Output_Write((int)aWhelp, *menu, a3);
  Output_Write((int)aWhelp, (int)aTopic_, v4);
  charIndex = 0;
  g_Lexer_PendingLineCharIndex = 0;
  peekOffset = -2;
  while ( 1 )
  {
    inputChar = Lexer_PeekChar((int)aWhelp, peekOffset);
    lineBuffer[charIndex] = inputChar;
    if ( inputChar == 10 || charIndex >= 254 || g_ClipsHaltExecution )
      break;
    if ( inputChar == 9 )
    {
      lineBuffer[charIndex] = 32;
      goto LABEL_14;
    }
    if ( inputChar == 8 && charIndex )
    {
      g_Lexer_PendingLineCharIndex += peekOffset;
      charIndex = charIndex - 2 + 1;
      ++g_Lexer_PendingLineCharIndex;
    }
    else
    {
LABEL_14:
      ++charIndex;
      ++g_Lexer_PendingLineCharIndex;
    }
  }
  wordLength = g_ClipsHaltExecution;
  g_Lexer_PendingLineCharIndex = -1;
  if ( g_ClipsHaltExecution )
  {
    Output_Write((int)aWhelp, (int)asc_50797C, g_ClipsHaltExecution);
    *(_DWORD *)(topicList + 80) = topicList;
    return topicList;
  }
  else
  {
    lineBuffer[charIndex] = 32;
    lineBuffer[charIndex + 1] = 0;
    listHead = topicList;
    scanIndex = 0;
    while ( lineBuffer[scanIndex] )
    {
      ch = lineBuffer[scanIndex];
      if ( ch == 32 || wordLength >= 80 )
      {
        if ( wordLength <= 0 )
        {
          ++scanIndex;
        }
        else
        {
          while ( 1 )
          {
            scanChar = lineBuffer[scanIndex];
            if ( scanChar == 32 || !scanChar )
              break;
            ++scanIndex;
          }
          wordBuffer[wordLength] = 0;
          wordLength = 0;
          if ( topicList )
          {
            copySrc = wordBuffer;
            copyDst = (char *)topicList;
            v24 = HIBYTE(topicList);
            do
            {
              nodeByte = *copySrc;
              *copyDst = *copySrc;
              if ( !nodeByte )
                break;
              nodeNextByte = copySrc[1];
              copySrc += 2;
              copyDst[1] = nodeNextByte;
              copyDst += 2;
            }
            while ( nodeNextByte );
            topicList = *(_DWORD *)(topicList + 84);
          }
          else
          {
            wordSrc = wordBuffer;
            newTopic = (char *)Mem_SmallBlockAlloc(0x58u);
            topicDst = newTopic;
            newTopicPtr = newTopic;
            v24 = HIBYTE(newTopic);
            do
            {
              newNodeByte = *wordSrc;
              *topicDst = *wordSrc;
              if ( !newNodeByte )
                break;
              newNodeNextByte = wordSrc[1];
              wordSrc += 2;
              topicDst[1] = newNodeNextByte;
              topicDst += 2;
            }
            while ( newNodeNextByte );
            *((_DWORD *)newTopic + 21) = wordLength;
            tailNode = listHead;
            *((_DWORD *)newTopic + 20) = wordLength;
            if ( tailNode )
            {
              for ( ; *(_DWORD *)(tailNode + 84); tailNode = *(_DWORD *)(tailNode + 84) )
                ;
              *(_DWORD *)(tailNode + 84) = newTopicPtr;
            }
            else
            {
              listHead = (int)newTopic;
            }
          }
        }
      }
      else
      {
        ++wordLength;
        ++scanIndex;
        lineBuffer[wordLength + 255] = ch;
      }
    }
    resultList = listHead;
    *(_DWORD *)(listHead + 80) = topicList;
    return resultList;
  }
}
// 4A6373: variable 'v4' is possibly undefined
// 4A638E: variable 'v6' is possibly undefined
// 4A63DC: variable 'v9' is possibly undefined
// 4A63EB: variable 'v8' is possibly undefined
// 51A628: using guessed type int dword_51A628;
// 51A968: using guessed type int dword_51A968;

//----- (004A6550) --------------------------------------------------------
int  Rules_HelpLocateTopicEntry(const CHAR *fileName, int topicList, _DWORD *statusOut, _DWORD *entryTitleOut)
{
  _DWORD *statusPtr; // edi
  int result; // eax
  int topicNode; // esi
  int v8; // ecx
  _DWORD *v9; // edx
  _DWORD *v10; // ecx
  const CHAR *v11; // eax
  _BYTE *topicName; // ebx
  int listEnd; // [esp+4h] [ebp-10h]

  statusPtr = statusOut;
  result = 0;
  if ( topicList )
    listEnd = *(_DWORD *)(topicList + 80);
  else
    listEnd = 0;
  topicNode = topicList;
  if ( topicList != listEnd )
  {
    while ( 1 )
    {
      if ( result )
        fclose_(statusOut);
      if ( !strcmp_(statusOut, asc_507B10) )
        break;
      if ( strcmp_(v8, aQuestionMark_507B14) || listEnd != *(_DWORD *)(topicNode + 84) )
      {
        v9 = entryTitleOut;
        v10 = statusPtr;
        topicName = (_BYTE *)topicNode;
        v11 = fileName;
        goto LABEL_8;
      }
      result = Help_ReopenFileAtActiveEntry(fileName, statusPtr, (DWORD)fileName);
LABEL_9:
      statusOut = (_DWORD *)*statusPtr;
      if ( *statusPtr != -10 && statusOut != (_DWORD *)-25 )
      {
        topicNode = *(_DWORD *)(topicNode + 84);
        if ( topicNode != listEnd )
          continue;
      }
      return result;
    }
    v9 = entryTitleOut;
    v10 = statusPtr;
    v11 = fileName;
    topicName = 0;
LABEL_8:
    result = Help_OpenFileAtNavigatedTopic(v11, v9, v10, topicName);
    goto LABEL_9;
  }
  return Help_OpenFileAtNavigatedTopic(fileName, entryTitleOut, statusOut, 0);
}
// 4A6580: variable 'a3' is possibly undefined
// 4A65CC: variable 'v8' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 476330: using guessed type int __fastcall strcmp_(_DWORD, _DWORD);

//----- (004A6610) --------------------------------------------------------
signed int Rules_RegisterHelpFunctions(void)
{
  Rules_RegisterHostFunction(aHelp, 118, (int)aHelpfunction, (int)Help_RunInteractiveHelpBrowser, 0);
  Rules_RegisterHostFunction(aHelpPath, 118, (int)aHelppathfuncti, (int)Help_SetHelpFilePathCommand, (int)a1k);
  Rules_RegisterHostFunction(aFetch, 117, (int)aFetchcommand, (int)Help_LoadHelpFileCommand, (int)a11k_2);
  Rules_RegisterHostFunction(aToss, 98, (int)aTosscommand, (int)Help_UnloadHelpFileCommand, (int)a11k_2);
  return Rules_RegisterHostFunction(aPrintRegion, 98, (int)aPrintregioncom, (int)Help_PrintRegionCommand, (int)a2Wk);
}

//----- (004A66B0) --------------------------------------------------------
int  Rules_ConstructsToCCommand(double a1)
{
  int result; // eax
  int argCount; // ebp
  const char *fileName; // esi
  int v4; // ecx
  int v5; // ecx
  int v6; // ecx
  int imageId; // edi
  int maxIndices; // ebx
  _DWORD item[2]; // [esp+0h] [ebp-30h] BYREF
  int itemValue; // [esp+8h] [ebp-28h]

  result = Rules_ArgRangeCheck((int)aConstructsToC, 3);
  argCount = result;
  if ( result != -1 )
  {
    result = Lexer_ParseValueList(1, item, 111, a1);
    if ( result )
    {
      fileName = *(const char **)(itemValue + 16);
      if ( (int)strlen(fileName) > 3 )
      {
        Rules_PrintWarningID((int)aConscomp, 1, 0);
        Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aBaseFileNameEx, v4);
        Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aThisMayCauseFi, v5);
        Output_Write((int)g_IO_LogicalNameTable_WWarning[0], (int)aIsLimitedOnYou, v6);
      }
      result = Lexer_ParseValueList(2, item, 1, a1);
      if ( result )
      {
        imageId = *(_DWORD *)(itemValue + 16);
        if ( imageId < 0 )
        {
          return Parser_ReportError(2, (int)aPositiveIntege);
        }
        else
        {
          if ( argCount != 3 )
          {
            maxIndices = 10000;
            return Rules_ConstructsToC(fileName, imageId, maxIndices, (char)fileName);
          }
          result = Lexer_ParseValueList(3, item, 1, a1);
          if ( result )
          {
            maxIndices = *(_DWORD *)(itemValue + 16);
            if ( maxIndices >= 0 )
              return Rules_ConstructsToC(fileName, imageId, maxIndices, (char)fileName);
            return Parser_ReportError(3, (int)aPositiveIntege);
          }
        }
      }
    }
  }
  return result;
}
// 4A672B: variable 'v4' is possibly undefined
// 4A673A: variable 'v5' is possibly undefined
// 4A6749: variable 'v6' is possibly undefined
// 51A610: using guessed type char *off_51A610[6];

//----- (004A6800) --------------------------------------------------------
signed int  Rules_ConstructsToC(const char *fileName, int imageId, int maxIndices, char a4)
{
  int imageIdLocal; // ecx
  int codeGenItem; // edx
  int v7; // ecx
  int v8; // ecx
  int headerFile; // eax
  int v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // ecx
  int v14; // edx
  int v15; // ecx
  int v16; // ecx
  int v17; // edx
  int v18; // edx
  int v19; // ecx
  int v20; // edx
  int v21; // ecx
  int v22; // edx
  int v23; // ecx
  int v24; // edx
  int v25; // ecx
  int v26; // edx
  int v27; // ecx
  int v28; // edx
  int v29; // edx
  int v30; // ecx
  int v31; // edx
  int v32; // ecx
  char headerFileHandle; // bl
  int v34; // edx
  int codeItem; // esi
  int i; // edi
  int codeGenIndex; // edx
  int v38; // ecx
  int v39; // ecx
  int v40; // ecx
  char v42; // [esp-8h] [ebp-60h]
  char v43; // [esp-8h] [ebp-60h]
  char v44; // [esp-8h] [ebp-60h]
  char v45; // [esp-8h] [ebp-60h]
  char v46; // [esp-8h] [ebp-60h]
  char v47; // [esp-8h] [ebp-60h]
  char v48; // [esp-8h] [ebp-60h]
  char v49; // [esp-8h] [ebp-60h]
  char v50; // [esp-8h] [ebp-60h]
  char v51; // [esp-8h] [ebp-60h]
  char v52; // [esp-8h] [ebp-60h]
  char v53; // [esp-8h] [ebp-60h]
  char v54; // [esp-8h] [ebp-60h]
  CHAR headerFileName[88]; // [esp+0h] [ebp-58h] BYREF

  imageIdLocal = imageId;
  codeGenItem = g_CodeGeneratorItemList;
  for ( g_ClipsCodeMaxIndicesPerArray = maxIndices; codeGenItem; codeGenItem = *(_DWORD *)(codeGenItem + 24) )
  {
    if ( *(_DWORD *)(codeGenItem + 4) )
      (*(void (__fastcall **)(int))(codeGenItem + 4))(imageIdLocal);
  }
  Rules_RunPeriodicCleanup(0, 0);
  g_Rules_ConstructsToCodeBaseName = (int)fileName;
  g_ConstructsToCImageId = v7;
  g_ClipsCodeDataFile = 0;
  g_ClipsConstructCodeEntryIndexInFile = 0;
  g_ClipsExpressionCodeFileVersion = 1;
  g_Rules_ExprCodeNeedNewFileFlag = 1;
  sprintf_(headerFileName, "%s.h", fileName);
  headerFile = IO_FOpen(headerFileName, (unsigned __int8 *)aW_2, v8, (DWORD)fileName);
  g_ClipsCodeHeaderFile = headerFile;
  if ( headerFile )
  {
    Output_WriteFormatted(v11, v10, headerFile, (int)aIfndef_constru, a4);
    Output_WriteFormatted(v13, v12, g_ClipsCodeHeaderFile, (int)aDefine_constru, v42);
    Output_WriteFormatted(v15, v14, g_ClipsCodeHeaderFile, (int)aIncludeStdio_h, v43);
    Output_WriteFormatted(v16, g_ClipsCodeHeaderFile, g_ClipsCodeHeaderFile, (int)aIncludeSetup_h, v44);
    Output_WriteFormatted(g_ClipsCodeHeaderFile, v17, g_ClipsCodeHeaderFile, (int)aIncludeExpress, v45);
    Output_WriteFormatted(v19, v18, g_ClipsCodeHeaderFile, (int)aIncludeExtnfun, v46);
    Output_WriteFormatted(v21, v20, g_ClipsCodeHeaderFile, (int)aIncludeClips_h, v47);
    Output_WriteFormatted(v23, v22, g_ClipsCodeHeaderFile, (int)aDefineVsVoid, v48);
    Output_WriteFormatted(v25, v24, g_ClipsCodeHeaderFile, (int)asc_507D2C, v49);
    Rules_PrintExternalFunctionDeclarations(g_ClipsCodeHeaderFile, v26);
    Output_WriteFormatted(v27, g_ClipsCodeHeaderFile, g_ClipsCodeHeaderFile, (int)aEndif, v50);
    Output_WriteFormatted(g_ClipsCodeHeaderFile, v28, g_ClipsCodeHeaderFile, (int)asc_507D3C, v51);
    Output_WriteFormatted(v30, v29, g_ClipsCodeHeaderFile, (int)aExternArrayDef, v52);
    Output_WriteFormatted(v32, v31, g_ClipsCodeHeaderFile, (int)asc_507D7C, v53);
    Compiler_GenerateConstructTables((DWORD)fileName);
    Rules_WriteFunctionDefinitionRecordsToCode(fileName);
    Rules_WriteHashedExpressionsToCode((DWORD)fileName);
    headerFileHandle = g_ClipsCodeHeaderFile;
    Compiler_WriteConstraintTableFile(fileName, v34, g_ConstructsToCImageId, g_ClipsCodeHeaderFile, g_ClipsCodeMaxIndicesPerArray);
    codeItem = g_CodeGeneratorItemList;
    for ( i = 5; codeItem; codeItem = *(_DWORD *)(codeItem + 24) )
    {
      if ( *(_DWORD *)(codeItem + 12) )
      {
        headerFileHandle = g_ClipsCodeHeaderFile;
        codeGenIndex = i++;
        (*(void (__fastcall **)(int, int, int))(codeItem + 12))(g_ConstructsToCImageId, codeGenIndex, g_ClipsCodeMaxIndicesPerArray);
      }
    }
    Rules_RestoreAtomicValueBuckets();
    if ( g_ClipsCodeDataFile )
    {
      Output_WriteFormatted(v38, g_ClipsCodeDataFile, g_ClipsCodeDataFile, (int)asc_507DA0, v54);
      fclose_(v39);
    }
    Rules_WriteConstructsToCDriverFile(fileName, headerFileHandle, (DWORD)fileName);
    fclose_(v40);
    return 1;
  }
  else
  {
    Rules_OpenFileErrorMessage(v11, (int)headerFileName);
    return 0;
  }
}
// 4A681F: variable 'v5' is possibly undefined
// 4A6822: variable 'v6' is possibly undefined
// 4A683A: variable 'v7' is possibly undefined
// 4A6875: variable 'v8' is possibly undefined
// 4A688F: variable 'v11' is possibly undefined
// 4A688F: variable 'v10' is possibly undefined
// 4A68A3: variable 'v13' is possibly undefined
// 4A68A3: variable 'v12' is possibly undefined
// 4A68A3: variable 'v42' is possibly undefined
// 4A68B6: variable 'v15' is possibly undefined
// 4A68B6: variable 'v14' is possibly undefined
// 4A68B6: variable 'v43' is possibly undefined
// 4A68CA: variable 'v16' is possibly undefined
// 4A68CA: variable 'v44' is possibly undefined
// 4A68DE: variable 'v17' is possibly undefined
// 4A68DE: variable 'v45' is possibly undefined
// 4A68F2: variable 'v19' is possibly undefined
// 4A68F2: variable 'v18' is possibly undefined
// 4A68F2: variable 'v46' is possibly undefined
// 4A6906: variable 'v21' is possibly undefined
// 4A6906: variable 'v20' is possibly undefined
// 4A6906: variable 'v47' is possibly undefined
// 4A691A: variable 'v23' is possibly undefined
// 4A691A: variable 'v22' is possibly undefined
// 4A691A: variable 'v48' is possibly undefined
// 4A692D: variable 'v25' is possibly undefined
// 4A692D: variable 'v24' is possibly undefined
// 4A692D: variable 'v49' is possibly undefined
// 4A693A: variable 'v26' is possibly undefined
// 4A694B: variable 'v27' is possibly undefined
// 4A694B: variable 'v50' is possibly undefined
// 4A695F: variable 'v28' is possibly undefined
// 4A695F: variable 'v51' is possibly undefined
// 4A6973: variable 'v30' is possibly undefined
// 4A6973: variable 'v29' is possibly undefined
// 4A6973: variable 'v52' is possibly undefined
// 4A6987: variable 'v32' is possibly undefined
// 4A6987: variable 'v31' is possibly undefined
// 4A6987: variable 'v53' is possibly undefined
// 4A69BC: variable 'v34' is possibly undefined
// 4A6A0C: variable 'v38' is possibly undefined
// 4A6A0C: variable 'v54' is possibly undefined
// 4A6A19: variable 'v39' is possibly undefined
// 4A6A2A: variable 'v40' is possibly undefined
// 475DC3: using guessed type int __thiscall fclose_(_DWORD);
// 4761CE: using guessed type double sprintf_(_DWORD, const char *, ...);
// 51ACF0: using guessed type int dword_51ACF0;
// 51ACF4: using guessed type int dword_51ACF4;
// 54E6D0: using guessed type int dword_54E6D0;
// 54E6D4: using guessed type int dword_54E6D4;
// 54E6D8: using guessed type int dword_54E6D8;
// 54E6DC: using guessed type int dword_54E6DC;
// 54E6E0: using guessed type int dword_54E6E0;
// 54E6E4: using guessed type int dword_54E6E4;
// 54E6E8: using guessed type int dword_54E6E8;

//----- (004A6B10) --------------------------------------------------------
int  Rules_PrintExternalFunctionDeclarations(int codeFile, int a2)
{
  int v2; // edx
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int result; // eax
  int v9; // edx
  int v10; // ecx
  int i; // ebx
  int v12; // edx
  int v13; // ecx
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  char v17; // [esp-8h] [ebp-Ch]
  char v18; // [esp-8h] [ebp-Ch]
  char v19; // [esp-8h] [ebp-Ch]
  char v20; // [esp-8h] [ebp-Ch]
  char v21; // [esp-8h] [ebp-Ch]

  Output_WriteFormatted(codeFile, a2, codeFile, (int)asc_507D2C, a2);
  Output_WriteFormatted(v3, v2, v3, (int)asc_507DA4, v17);
  Output_WriteFormatted(v5, v4, v5, (int)aExternalFuncti, v18);
  Output_WriteFormatted(v7, v6, v7, (int)asc_507DF4, v19);
  result = Rules_GetFunctionDefinitionListHead();
  for ( i = result; i; i = *(_DWORD *)(i + 27) )
  {
    Output_WriteFormatted(v10, v9, v10, (int)aExtern, v20);
    switch ( *(_BYTE *)(i + 8) )
    {
      case 'a':
      case 'x':
        Output_WriteFormatted(v13, v12, v13, (int)aVoid, v21);
        break;
      case 'b':
      case 'i':
        Output_WriteFormatted(v13, v12, v13, (int)aInt, v21);
        break;
      case 'c':
        Output_WriteFormatted(v13, v12, v13, (int)aChar, v21);
        break;
      case 'd':
        Output_WriteFormatted(v13, v12, v13, (int)aDouble, v21);
        break;
      case 'f':
        Output_WriteFormatted(v13, v12, v13, (int)aFloat_3, v21);
        break;
      case 'j':
      case 'k':
      case 'm':
      case 'n':
      case 'u':
      case 'v':
        Output_WriteFormatted(v13, v12, v13, (int)aVoid_0, v21);
        break;
      case 'l':
        Output_WriteFormatted(v13, v12, v13, (int)aLong, v21);
        break;
      case 'o':
      case 's':
      case 'w':
        Output_WriteFormatted(v13, v12, v13, (int)aSymbol_hn, v21);
        break;
      default:
        Rules_ReportSystemError(v13, 1);
        break;
    }
    Output_WriteFormatted(v14, *(_DWORD *)(i + 4), v14, (int)aS_10, *(_DWORD *)(i + 4));
    switch ( *(_BYTE *)(i + 8) )
    {
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'f':
      case 'i':
      case 'l':
      case 'o':
      case 's':
      case 'v':
      case 'w':
      case 'x':
        Output_WriteFormatted(v16, v15, v16, (int)aVoid_arg, v21);
        break;
      case 'j':
      case 'k':
      case 'm':
      case 'n':
      case 'u':
        Output_WriteFormatted(v16, v15, v16, (int)aData_object_pt, v21);
        break;
      default:
        break;
    }
    result = Output_WriteFormatted(v16, v15, v16, (int)asc_507E90, v21);
  }
  return result;
}
// 4A6B29: variable 'v3' is possibly undefined
// 4A6B29: variable 'v2' is possibly undefined
// 4A6B29: variable 'v17' is possibly undefined
// 4A6B37: variable 'v5' is possibly undefined
// 4A6B37: variable 'v4' is possibly undefined
// 4A6B37: variable 'v18' is possibly undefined
// 4A6B45: variable 'v7' is possibly undefined
// 4A6B45: variable 'v6' is possibly undefined
// 4A6B45: variable 'v19' is possibly undefined
// 4A6B62: variable 'v10' is possibly undefined
// 4A6B62: variable 'v9' is possibly undefined
// 4A6B62: variable 'v20' is possibly undefined
// 4A6B89: variable 'v13' is possibly undefined
// 4A6B89: variable 'v12' is possibly undefined
// 4A6B89: variable 'v21' is possibly undefined
// 4A6B9B: variable 'v14' is possibly undefined
// 4A6BBE: variable 'v16' is possibly undefined
// 4A6BBE: variable 'v15' is possibly undefined
