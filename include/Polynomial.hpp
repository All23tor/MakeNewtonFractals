#include <complex>
#include <vector>

typedef std::vector<std::complex<double>> Polynomial;
class ComplexPolynomial {

private:
  Polynomial coefficients;
  int degree;

private:
  void simplify();
  Polynomial durandkernerStep(Polynomial);

public:
  ComplexPolynomial();
  ComplexPolynomial(Polynomial);

  void normalize();
  std::string to_String();
  std::complex<double> evaluate(std::complex<double>);
  ComplexPolynomial derivative();
  Polynomial findroots();
};
