#include "Color.hpp"
#include <cmath>

Color::Color(unsigned char r, unsigned char g, unsigned char b) :
    R(r),
    G(g),
    B(b) {}

Color::Color(double hue) {
  unsigned char x = 255 * (1 - std::abs(std::fmod(hue / 60, 2) - 1));
  int sector = (int(hue) / 60);
  switch (sector / 2) {
  case 0:
    R = sector % 2 ? x : 255;
    G = sector % 2 ? 255 : x;
    B = 0;
    break;

  case 1:
    R = 0;
    G = sector % 2 ? x : 255;
    B = sector % 2 ? 255 : x;
    break;

  case 2:
    R = sector % 2 ? 255 : x;
    G = 0;
    B = sector % 2 ? x : 255;
    break;
  }
}

Color Color::scale(double value) const {
  return Color(R * value, G * value, B * value);
}
