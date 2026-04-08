namespace clash95 {
namespace cpp {

// Force the executable target onto the C++ link path while the actual startup
// harness is still rooted in `bootstrap_main.c`.
int cpp_regen_link_anchor(void)
{
  return 0;
}

} // namespace cpp
} // namespace clash95
