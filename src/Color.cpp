#include "Color.hpp"
#include <cmath>
#include <utility>

Color Color::from_hue(double hue) {
  static constexpr unsigned char FULL = 255;
  //  Finds the intermediate color according to the function
  //  x(h) = 255 (1 - |1 * mod(h/60, 2) - 1|)
  //  The graph of x(h) kinda looks like this
  //
  //     h
  // 255 |     /\          /\          /\
  //     |    /  \        /  \        /  \
  //     |   /    \      /    \      /    \
  //     |  /      \    /      \    /      \
  //     | /        \  /        \  /        \
  //     |/          \/          \/          \
  //   0 |______________________________________ x
  //    0     60    120   180   240   300   360
  //
  // Then
  unsigned char x = 255 * (1 - std::abs(std::fmod(hue / 60, 2) - 1));
  // Divides the 360 degree hue circle in six sectors [0, 6);
  int sector = static_cast<int>(hue) / 60;
  // Divides the sectors in two groups 0: {0, 2, 4} and 1: {1, 3, 5};
  bool is_odd = sector % 2;
  // Divides the sector in three groups 0: {0, 1} , 1: {2, 3} , 2: {4, 5}
  switch (sector / 2) {
  case 0:
    return {is_odd ? x : FULL, is_odd ? FULL : x, 0};
  case 1:
    return {0, is_odd ? x : FULL, is_odd ? FULL : x};
  case 2:
    return {is_odd ? FULL : x, 0, is_odd ? x : FULL};
  }
  std::unreachable();
};

Color Color::scale(double value) const {
  return Color{static_cast<unsigned char>(R * value),
               static_cast<unsigned char>(G * value),
               static_cast<unsigned char>(B * value)};
}
