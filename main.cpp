#include "NewtonFractal.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>

auto manual_colors(std::size_t n) {
  std::vector<Color> newColors(n);
  std::cout << "Input colors: ";
  for (Color& color : newColors) {
    std::string hexColor;
    unsigned char r, g, b;
    std::cin >> hexColor;
    // Read each color in hex format
    sscanf(hexColor.c_str(), "%02hhx%02hhx%02hhx", &r, &g, &b);
    color = Color{r, g, b};
  }
  return newColors;
}

auto sorted_colors(const NewtonFractal& nf) {
  const std::vector<Color>& colors = nf.getColors();
  std::vector<std::size_t> sortedIndices(colors.size());
  std::iota(sortedIndices.begin(), sortedIndices.end(), 0);
  std::sort(
    sortedIndices.begin(),
    sortedIndices.end(),
    [&roots = nf.getRoots()](std::size_t i, std::size_t j) {
      return std::arg(roots[i]) < std::arg(roots[j]);
    }
  );
  std::vector<Color> sortedColors(colors.size());
  for (std::size_t i = 0; i < sortedIndices.size(); ++i)
    sortedColors[sortedIndices[i]] = colors[i];
  return sortedColors;
}

int main() {
  std::cout << "Make a Newton Fractal!\nEnter the polynomials degree: ";
  unsigned int m;
  std::cin >> m;
  m++;

  std::cout << "Now enter each term's coefficients (highest degree last): ";
  ComplexVector polynomial_coefficients(m);
  for (Complex& i : polynomial_coefficients) {
    std::cin >> i;
  }

  NewtonFractal newtonFractal(polynomial_coefficients);

  std::cout << "Roots: ";
  for (Complex root : newtonFractal.getRoots()) {
    std::cout << root << ' ';
  }
  std::cout << '\n';

  std::cout << "Insert colors manually? (Y/N): ";
  char isManual;
  std::cin >> isManual;
  if (isManual == 'Y')
    newtonFractal.setColors(manual_colors(newtonFractal.getRoots().size()));
  else
    newtonFractal.setColors(sorted_colors(newtonFractal));

  std::cout << "Assignation done!" << '\n';
  std::cout << newtonFractal.getPolynomial() << '\n';

  std::cout << "Insert file name: ";
  std::string name;
  std::cin >> name;

  newtonFractal.makeBMP(name);
  std::cout << "Pixels done!" << '\n';
  return 0;
}
