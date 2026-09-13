int  UnitStack_CalcMilitaryStrength(int stackPtr)
{
  signed int squadCount; // eax

  squadCount = Unit_GetSquadCount(stackPtr);
  // 0x412BE3 retains the input in EDX; the LEA at 0x412BEA wraps at 32 bits.
  return UnitSlots_CalcCombatStrengthScoreWithSpecialPersonageCheck((char *)(uintptr_t)((uint32_t)stackPtr + 6u), squadCount, 0);
}
