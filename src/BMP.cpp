#include "BMP.hpp"

BMP::BMP(const char *name, int width, int height)
    : pixel_width{width}, pixel_height{height} {
  fout = fopen(name, "wb");

  const unsigned int size_data = bytes_per_pixel * width * height;

  // Header

  std::fwrite("BM", sizeof(char), 2, fout);        // Signature
  std::fwrite(&size_of_bmp, sizeof(int), 1, fout); // Size of bitmap in bytes
  std::fwrite("\0\0\0\0", sizeof(short), 2, fout); // Unused bytes
  std::fwrite(&offset, sizeof(int), 1, fout);      // Size of bitmap in bytes

  // DIB header

  std::fwrite(&size_of_dib, sizeof(int), 1,
              fout);                          // Size of DIB header in bytes
  std::fwrite(&width, sizeof(int), 1, fout);  // Bitmap width (signed)
  std::fwrite(&height, sizeof(int), 1, fout); // Bitmap height (signed)
  std::fwrite("\1\0", sizeof(char), 2,
              fout); // Number of color planes (must be 1)
  std::fwrite(&bits_per_pixel, sizeof(short), 1,
              fout); // Number of bits per pixel
  std::fwrite(&compression_method, sizeof(int), 1,
              fout);                             // Compression method utilized
  std::fwrite(&size_data, sizeof(int), 1, fout); // Size of raw bitmap data
  std::fwrite(&horizontal_resolution, sizeof(int), 1,
              fout); // Pixel per meter horizontal resolution (signed)
  std::fwrite(&vertical_resolution, sizeof(int), 1,
              fout); // Pixel per meter vertical resolution (signed)
  std::fwrite("\0\0\0\0", sizeof(int), 1,
              fout); // Number of colors in color palette, 0 defaults to 2^n
  std::fwrite("\0\0\0\0", sizeof(int), 1,
              fout); // Number of important colors????
}

BMP::~BMP() { fclose(fout); }

void BMP::writeColor(Color x) {
  std::fwrite(&x.R, sizeof(char), 1, fout);
  std::fwrite(&x.G, sizeof(char), 1, fout);
  std::fwrite(&x.B, sizeof(char), 1, fout);
}
