#pragma once

#include "common.hpp"

namespace clash95 {
namespace cpp {

// Conservative wrapper for the AVI decompressor class family recovered from
// the map and C/asm evidence.
//
// The public surface is intentionally a raw-handle view with layout notes; it
// does not claim ownership or full decoded-frame semantics.
class CAviDecompressor final {
public:
  CAviDecompressor() noexcept;
  explicit CAviDecompressor(RawHandle raw) noexcept;

  static CAviDecompressor from_raw(RawHandle raw) noexcept;

  RawHandle raw() noexcept;
  const void *raw() const noexcept;

  bool empty() const noexcept;
  void reset(RawHandle raw = nullptr) noexcept;

  int frames() const noexcept;
  int fps() const noexcept;
  bool is_playing() const noexcept;
  bool initialized() const noexcept;
  int palette() const noexcept;
  int header() const noexcept;
  int pixel_size() const noexcept;
  int bpp() const noexcept;
  int width() const noexcept;
  int height() const noexcept;
  int decoded_frame() const noexcept;
  unsigned int time_ms() const noexcept;
  int sum_sleep_time() const noexcept;

  void start() noexcept;
  void stop() noexcept;
  void done() noexcept;
  void wait_for_next_frame() noexcept;

  void init_clip_rect(const Rect &clip_rect) noexcept;
  void update_pos(long x, int y, long z) noexcept;
  void update_rect(const Rect &rect) noexcept;
  void blit() noexcept;
  void blit_to(long x, int y, long z) noexcept;
  void stretch_to(const Rect &rect) noexcept;
  void get_rect(Rect &rect) const noexcept;
  void init_color_keys(int low_key, int high_key) noexcept;
  void init_pos(int x, int y) noexcept;
  void init_rect(const Rect &rect) noexcept;
  void init_overlays(char enabled) noexcept;
  void set_background(void *background_surface, const Rect &clip_rect, int options) noexcept;

private:
  RawHandle raw_;
};

} // namespace cpp
} // namespace clash95
