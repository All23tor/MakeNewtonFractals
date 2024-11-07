#include "Color.hpp"
#include <cmath>

Color::Color() { // Defaults to black
  R = 0;
  G = 0;
  B = 0;
}

Color::Color(unsigned char r, unsigned char g,
             unsigned char b) { // Initializes RGB values (0-255)
  R = r;
  G = g;
  B = b;
}

Color::Color(double hue) { // Pick by hue [0, 360)
  unsigned char x = 255 * (1 - std::abs(std::fmod(hue / 60, 2) - 1));
  switch (int(hue) / 60) {
  case 0:
    R = 255;
    G = x;
    B = 0;
    break;

  case 1:
    R = x;
    G = 255;
    B = 0;
    break;

  case 2:
    R = 0;
    G = 255;
    B = x;
    break;

  case 3:
    R = 0;
    G = x;
    B = 255;
    break;

  case 4:
    R = x;
    G = 0;
    B = 255;
    break;

  case 5:
    R = 255;
    G = 0;
    B = x;
    break;

  default:
    R = 0;
    G = 0;
    B = 0;
    break;
  }
}

Color Color::scale(
    double value) { // Returns copy of color scaled by decimal value
  return Color(R * value, G * value, B * value);
}

unsigned int Color::toUInt() { // Returns the pointer that the RGBA stores
  unsigned int color = R + ((unsigned int)G << 8) + ((unsigned int)B << 16);
  return color;
}
