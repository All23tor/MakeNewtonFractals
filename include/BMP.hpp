#include "Color.hpp"
#include <fstream>
#include <bit>
#include <array>

class BMP {
private:
  std::ofstream fout;
  const signed int pixel_width;
  const signed int pixel_height;

  template<typename T>
  void writeBytes(T value) {
    auto bytes = std::bit_cast<std::array<char, sizeof(T)>>(value);
    fout.write(bytes.data(), sizeof(T));
  }

public:
  BMP(const std::string& name, int width, int height);
  void writeColor(Color);
};
