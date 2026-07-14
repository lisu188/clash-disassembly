/* Final deterministic top-up: reachable branches in "clean" (non-decompiler-UB)
 * functions, driven with fully-constructed fixtures. Included into test_all.c. */

/* WCIsvListBase_base_sget pops the head link of a Watcom intrusive list.
 * The handle helpers are bare casts (handle == pointer), and this is a -no-pie
 * build so static buffers live at low, 32-bit-safe addresses. Build a real
 * list + head link and drive the pop path (list->head_link = head->next_link;
 * tail clear; count decrement; return link_handle). */
TEST(extra_wclist, sget_pop_head) {
  /* WCCompatListBase: head_link+0, vtable+4, tail_link+8, count+12 (6 ints).
   * WCCompatLink: next_link+0, value+4. */
  static int list[6];
  static int link[2];
  int rv;

  memset(list, 0, sizeof list);
  memset(link, 0, sizeof link);
  link[0] = 0;                       /* next_link = 0 -> tail cleared branch */
  link[1] = 0x1234;                  /* value */
  list[0] = (int)(intptr_t)link;     /* head_link -> our link */
  list[2] = (int)(intptr_t)link;     /* tail_link */
  list[3] = 1;                       /* count = 1 -> decrement branch */

  rv = WCIsvListBase_base_sget((int)(intptr_t)list);
  CHECK_EQ(rv, (int)(intptr_t)link); /* returns the popped link handle */
  CHECK_EQ(list[0], 0);              /* head_link now head->next_link (0) */
  CHECK_EQ(list[3], 0);              /* count decremented to 0 */
}

/* Empty-list and missing-link early returns for completeness (also cheap,
 * deterministic coverage of the guard lines). */
TEST(extra_wclist, sget_empty) {
  static int list[6];
  memset(list, 0, sizeof list);
  CHECK_EQ(WCIsvListBase_base_sget((int)(intptr_t)list), 0); /* !head_link */
  CHECK_EQ(WCIsvListBase_base_sget(0), 0);                   /* !list */
}
