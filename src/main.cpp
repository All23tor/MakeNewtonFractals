#include "NewtonFractal.hpp"
#include <iostream>

int main() {
  std::cout << "Make a Newton Fractal!" << '\n'
            << "Enter the polynomials degree: ";
  int m;
  std::cin >> m;
  m++;

  std::cout << "Now enter each term's coefficients (from the constant to the "
               "leading): ";
  std::vector<std::complex<double>> polynomial_coefficients(m, 0);
  for (std::complex<double> &i : polynomial_coefficients) {
    std::cin >> i;
  }

  NewtonFractal N(polynomial_coefficients);
  std::cout << N.getPolynomialToString() << '\n';
  std::string name;
  std::cout << "Insert file name: ";
  std::cin >> name;
  N.makeBMP(name);
  return 0;
}
