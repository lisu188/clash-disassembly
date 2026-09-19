int clash95::UnitTurn::Unit_UpdatePerTurn(int buildingPtr, int a2)
{
  typedef _WORD PackedWord __attribute__((aligned(1), may_alias));
  __int16 currentHitPoints; // dx
  unsigned __int16 maxHitPoints; // cx
  int damagePercent; // eax
  int damageUpper; // esi
  int damageLower; // ebx
  int result; // eax
  int slotWalker; // ecx
  char rolledDamage; // dl

  (void)a2;
  currentHitPoints = *(PackedWord *)(uintptr_t)(buildingPtr + 16);
  if ( !currentHitPoints )
  {
    memset((void *)(uintptr_t)(unsigned int)(buildingPtr + 422), 100, 7);
    return buildingPtr + 422;
  }
  maxHitPoints = this->state_field_1_[*(char *)(uintptr_t)(buildingPtr + 4)];
  damagePercent = 100 * (maxHitPoints - currentHitPoints) / maxHitPoints;
  damageUpper = damagePercent + 10;
  damageLower = damagePercent - 10;
  slotWalker = buildingPtr;
  do
  {
    result = ::Rng_RandRange(damageLower, damageUpper);
    rolledDamage = result;
    if ( result < 0 )
    {
      rolledDamage = 0;
    }
    else if ( result > 100 )
    {
      rolledDamage = 100;
    }
    ++slotWalker;
    *(_BYTE *)(uintptr_t)(slotWalker + 421) = rolledDamage;
  }
  while ( slotWalker != buildingPtr + 7 );
  return result;
}
