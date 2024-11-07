#include "BMP.hpp"
#include <cstdint>

BMP::BMP(const std::string& name, int width, int height)
  : fout(name, std::ios::binary), pixel_width(width), pixel_height(height) {

  static constexpr const char* signature = "BM";
  static constexpr u_int32_t size_of_header = 14;
  static constexpr u_int32_t size_of_dib = 40;
  static constexpr u_int32_t offset = size_of_dib + size_of_header;
  static constexpr u_int16_t bytes_per_pixel = 3;
  constexpr u_int16_t number_of_color_planes = 1;
  static constexpr u_int16_t bits_per_pixel = bytes_per_pixel * 8;
  static constexpr u_int32_t compression_method = 0;
  static constexpr int32_t horizontal_resolution = 2835;
  static constexpr int32_t vertical_resolution = 2835;
  static constexpr u_int32_t number_colors_in_palette = 0; //0 defaults to 2^n
  static constexpr u_int32_t number_important_colors = 0;
  static constexpr u_int16_t unused_bytes = 0;

  const u_int32_t size_data = bytes_per_pixel * width * height;
  const u_int32_t size_of_bmp = size_data + offset;
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
