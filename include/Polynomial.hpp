#include <complex>
#include <ostream>
#include <vector>

using Complex = std::complex<double>;
using ComplexVector = std::vector<Complex>;

class Polynomial {
  ComplexVector coefficients;

public:
  Polynomial();
  Polynomial(const ComplexVector&, bool normalize = false);
  void normalize();
  std::size_t degree() const;
  Complex evaluate(const Complex&) const;
  Polynomial derivative() const;
  ComplexVector findroots() const;
  friend std::ostream& operator<<(std::ostream&, const Polynomial&);
};
