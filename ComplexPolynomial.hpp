#include <vector>
#include <string>
#include <complex>

class ComplexPolynomial{ //Class used to manage polynomials with complex coefficients

  std::vector<std::complex<double>> coefficients; //Here the polynomial coefficients are stored
  int degree; //The degree of the polynomial

  void simplify(){ //Used to remove all zero terms at the end of the polynomials representation
    if (coefficients[degree]==std::complex<double>(0,0)){
        coefficients.pop_back();
        degree--;
        simplify();
    }
  }

  std::vector<std::complex<double>> durandkernerStep(std::vector<std::complex<double>> roots){ //This is an algorithm to find all of the roots of the polynomial at once, surely this isn't optimized at all
    std::vector<std::complex<double>> newroots(degree);
    for (int index=0;index<degree;index++){ //All of the roots must be calculated at once, i think
      std::complex<double> currentvalue = roots[index];
      std::complex<double> newvalue = 1;
      for (int i=0;i<index;i++){
        newvalue *= currentvalue - roots[i];
      }
      for (int i=index+1;i<degree;i++){
        newvalue *= currentvalue - roots[i];
      }
      newroots[index]= currentvalue - (evaluate(currentvalue) / newvalue);
    }
    return newroots;
  }

  public:
  
  ComplexPolynomial(){ //Default constructor makes the 0 constant polynomial, not really used
    coefficients = std::vector<std::complex<double>>(1,0);
    degree=0;
  }
  
  ComplexPolynomial(std::vector<std::complex<double>> poly){ //Useful constructor
    coefficients = poly;
    degree= poly.size()-1;
  }

  void normalize(){ //Normalizes the polynomial so the leading coefficient is 1
    simplify();
    for (int i=0;i<degree;i++){
        coefficients[i]/=coefficients[degree];
    }
    coefficients[degree]=1;
  }
  
  std::string to_String(){ //Returns the conventional way in maths to write a polynomial 
    std::stringstream text; //I tried to make this look good, don't think success was achieved
    text<<coefficients[0]<<" + ";
    for (int i=1;i<degree;i++){
      text<<coefficients[i]<<"x^"<<i<<" + ";
    }
    return text.str();
  }
  
  std::complex<double> evaluate(std::complex<double> z){//Evaluates the polynomial at a complex number z
    std::complex<double> ans = 0;
    for (int i=degree;i>=0;i--){
      ans *= z;
      ans += coefficients[i];
    }
    return ans;
  }
  
  ComplexPolynomial derivative(){ //The derivative of a polynomial
    std::vector<std::complex<double>> newrule(degree);
    for (int i=0;i<degree;i++){
      newrule[i]=coefficients[i+1]*(i+1.0);
    }
    return ComplexPolynomial(newrule);
  }
  
  std::vector<std::complex<double>> findroots(){ //This just runs the previous algorithm a bunch of times so it's accurate
    std::complex<double> r_0 = std::complex<double>(0.4,0.9); //Initial value for roots, chosen arbitrairly
    std::vector<std::complex<double>> roots(degree);
    for (int i=0;i<degree;i++){
      roots[i]=std::pow(r_0,i);
    }
    for (int i=0;i<20;i++){ //Magic number 20 chosen because it seemed to be enough, not sure
      roots = durandkernerStep(roots);
    }
    return roots;
  }
};