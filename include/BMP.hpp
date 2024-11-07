#include "Color.hpp"
#include <cstdio>

class BMP {
  static constexpr unsigned int size_of_header = 14;
  static constexpr unsigned int size_of_dib = 40;
  static constexpr unsigned int offset = size_of_dib + size_of_header;
  static constexpr unsigned int size_of_bmp = 70;

  static constexpr unsigned short bytes_per_pixel = 3;
  static constexpr unsigned short bits_per_pixel = bytes_per_pixel * 8;

  static constexpr unsigned int compression_method = 0;
  static constexpr signed int horizontal_resolution = 2835;
  static constexpr signed int vertical_resolution = 2835;
  FILE *fout;
  const signed int pixel_width, pixel_height;

public:
  BMP(const char *name, int width, int height);
  ~BMP();
  void writeColor(Color);
};
