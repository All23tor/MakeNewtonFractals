#include "Polynomial.hpp"

std::size_t Polynomial::degree() const {
  return coefficients.size() - 1;
}

// Used to remove all zero terms at the end of the polynomials representation
void Polynomial::simplify() {
  if (coefficients[degree()] == 0.0) {
    coefficients.pop_back();
    simplify();
  }
}

// Zero Polynomial
Polynomial::Polynomial() {
  coefficients = ComplexVector(1, 0);
}

Polynomial::Polynomial(const ComplexVector& poly, bool shouldNormalize) :
  coefficients(poly) {
  if (poly.size() == 0) {
    coefficients.push_back(0);
    return;
  }
  if (shouldNormalize)
    this->normalize();
}

void Polynomial::normalize() {
  simplify();
  for (int i = 0; i < degree(); i++) {
    coefficients[i] /= coefficients[degree()];
  }
  coefficients[degree()] = 1;
}

std::string Polynomial::toString() const {
  std::stringstream text;
  for (int i = 0; i < degree(); i++) {
    text << coefficients[i] << "x^" << i << " + ";
  }
  text << coefficients[degree()] << "x^" << degree();
  return text.str();
}

Complex Polynomial::evaluate(const Complex& z) const {
  Complex ans = 0;
  for (int i = degree(); i >= 0; i--) { // Horner's method
    ans *= z;
    ans += coefficients[i];
  }
  return ans;
}

Polynomial Polynomial::derivative() const {
  ComplexVector newrule(degree());
  for (int i = 0; i < degree(); i++) {
    newrule[i] = coefficients[i + 1] * (i + 1.0); // Chain rule
  }
  return Polynomial(newrule);
}

static ComplexVector
durand_kerner(const Polynomial& p, const ComplexVector& r) {
  ComplexVector newroots(p.degree());
  // All of the roots must be calculated at once, i think
  for (int index = 0; index < p.degree(); index++) {
    Complex currentvalue = r[index];
    Complex newvalue = 1;

    for (int i = 0; i < index; i++)
      newvalue *= currentvalue - r[i];
    for (int i = index + 1; i < p.degree(); i++)
      newvalue *= currentvalue - r[i];

    newroots[index] = currentvalue - (p.evaluate(currentvalue) / newvalue);
  }
  return newroots;
}

ComplexVector Polynomial::findroots() const {
  Complex r_0(0.4, 0.9);
  ComplexVector roots(degree());
  for (int i = 0; i < degree(); i++) {
    roots[i] = std::pow(r_0, i); // Make initial guess for each root different
                                 // (and not too close to each other)
  }
  for (int i = 0; i < 60; i++) { // Magic number 60 chosen because it seemed
                                 // to be enough, not sure
    roots = durand_kerner(*this, roots);
  }
  return roots;
}
