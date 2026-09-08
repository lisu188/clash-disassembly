class ReferenceUnitTurn final {
 public:
  explicit ReferenceUnitTurn(__int16 (&hp)[4]) : state_field_1_(hp) {}
  int Unit_UpdatePerTurn(int buildingPtr, int a2);
 private:
  __int16 (&state_field_1_)[4];
};
