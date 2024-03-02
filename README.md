# Make Newton Fractals

![Screenshot 2024-03-01 202801](https://github.com/All23tor/MakeNewtonFractals/assets/158845088/e6f05c03-f742-46b5-84c5-8bd84f10e020)

Make a Newton Fractal by inputting the coefficients of a polynomial. All the possibly complex roots are found using the Durand-Kerner algorithm. 

## Header files

The main code uses three header files which define the behaviour of polynomials, colors and fractals.

### Polynomial.hpp

Polynomials are represented by a list of their coefficients starting with the constant coefficient and ending with the leading coefficient. 
The polynomial is evaluated using the Horner method and its roots are found using the Durand-Kerner algorithm, which by dufault uses 20 iterations.
Polynomials also support differentiation, which is done by aplying the power ruleto each term.

### Color.hpp

Colors are simply three bytes, one for red, one for green, and one for blue. Each byte is stored in an unsigned char.
Colors can also be picked by hue instead of RGB, though as it is the implementation is rather ugly.
Colors support being scaled by a real number, which just scales each of the three values accordingly.

### NewtonFractal.hpp

Newton Fractals are made by aplying Newtons Method at each point and calculating which root it is closest to, then coloring the corresponding pixel according to a color list.
By default the width and height of the resulting image is 1600x900, and the range of the real axis is form -5 to 5, the maximum amount of Newton iterations is 200, and the minimum ditance required for a point to be associated with a root is 10 <sup>-6</sup>.
The eccentricity defines how fast the colors descend into black as they take more iterations to reach a root. 
When the colors for each root are not inputted manually, the Newton Fractal takes as many colors evenly spaced by hue as are necesary.
The class generates a .bmp with a BITMAPINFOHEADER DIB header.

## Compile and Run

The main.cpp file when compiled makes a simple implementation of the above headers, that only allows for the colors to be inputted manually if desired, every other value is set to default, and the resulting image is stored in a folder called BMPs.

### Input

The first value it will ask for is the degree of the polynomial, then it will as for the list of the coefficients (real numebers).
This is enough information to calculate the roots of this polynomial. When the roots are found it will inform this on the console.
Then it asks you if you want to choose the colors manually, if so, one must enter as many colors as there are solutions to the polynomial.
Once colors are assignated it will inform this on the console.
Then the common mathematical representation of the polynomial is printed.
Finally it will ask the name of the .bmp file that it is going to generate.

![image](https://github.com/All23tor/MakeNewtonFractals/assets/158845088/383d7c6e-6cc7-408a-9270-052e3e262c95)

