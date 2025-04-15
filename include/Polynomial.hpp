#include <complex>
#include <vector>

typedef std::vector<std::complex<double>> ComplexVector;

class ComplexPolynomial {
public:
  ComplexVector coefficients;

public:
  ComplexPolynomial();
  ComplexPolynomial(const ComplexVector&, bool normalize = false);
  void simplify();
  void normalize();
  std::size_t degree() const;
  std::string toString() const;
  std::complex<double> evaluate(const std::complex<double>&) const;
  ComplexPolynomial derivative() const;
  ComplexVector findroots() const;

private:
  ComplexVector durandkernerStep(const ComplexVector&) const;
};
