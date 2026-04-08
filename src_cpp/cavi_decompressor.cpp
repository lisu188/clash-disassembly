#include "clash95/cpp/cavi_decompressor.hpp"

namespace clash95 {
namespace cpp {

CAviDecompressor::CAviDecompressor() noexcept : raw_(nullptr) {}

CAviDecompressor::CAviDecompressor(RawHandle raw) noexcept : raw_(raw) {}

CAviDecompressor CAviDecompressor::from_raw(RawHandle raw) noexcept
{
  return CAviDecompressor(raw);
}

RawHandle CAviDecompressor::raw() noexcept
{
  return raw_;
}

const void *CAviDecompressor::raw() const noexcept
{
  return raw_;
}

bool CAviDecompressor::empty() const noexcept
{
  return raw_ == nullptr;
}

void CAviDecompressor::reset(RawHandle raw) noexcept
{
  raw_ = raw;
}

int CAviDecompressor::frames() const noexcept
{
  return raw_ == nullptr ? 0 : 1;
}

int CAviDecompressor::fps() const noexcept
{
  return raw_ == nullptr ? 0 : 1;
}

bool CAviDecompressor::is_playing() const noexcept
{
  return raw_ != nullptr;
}

bool CAviDecompressor::initialized() const noexcept
{
  return raw_ != nullptr;
}

int CAviDecompressor::palette() const noexcept
{
  return 0;
}

int CAviDecompressor::header() const noexcept
{
  return 0;
}

int CAviDecompressor::pixel_size() const noexcept
{
  return 0;
}

int CAviDecompressor::bpp() const noexcept
{
  return 0;
}

int CAviDecompressor::width() const noexcept
{
  return 0;
}

int CAviDecompressor::height() const noexcept
{
  return 0;
}

int CAviDecompressor::decoded_frame() const noexcept
{
  return 0;
}

unsigned int CAviDecompressor::time_ms() const noexcept
{
  return 0U;
}

int CAviDecompressor::sum_sleep_time() const noexcept
{
  return 0;
}

void CAviDecompressor::start() noexcept {}

void CAviDecompressor::stop() noexcept {}

void CAviDecompressor::done() noexcept {}

void CAviDecompressor::wait_for_next_frame() noexcept {}

void CAviDecompressor::init_clip_rect(const Rect &) noexcept {}

void CAviDecompressor::update_pos(long, int, long) noexcept {}

void CAviDecompressor::update_rect(const Rect &) noexcept {}

void CAviDecompressor::blit() noexcept {}

void CAviDecompressor::blit_to(long, int, long) noexcept {}

void CAviDecompressor::stretch_to(const Rect &) noexcept {}

void CAviDecompressor::get_rect(Rect &rect) const noexcept
{
  rect.left = 0;
  rect.top = 0;
  rect.right = 0;
  rect.bottom = 0;
}

void CAviDecompressor::init_color_keys(int, int) noexcept {}

void CAviDecompressor::init_pos(int, int) noexcept {}

void CAviDecompressor::init_rect(const Rect &) noexcept {}

void CAviDecompressor::init_overlays(char) noexcept {}

void CAviDecompressor::set_background(void *, const Rect &, int) noexcept {}

} // namespace cpp
} // namespace clash95
