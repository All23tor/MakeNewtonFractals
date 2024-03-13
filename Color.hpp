#include <string>
#include <memory>

struct Color{
    std::shared_ptr<unsigned char[]> RGBA;

    Color(){ //defaults to black
        RGBA = std::shared_ptr<unsigned char[]>(new unsigned char[4]);
        RGBA[0]=0;
        RGBA[1]=0;
        RGBA[2]=0;
        RGBA[3]=0;
    }

    Color(unsigned char _r, unsigned char _g, unsigned char _b){ //Initializes RGB
        RGBA = std::shared_ptr<unsigned char[]>(new unsigned char[4]);
        RGBA[0]=_r;
        RGBA[1]=_g;
        RGBA[2]=_b;
        RGBA[3]=255;
    }

    Color(int hue){ //Pick by hue [0,1530[ because I'm too lazy to normalize it
        RGBA = std::shared_ptr<unsigned char[]>(new unsigned char[4]);
        RGBA[3]=255;
        if (hue<256){
            RGBA[0]=255;
            RGBA[1]=hue;
            RGBA[2]=0;
            return;
        }
        if (hue<511){
            RGBA[0]=510-hue;
            RGBA[1]=255;
            RGBA[2]=0;
            return;
        }
        if (hue<766){;
            RGBA[0]=0;
            RGBA[1]=255;
            RGBA[2]=hue-510;
            return;
        }
        if (hue<1021){
            RGBA[0]=0;
            RGBA[1]=1020-hue;
            RGBA[2]=255;
            return;
        }
        if (hue<1276){
            RGBA[0]=hue-1020;
            RGBA[1]=0;
            RGBA[2]=255;
            return;
        }

        RGBA[0]=255;
        RGBA[1]=0;
        RGBA[2]=1530-hue;
    }

    Color scale(double value){ //Scales color by decimal value
        return Color(RGBA[0]*value,RGBA[1]*value,RGBA[2]*value);
    }

    void setAlpha(unsigned char _a){
        RGBA[3] = _a;
    }

    std::shared_ptr<unsigned char[]> toChars(){
        return RGBA;
    }
};