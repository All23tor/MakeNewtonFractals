#include "BMP.hpp"
#include "Polynomial.hpp"

#include <iostream>

// Builds a Newton Fractal pixel by pixel given a polynomial;
class NewtonFractal {
private:
  ComplexPolynomial polynomial;
  ComplexPolynomial derivative;
  std::vector<std::complex<double>> roots;
  std::vector<Color> colors;

  const int pixel_width;
  const int pixel_height;

private:
  // Measures how quickly colors turn to black
  static constexpr double eccentricity = 0.3;
  static constexpr int maxNewtonIterations = 200;
  static constexpr float invmaxItEx = 1.0 / (maxNewtonIterations * eccentricity);
  static constexpr double tolerance = 1.0E-6;
  // We will calculate the numerical coordinates that each pixel represents ahead of time
  std::vector<double> xs, ys;

private:
  double map(double value, double input_start, double input_end, double output_start, double output_end) {
    double input_range = input_end - input_start;
    double output_range = output_end - output_start;
    return (value - input_start) * (output_range / input_range) + output_start;
  }

  // This checks which root each point is closest to, then assigns it a color
  Color printableColor(double x, double y);
  std::vector<Color> evenlyspacedColors(int n);

public:
  std::string getPolynomialToString() { return polynomial.to_String(); }
  NewtonFractal(std::vector<std::complex<double>> _coefficients, int width = 1600, int height = 900, double _xr = 5.0);
  void makeBMP(std::string filename);
};
