#include "Polynomial.hpp"

std::size_t ComplexPolynomial::degree() const {
  return coefficients.size() - 1;
}

// Used to remove all zero terms at the end of the polynomials representation
void ComplexPolynomial::simplify() {
  if (coefficients[degree()] == std::complex<double>(0, 0)) {
    coefficients.pop_back();
    simplify();
  }
}

ComplexVector ComplexPolynomial::durandkernerStep(const ComplexVector &roots) const {
  ComplexVector newroots(degree());
  // All of the roots must be calculated at once, i think
  for (int index = 0; index < degree(); index++) { 
    std::complex<double> currentvalue = roots[index];
    std::complex<double> newvalue = 1;
    for (int i = 0; i < index; i++) {
      newvalue *= currentvalue - roots[i];
    }
    for (int i = index + 1; i < degree(); i++) {
      newvalue *= currentvalue - roots[i];
    }
    newroots[index] = currentvalue - (evaluate(currentvalue) / newvalue);
  }
  return newroots;
}

// Zero Polynomial
ComplexPolynomial::ComplexPolynomial() { 
  coefficients = ComplexVector(1, 0);
}

ComplexPolynomial::ComplexPolynomial(const ComplexVector &poly, bool shouldNormalize): coefficients(poly) {
  if (poly.size() == 0) {
    coefficients.push_back(0);
    return;  
  }
  if (shouldNormalize) this->normalize();
}

void ComplexPolynomial::normalize() {
  simplify();
  for (int i = 0; i < degree(); i++) {
    coefficients[i] /= coefficients[degree()];
  }
  coefficients[degree()] = 1;
}

std::string ComplexPolynomial::toString() const {
  std::stringstream text;
  for (int i = 0; i < degree(); i++) {
    text << coefficients[i] << "x^" << i << " + ";
  }
  text << coefficients[degree()] << "x^" << degree();
  return text.str();
}

std::complex<double> ComplexPolynomial::evaluate(const std::complex<double> &z) const {
  std::complex<double> ans = 0;
  for (int i = degree(); i >= 0; i--) { // Horner's method
    ans *= z;
    ans += coefficients[i];
  }
  return ans;
}

ComplexPolynomial ComplexPolynomial::derivative() const {
  ComplexVector newrule(degree());
  for (int i = 0; i < degree(); i++) {
    newrule[i] = coefficients[i + 1] * (i + 1.0); // Chain rule
  }
  return ComplexPolynomial(newrule);
}

ComplexVector ComplexPolynomial::findroots() const {
  std::complex<double> r_0 = std::complex<double>(0.4, 0.9);
  ComplexVector roots(degree());
  for (int i = 0; i < degree(); i++) {
    roots[i] = std::pow(r_0, i); // Make initial guess for each root different
                                 // (and not too close to each other)
  }
  for (int i = 0; i < 60; i++) { // Magic number 60 chosen because it seemed
                                 // to be enough, not sure
    roots = durandkernerStep(roots);
  }
  return roots;
}
