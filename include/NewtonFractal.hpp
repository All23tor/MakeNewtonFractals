#include "BMP.hpp"
#include "Polynomial.hpp"

// Builds a Newton Fractal pixel by pixel given a polynomial;
class NewtonFractal {
private:
  const ComplexPolynomial polynomial;
  const ComplexPolynomial derivative;
  const std::vector<std::complex<double>> roots;
  std::vector<Color> colors;

private:
  // Measures how quickly colors turn to black
  static constexpr double eccentricity = 0.3;
  static constexpr int maxNewtonIterations = 200;
  static constexpr float invmaxItEx =
      1.0 / (maxNewtonIterations * eccentricity);
  static constexpr double tolerance = 1.0E-6;

private:
  // This checks which root each point is closest to, then assigns it a color
  Color printableColor(double x, double y);

public:
  NewtonFractal(const std::vector<std::complex<double>>& _coefficients);
  void makeBMP(const std::string& filename, int pixel_width = 1600,
               int pixel_height = 900, double x_range = 5.0);
  const ComplexPolynomial& getPolynomial() {
    return polynomial;
  }
  const ComplexVector& getRoots() {
    return roots;
  }
  const std::vector<Color>& getColors() {
    return colors;
  }
  void setColors(const std::vector<Color>&);
};

std::vector<Color> evenlyspacedColors(int n);
