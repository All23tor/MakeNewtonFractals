#include "Color.hpp"
#include <fstream>

class BMP {
  std::ofstream fout;
  const std::int32_t pixel_width;
  const std::int32_t pixel_height;

public:
  BMP(const std::string& name, std::int32_t width, std::int32_t height);
  void writeColor(Color);
};
