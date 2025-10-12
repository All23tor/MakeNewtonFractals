#include "NewtonFractal.hpp"

static constexpr int MAX_ITERATION = 200;
static constexpr double ECCENTRICITY = 3;

constexpr double scaling_factor(double x) {
  return (1 - x / MAX_ITERATION) / (1 + x / ECCENTRICITY);
}

Color NewtonFractal::printableColor(double x, double y) {
  Complex z(x, y);

  for (int it = 0; it < MAX_ITERATION; it++) {
    z -= polynomial.evaluate(z) / derivative.evaluate(z);
    static constexpr double tolerance = 1.0E-6;
    for (int k = 0; k < roots.size(); k++) // This is reaaaaally slow
      if (norm(z - roots[k]) < tolerance)
        return colors[k].scale(scaling_factor(it));
  }

  return Color{};
}

std::vector<Color> evenlyspacedColors(int n) {
  std::vector<Color> resulting_colors;
  double base_hue = 360.0 / n;
  double hue = 0.0;
  for (int i = 0; i < n; ++i) {
    resulting_colors.push_back(Color::from_hue(hue));
    hue += base_hue;
  }
  return resulting_colors;
}

NewtonFractal::NewtonFractal(const ComplexVector& _coefficients) :
  polynomial(_coefficients, true),
  derivative(polynomial.derivative()),
  roots(polynomial.findroots()),
  colors(evenlyspacedColors(roots.size())) {}

static constexpr double map(
  double value,
  double input_start,
  double input_end,
  double output_start,
  double output_end
) {
  double input_range = input_end - input_start;
  double output_range = output_end - output_start;
  return (value - input_start) * (output_range / input_range) + output_start;
}

void NewtonFractal::makeBMP(
  const std::string& filename,
  int pixel_width,
  int pixel_height,
  double x_range
) { // Store image in a file
  BMP bmp(filename + ".bmp", pixel_width, pixel_height);

  // We will calculate the numerical coordinates that each pixel represents
  // ahead of time
  std::vector<double> real_axis, imaginary_axis;
  const double aspect_ratio = static_cast<double>(pixel_height) / pixel_width;
  const double y_range = aspect_ratio * x_range;

  // Pixels to xy plane translation
  for (int i = 0; i < pixel_width; i++) {
    real_axis.push_back(map(i, 0, pixel_width, -x_range, x_range));
  }
  for (int j = 0; j < pixel_height; j++) {
    imaginary_axis.push_back(map(j, 0, pixel_height, y_range, -y_range));
  }

  for (double zy : imaginary_axis) {
    for (double zx : real_axis) {
      bmp.writeColor(printableColor(zx, zy));
    }
  }
}

void NewtonFractal::setColors(const std::vector<Color>& newColors) {
  const std::size_t numberOfColorsToAssign =
    std::min(newColors.size(), colors.size());
  for (int i = 0; i < numberOfColorsToAssign; ++i) {
    colors[i] = newColors[i];
  }

  for (int i = numberOfColorsToAssign; i < colors.size(); ++i) {
    colors[i] = Color();
  }
}

const Polynomial& NewtonFractal::getPolynomial() const {
  return polynomial;
}

const ComplexVector& NewtonFractal::getRoots() const {
  return roots;
}

const std::vector<Color>& NewtonFractal::getColors() const {
  return colors;
}
