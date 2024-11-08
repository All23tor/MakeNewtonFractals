#include "NewtonFractal.hpp"

Color NewtonFractal::printableColor(double x, double y) {
  std::complex<double> z(x, y);

  for (int it = 0; it < maxNewtonIterations; it++) {
    z -= polynomial.evaluate(z) / derivative.evaluate(z);
    for (int k = 0; k < roots.size(); k++) { // This is reaaaaally slow
      if (norm(z - roots[k]) < tolerance) {
        // Scale the color such that it fades to black appropiately
        return colors[k].scale((1.0 + invmaxItEx) / (it * eccentricity + 1) - invmaxItEx);
      }
    }
  }

  return Color();
}

std::vector<Color> NewtonFractal::evenlyspacedColors(int n) {
  std::vector<Color> resulting_colors;
  double base_hue = 360.0 / n;
  double hue = 0.0;
  for (int i = 0; i < n; ++i) {
    resulting_colors.push_back(Color(hue));
    hue += base_hue;
  }
  return resulting_colors;
}

NewtonFractal::NewtonFractal(std::vector<std::complex<double>> _coefficients, int width, int height, double xr) : 
  polynomial(_coefficients, true),
  derivative(polynomial.derivative()),
  roots(polynomial.findroots()),
  colors(evenlyspacedColors(roots.size())),
  pixel_height(height),
  pixel_width(width) 
{
  std::cout << "Roots: ";
  for (std::complex<double> root : roots) {
    std::cout << root << ' ';
  }
  std::cout << '\n';

  char isManual;
  std::cout << "Insert colors manually? (Y/N): ";
  std::cin >> isManual; // If we want to
  if (isManual == 'Y') {
    colors = std::vector<Color>(roots.size());
    std::cout << "Input colors: ";
    for (Color& color : colors) {
      std::string hexColor;
      unsigned char r, g, b;
      std::cin >> hexColor;
      // Read each color in hex format
      sscanf(hexColor.c_str(), "%02hhx%02hhx%02hhx", &r, &g, &b);
      color = Color(r, g, b);
    }
  }

  const double aspect_ratio = static_cast<double>(pixel_height) / pixel_width;
  const double yr = aspect_ratio * xr;

  // Pixels to xy plane translation
  for (int i = 0; i < pixel_width; i++) { 
    xs.push_back(map(i, 0, pixel_width, -xr, xr));
  }
  for (int j = 0; j < pixel_height; j++) {
    ys.push_back(map(j, 0, pixel_height, yr, -yr));
  }
  std::cout << "Assignation done!" << '\n';
}

void NewtonFractal::makeBMP(std::string filename) { // Store image in a file
  BMP bmp((filename + ".bmp").data(), pixel_width, pixel_height);

  for (double zy : ys) {
    for (double zx : xs) {
      bmp.writeColor(printableColor(zx, zy));
    }
  }

  std::cout << "Pixels done!" << '\n';
}