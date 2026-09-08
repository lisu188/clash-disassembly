DWORD  DLXSprite_LoadCachedEntry(DWORD sprite, char *file_name, int entry_index)
{
  int query_handle; // [esp+100h] [ebp-1Ch] BYREF
  int entry_offset; // [esp+104h] [ebp-18h]
  int entry_end_offset; // [esp+108h] [ebp-14h]
  int payload_size;
  unsigned int payload_handle;
  char path[256]; // [esp+0h] [ebp-11Ch] BYREF

  *(_DWORD *)(uintptr_t)(sprite + 10) = 0;
  strcpy(path, aGfx_3);
  strcat(path, file_name);
  query_handle = FileSystem_ResolveReadPath(path, 1);
  if ( !query_handle )
    return sprite;
  Compat_QueryRead(query_handle, g_DlxDirectoryEntryStartOffsets, DLX_DIRECTORY_BYTES);
  entry_offset = g_DlxDirectoryEntryStartOffsets[entry_index];
  if ( g_DlxDirectoryEntryEndOffsets[entry_index] )
    entry_end_offset = g_DlxDirectoryEntryEndOffsets[entry_index];
  else
    entry_end_offset = IO_QueryVTableStreamSize(query_handle);
  *(_DWORD *)(uintptr_t)(sprite + 14) = entry_end_offset - entry_offset;
  Compat_QuerySeek(query_handle, entry_offset);
  Compat_QueryRead(query_handle, (void *)(uintptr_t)(unsigned int)sprite, 10);
  payload_size = *(_DWORD *)(uintptr_t)(sprite + 14) - 10;
  payload_handle = (unsigned int)nmalloc_(payload_size, 4);
  *(_DWORD *)(uintptr_t)(sprite + 10) = payload_handle;
  if ( !*(_DWORD *)(uintptr_t)(sprite + 10) )
  {
    Debug_Log(0, 10, payload_size, (int)(intptr_t)aNotEnoughMem_7);
    App_RequestQuit((int)(intptr_t)aNotEnoughMem_8);
  }
  Compat_QueryRead(query_handle, (void *)(uintptr_t)payload_handle, payload_size);
  Compat_FileSystemQueryRelease((int)(intptr_t)&g_FileSystemMountTable, &query_handle);
  return sprite;
}
