#include "BMP.hpp"
#include "Polynomial.hpp"

class NewtonFractal { // Builds a Newton Fractal pixel by pixel given a
                      // polynomial;
private:
  ComplexPolynomial polynomial;
  ComplexPolynomial derivative;
  std::vector<std::complex<double>>
      roots; // Here we will store the possibly complex roots of the polynomial
  int number_of_roots;
  std::vector<Color> colors;

  const int pixel_width;
  const int pixel_height;

private:
  // Measures how quickly colors turn to black
  static constexpr double eccentricity = 0.3;
  // Maximum number of Newton iterations per number
  static constexpr int maxIteration = 200;
  static constexpr float invmaxItEx = 1.0 / (maxIteration * eccentricity);
  // Minimum proximity to a root necessary for it to be assigned
  static constexpr double tolerance = 1.0E-6;

  std::vector<double> xs, ys; // We will calculate the numerical coordinates
                              // that each pixel represents ahead of time
private:
  double map(double value, double input_start, double input_end,
             double output_start,
             double output_end) { // Simple mapping function
    double input_range = input_end - input_start;
    double output_range = output_end - output_start;
    return (value - input_start) * (output_range / input_range) + output_start;
  }

  Color printableColor(double x,
                       double y) { // This checks which root each point is
                                   // closest to, then assigns it a color
    std::complex<double> z(x, y);

    for (int it = 0; it < maxIteration; it++) {
      z -= polynomial.evaluate(z) / derivative.evaluate(z);
      for (int k = 0; k < number_of_roots; k++) { // This is reaaaaally slow
        if (norm(z - roots[k]) < tolerance) {
          return colors[k].scale((1.0 + invmaxItEx) / (it * eccentricity + 1) -
                                 invmaxItEx); // Scale the color such that it
                                              // fades to black appropiately
        }
      }
    }

    return Color(); // Black means that the point doesn't land near any root
  }

  std::vector<Color>
  evenlyspacedColors(int n) { // Picks n colors that are evenly spaced by hue
    std::vector<Color> resulting_colors;
    double base_hue = 360.0 / n; // Hue in range of [0,360)
    double hue = 0.0;
    for (int i = 0; i < n; ++i) {
      resulting_colors.push_back(Color(hue));
      hue += base_hue;
    }
    return resulting_colors;
  }

public:
  std::string to_String() { return polynomial.to_String(); }

  NewtonFractal(std::vector<std::complex<double>> _coefficients,
                int width = 1600, int height = 900, double _xr = 5.0)
      : pixel_height{height}, pixel_width{width} { // Initializes everything
    polynomial = ComplexPolynomial(_coefficients); // Sets polynomial
    polynomial.normalize();
    derivative = polynomial.derivative(); // Stores the derivative
    roots = polynomial.findroots();       // Finds roots
    std::cout << "Roots: ";
    for (std::complex<double> root : roots) {
      std::cout << root << ' ';
    }
    std::cout << '\n';
    number_of_roots = roots.size();

    char isManual;
    std::cout << "Insert colors manually? (Y/N): ";
    std::cin >> isManual; // If we want to
    if (isManual == 'Y') {
      colors = std::vector<Color>(number_of_roots);
      std::cout << "Input colors: ";
      for (Color &color : colors) {
        std::string hexColor;
        unsigned char r, g, b;
        std::cin >> hexColor;
        sscanf(hexColor.c_str(), "%02hhx%02hhx%02hhx", &r, &g,
               &b); // Read each color in hex format
        color = Color(r, g, b);
      }
    } else {
      colors = evenlyspacedColors(
          number_of_roots); // Makes colors according to the number of roots
    }

    const double aspect_ratio = ((double)pixel_height) / pixel_width;
    const double xr = _xr; // Range of values for the x-axis
    const double yr =
        aspect_ratio * xr; // Calculates range of values for y-axis

    for (int i = 0; i < pixel_width; i++) { // This translates pixels to x-axis
      xs.push_back(map(i, 0, pixel_width, -xr, xr));
    }
    for (int j = 0; j < pixel_height; j++) { // This translates pixels to y-axis
      ys.push_back(map(j, 0, pixel_height, yr, -yr));
    }
    std::cout << "Assignation done!" << '\n';
  }

  void makeBMP(std::string filename) { // Store image in a file
    BMP bmp((filename + ".bmp").data(), pixel_width, pixel_height);

    for (double zy : ys) {
      for (double zx : xs) {
        bmp.writeColor(printableColor(zx, zy));
      }
    }

    std::cout << "Pixels done!" << '\n';
  }
};
