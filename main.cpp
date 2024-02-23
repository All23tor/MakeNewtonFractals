#include <iostream>
#include "NewtonFractal.hpp"

int main(){
    std::cout<<"Make a Newton Fractal!"<<'\n'<<"Enter the polynomials degree: ";
    int m; std::cin>>m; m++;
    std::cout<<"Now enter each term's coefficients (from the constant to the leading): ";
    std::vector<float> polynomial_coefficients(m,0);
    for (float& i: polynomial_coefficients){
        std::cin>>i;
    }
    NewtonFractal N(polynomial_coefficients);
    N.loadPixels();
    N.makeBMP("Fractal");
    system("Fractal.bmp");
    return 0;
}