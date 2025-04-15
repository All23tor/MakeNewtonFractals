#include "BMP.hpp"
#include <array>
#include <bit>

template <typename T>
void BMP::writeBytes(T value) {
  if constexpr (std::endian::native == std::endian::big) {
    value = std::byteswap(value);
  }

  auto bytes = std::bit_cast<std::array<char, sizeof(T)>>(value);
  fout.write(bytes.data(), sizeof(T));
}

BMP::BMP(const std::string& name, std::int32_t width, std::int32_t height) :
    fout(name, std::ios::binary),
    pixel_width(width),
    pixel_height(height) {

  static constexpr const char* signature = "BM";
  static constexpr std::uint32_t size_of_header = 14;
  static constexpr std::uint32_t size_of_dib = 40;
  static constexpr std::uint32_t offset = size_of_dib + size_of_header;
  static constexpr std::uint16_t bytes_per_pixel = 3;
  static constexpr std::uint16_t number_of_color_planes = 1;
  static constexpr std::uint16_t bits_per_pixel = bytes_per_pixel * 8;
  static constexpr std::uint32_t compression_method = 0;
  static constexpr std::int32_t horizontal_resolution = 2835;
  static constexpr std::int32_t vertical_resolution = 2835;
  static constexpr std::uint32_t number_colors_in_palette = 0;
  static constexpr std::uint32_t number_important_colors = 0;
  static constexpr std::uint16_t unused_bytes = 0;

  const std::uint32_t size_data = bytes_per_pixel * width * height;
  const std::uint32_t size_of_bmp = size_data + offset;
  // Header

  fout.write(signature, 2);
  writeBytes(size_of_bmp);
  writeBytes(unused_bytes);
  writeBytes(unused_bytes);
  writeBytes(offset);

  // DIB header
  writeBytes(size_of_dib);
  writeBytes(width);
  writeBytes(height);
  writeBytes(number_of_color_planes);
  writeBytes(bits_per_pixel);
  writeBytes(compression_method);
  writeBytes(size_data);
  writeBytes(horizontal_resolution);
  writeBytes(vertical_resolution);
  writeBytes(number_colors_in_palette);
  writeBytes(number_important_colors);
}

void BMP::writeColor(Color x) {
  fout.put(x.R);
  fout.put(x.G);
  fout.put(x.B);
}
