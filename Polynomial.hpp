#include <vector>
#include <string>
#include <complex>

class Polynomial{ //Class used to manage polynomials with real coefficients

  std::vector<float> rule; //Here the polynomial coefficients are stored
  int degree; //The degree of the polynomial

  void simplify(){ //Used to remove all zero terms at the end of the polynomials representation
    if (rule[degree]==0){
        rule.pop_back();
        degree--;
        simplify();
    }
  }

  std::vector<std::complex<float>> durandkernerStep(std::vector<std::complex<float>> roots){ //This is an algorithm to find all of the roots of the polynomial at once, surely this isn't optimized at all
    std::vector<std::complex<float>> newroots(degree);
    for (int index=0;index<degree;index++){ //All of the roots must be calculated at once, i think
      std::complex<float> currentvalue = roots[index];
      std::complex<float> newvalue = 1;
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
  
  Polynomial(){ //Default constructor makes the 0 constant polynomial, not really used
    rule = std::vector<float>(1,0);
    degree=0;
  }
  
  Polynomial(std::vector<float> poly){ //Useful constructor
    rule = poly;
    degree= poly.size()-1;
  }

  void normalize(){ //Normalizes the polynomial so the leading coefficient is 1
    simplify();
    for (int i=0;i<degree;i++){
        rule[i]/=rule[degree];
    }
    rule[degree]=1;
  }
  
  std::string toString(){ //Returns the conventional way in maths to write a polynomial 
    std::string text = ""; //I tried to make this look good, don't think success was achieved
    text += std::to_string(rule[0]);
    for (int i=1;i<rule.size();i++){
      if(rule[i]>0){
        text+=" +";
        text+=std::to_string(rule[i]);
        text+="x^"+std::to_string(i);
      } else if (rule[i]<0) { //This sucks
        text+=std::to_string(rule[i]);
        text+="x^"+std::to_string(i);
      }
    }
    return text;
  }
  
  std::complex<float> evaluate(std::complex<float> z){//Evaluates the polynomial at a complex number z
    std::complex<float> ans = 0;
    for (int i=0;i<rule.size();i++){
      ans += std::pow<float,float>(z,i)*rule[i];
    }
    return ans;
  }
  
  Polynomial derivative(){ //The derivative of a polynomial
    std::vector<float> newrule(degree);
    for (int i=0;i<degree;i++){
      newrule[i]=rule[i+1]*(i+1);
    }
    return Polynomial(newrule);
  }
  
  std::vector<std::complex<float>> findroots(){ //This justruns the previous algorithm a bunch of times so it's accurate
    std::complex<float> r_0 = std::complex<float>(0.4,0.9); //Initial value for roots, chose arbitrairly
    std::vector<std::complex<float>> roots(degree);
    for (int i=0;i<degree;i++){
      roots[i]=std::pow(r_0,i);
    }
    for (int i=0;i<20;i++){ //Magic number 20 chosen because it seemed to be enough, not sure
      roots = durandkernerStep(roots);
    }
    std::cout<<"Roots done!"<<'\n';
    return roots;
  }
};