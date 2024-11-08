#include "Color.hpp"
#include <cmath>

// Initializes RGB values (0-255)
Color::Color(unsigned char r, unsigned char g, unsigned char b) :
  R(r), G(g), B(b) {}

// Pick by hue [0, 360)
Color::Color(double hue) {
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
  }
}

// Returns copy of color scaled by decimal value
Color Color::scale(double value) {
  return Color(R * value, G * value, B * value);
}
