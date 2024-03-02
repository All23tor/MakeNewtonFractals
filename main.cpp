#include <iostream>
#include "ComplexNewtonFractal.hpp"

int main(){
    std::cout<<"Make a Newton Fractal!"<<'\n'<<"Enter the polynomials degree: ";
    int m; std::cin>>m; m++;

    std::cout<<"Now enter each term's coefficients (from the constant to the leading): ";
    std::vector<std::complex<double>> polynomial_coefficients(m,0);
    for (std::complex<double>& i: polynomial_coefficients){
        std::cin>>i;
    }

    NewtonFractal N(polynomial_coefficients);
    std::cout<<N.to_String()<<'\n';
    std::string name;
    std::cout<<"Insert file name: ";
    std::cin>> name;
    N.makeBMP("BMPs/" + name);
    return 0;
}