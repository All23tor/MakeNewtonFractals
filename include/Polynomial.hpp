#include <complex>
#include <vector>

typedef std::vector<std::complex<double>> ComplexVector;

class ComplexPolynomial {
private:
  ComplexVector coefficients;
  int degree;

private:
  void simplify();
  ComplexVector durandkernerStep(ComplexVector);

public:
  ComplexPolynomial();
  ComplexPolynomial(ComplexVector, bool normalize = false);

  void normalize();
  std::string to_String();
  std::complex<double> evaluate(std::complex<double>);
  ComplexPolynomial derivative();
  ComplexVector findroots();
};
