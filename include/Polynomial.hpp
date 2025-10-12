#include <complex>
#include <ostream>
#include <vector>

using Complex = std::complex<double>;
using ComplexVector = std::vector<Complex>;

class Polynomial {
  ComplexVector coefficients;

public:
  Polynomial();
  Polynomial(const ComplexVector&);
  std::size_t degree() const;
  Polynomial derivative() const;
  Polynomial normalized() const;
  Complex evaluate(const Complex&) const;
  ComplexVector findroots() const;
  friend std::ostream& operator<<(std::ostream&, const Polynomial&);
};
