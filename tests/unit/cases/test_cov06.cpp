/* cov06 experiment scratch - will be overwritten */
TEST(cov06_exp, widget_button) {
  unsigned char widget[256];
  memset(widget, 0, sizeof(widget));
  TOUCH(MainMenu_RequestExit((uintptr_t)widget));
}
