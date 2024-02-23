#include <fstream>
#include <iostream>
#include "Polynomial.hpp"
#include "Color.hpp"

const int pixel_width = 1600;
const int pixel_height = 900;
const float aspect_ratio = ((float)pixel_height)/pixel_width; //Aspect ratio of output image
const float xr = 5.0; //Range of values for the x-axis
const float yr = aspect_ratio * xr; //Calculates range of values for y-axis


const int maxIteration = 120; //Maximum number of Newton iterations per number
const float tolerance = 0.001; //Minimum proximity to a root necessary for it to be assigned 

class NewtonFractal{ //Builds a Newton Fractal pixel by pixel given a polynomial;

    Polynomial polynomial; 
    Polynomial derivative;
    std::vector<std::complex<float>> roots; //Here we will store the possibly complex roots of the polynomial
    int number_of_roots;
    std::vector<Color> colors;

    std::vector<float> xs, ys; //We will calculate the numerical coordinates that each pixel represents ahead of time

    std::vector<Color> pixels; //Here we store the color in each pixel

    float map(float value, float input_start, float input_end, float output_start, float output_end){ //Simple mapping function
        float input_range = input_end - input_start;
        float output_range = output_end - output_start;
        return (value-input_start)*(output_range/input_range)+output_start;
    }

    Color assignColor(float x, float y){ //This checks which root each point is closest to
        std::complex<float> z(x,y);

        for (int i=0;i<maxIteration;i++){
            z -= polynomial.evaluate(z)/derivative.evaluate(z);
            for (int i=0;i<number_of_roots;i++){ //This is reaaaaally slow
                if (std::norm((z - roots[i])) < tolerance){
                    return colors[i];
                }
            }
        }

        return Color();
    }
    
    std::vector<Color> evenlyspacedColors(int n){ //Picks n colors that are evenly spaced by hue
        std::vector<Color> resulting_colors;
        int space = 1530/n; //My hue space goes from 0 to 1529 because I'm pretty sure my implementation is awful
        for (int i=0;i<1530;i+=space){
            resulting_colors.push_back(Color(i));; //Still works though
        }
        return resulting_colors;
    }

    public:

    NewtonFractal(std::vector<float> _rule){ //Initializes everything
        polynomial = Polynomial(_rule);
        polynomial.normalize();
        derivative = polynomial.derivative();
        roots = polynomial.findroots();
        number_of_roots = roots.size();
        colors = evenlyspacedColors(number_of_roots);
        for(int i=0;i<pixel_width;i++){ //This translates pixels to x-axis
            xs.push_back(map(i,0,pixel_width,-xr,xr));
        }
        for(int j=0;j<pixel_height;j++){ //This translates pixels to y-axis
            ys.push_back(map(j,0,pixel_height,yr,-yr));
        }
        std::cout<<"Assignation done!"<<'\n';
        pixels = std::vector<Color>(0);
    }

    void loadPixels(){ //Go through each pixel
        for (int j=0;j<pixel_height;j++){
            float zy = ys[j];
            for (int i=0;i<pixel_width;i++){
                float zx = xs[i];
                pixels.push_back(assignColor(zx,zy));
            }
        }
        std::cout<<"Pixels done!"<<'\n';
    }

    void makeBMP(std::string filename){ //Store image in a file
        std::ofstream fout(filename + ".bmp");
        const unsigned char start[] = {66,77,54,235,65,0,0,0,0,0,54,0,0,0,40,0,0,0,64,6,0,0,132,3,0,0,1,0,24,0,0,0,0,0,0,235,65,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // I dont know how BMP works I just made one in Paint and copied it's initial data in here
        for (auto c: start){
            fout<<c;
        }
        for (auto i: pixels){
            fout<<i.b<<i.g<<i.r; // BGR instead of RGB because BMP wirtes things backwards I think
        }
        std::cout<<"Image done!"<<'\n';
    }
};