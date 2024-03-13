#include <fstream>
#include <iostream>
#include <cmath>
#include "Polynomial.hpp"
#include "Color.hpp"

const int pixel_width = 1600;
const int pixel_height = 900;
const double aspect_ratio = ((double)pixel_height)/pixel_width; //Aspect ratio of output image
const double xr = 5.0; //Range of values for the x-axis
const double yr = aspect_ratio * xr; //Calculates range of values for y-axis
const double eccentricity = 0.3; //Measures how quickly colors turn to black

const int maxIteration = 200; //Maximum number of Newton iterations per number
const float invmaxItEx = 1.0/(maxIteration*eccentricity);
const double tolerance = 1.0E-6; //Minimum proximity to a root necessary for it to be assigned 

class NewtonFractal{ //Builds a Newton Fractal pixel by pixel given a polynomial;

    ComplexPolynomial polynomial; 
    ComplexPolynomial derivative;
    std::vector<std::complex<double>> roots; //Here we will store the possibly complex roots of the polynomial
    int number_of_roots;
    std::vector<Color> colors;

    std::vector<double> xs, ys; //We will calculate the numerical coordinates that each pixel represents ahead of time

    std::vector<Color> pixels; //Here we store the color in each pixel

    double map(double value, double input_start, double input_end, double output_start, double output_end){ //Simple mapping function
        double input_range = input_end - input_start;
        double output_range = output_end - output_start;
        return (value-input_start)*(output_range/input_range)+output_start;
    }

    std::shared_ptr<unsigned char[]> printableColor(double x, double y){ //This checks which root each point is closest to
        std::complex<double> z(x,y);

        for (int it=0;it<maxIteration;it++){
            z -= polynomial.evaluate(z)/derivative.evaluate(z);
            for (int k=0;k<number_of_roots;k++){ //This is reaaaaally slow
                if (norm(z - roots[k])<tolerance){
                    return colors[k].scale((1.0+invmaxItEx)/(it*eccentricity+1)-invmaxItEx).toChars();
                }   
            }
        }

        return Color().toChars();
    }
    
    std::vector<Color> evenlyspacedColors(int n){ //Picks n colors that are evenly spaced by hue
        std::vector<Color> resulting_colors;
        int space = 1530/n; //My hue space goes from 0 to 1529 because I'm pretty sure my implementation is awful
        for (int i=0;i<1530;i+=space){
            resulting_colors.push_back(Color(i)); //Still works though
        }
        return resulting_colors;
    }

    char * toChars(int number){ //Used for creating .bmp file
        std::shared_ptr<char[]> ans(new char[4]);
        int count=0;
        while(number>0){
            ans[count]=number%256;
            number/=256;
            count++;
        }
        while(count<4){
            ans[count]=0;
            count++;
        }
        return ans.get();
    }

    char * toChars(short number){ //Used for creating .bmp file
        std::shared_ptr<char[]> ans(new char[2]);
        int count=0;
        while(number>0){
            ans[count]=number%256;
            number/=256;
            count++;
        }
        while(count<4){
            ans[count]=0;
            count++;
        }
        return ans.get();
    }

    public:

    std::string to_String(){
        return polynomial.to_String();
    }

    NewtonFractal(std::vector<std::complex<double>> _coefficients){ //Initializes everything
        polynomial = ComplexPolynomial(_coefficients); //Sets polynomial
        polynomial.normalize(); 
        derivative = polynomial.derivative(); //Stores the derivative
        roots = polynomial.findroots(); //Finds roots
        std::cout<<"Roots: ";
        for (std::complex<double> root : roots){
            std::cout<<root<<' ';
        }
        std::cout<<'\n';
        number_of_roots = roots.size();
        char isManual;
        std::cout<<"Insert colors manually? (Y/N): ";
        std::cin>>isManual; //If we want to
        if (isManual=='Y'){
            colors = std::vector<Color>(number_of_roots);
            std::cout<<"Input colors: ";
            for (Color& color: colors){
                std::string hexColor;
                unsigned char r,g,b;
                std::cin >> hexColor;
                sscanf(hexColor.c_str(), "%02hhx%02hhx%02hhx", &r, &g, &b);
                color = Color(r,g,b);
            }
        }else{
            colors = evenlyspacedColors(number_of_roots); //Makes colors according to the number of roots
        }
        for(int i=0;i<pixel_width;i++){ //This translates pixels to x-axis
            xs.push_back(map(i,0,pixel_width,-xr,xr));
        }
        for(int j=0;j<pixel_height;j++){ //This translates pixels to y-axis
            ys.push_back(map(j,0,pixel_height,yr,-yr));
        }
        std::cout<<"Assignation done!"<<'\n';
        pixels = std::vector<Color>(0);
    }

    void makeBMP(std::string filename){ //Store image in a file
        std::ofstream fout(filename + ".bmp", std::ofstream::binary);

        const int sizeofDIB = 40; //Size of the DIB header we use             
        const int sizeofheader = 14 + sizeofDIB; //Add the 14 mandatory bytes from BMP header
        const int sizeofbitmap = 4*pixel_width*pixel_height + sizeofheader; //3 bytes per pixel

        const int horizontalresolution = 4724;
        const int verticalresolution = 4724;

        const char* fourzeroes = "\0\0\0\0";
        const char* twozeroes = "\0\0";

        //BMP header

        fout.write("BM",2); //We always start with BM
        fout.write(toChars(sizeofbitmap),4); //Specify the size of the bitmap
        fout.write(twozeroes,2); //Always two zeroes
        fout.write(twozeroes,2); //Always two zeroes
        fout.write(toChars(sizeofheader),4); //Specify size of header

        //DIB header

        fout.write(toChars(sizeofDIB),4); //Size of this DIB format
        fout.write(toChars(pixel_width),4);
        fout.write(toChars(pixel_height),4);

        fout.write("\1\0",2); //Number of color planes (Always one)
        fout.write(std::string{32,0}.data(),2); //Bits per pixel, we use RGBA so 4 bytes per pixel

        fout.write(fourzeroes,4); //No compression used
        fout.write(fourzeroes,4); //We don't specify the imge size cause we don't use compression
        fout.write(toChars(horizontalresolution),4);
        fout.write(toChars(verticalresolution),4);
        fout.write(fourzeroes,4); //I dont know what this does tbh
        fout.write(fourzeroes,4); //Nor do I know what this does

        pixels.clear();
        for (int j=0;j<pixel_height;j++){
            double zy = ys[j];
            for (int i=0;i<pixel_width;i++){
                double zx = xs[i];
                fout.write(reinterpret_cast<char *>(printableColor(zx,zy).get()),4);
            }
        }
        std::cout<<"Pixels done!"<<'\n';

        fout.close();
    }
};
