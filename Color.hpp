#include <string>

struct Color{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Color(){ //defaults to black
        r=0;
        g=0;
        b=0;
    }

    Color(unsigned char _r, unsigned char _g, unsigned char _b){ //Initializes RGB
        r=_r;
        g=_g;
        b=_b;
    }

    Color(int hue){ //Pick by hue [0,1530[ because I'm too lazy to normalize it
        if (hue<256){
            r=255;
            g=hue;
            b=0;
            return;
        }
        if (hue<511){
            r=510-hue;
            g=255;
            b=0;
            return;
        }
        if (hue<766){;
            r=0;
            g=255;
            b=hue-510;
            return;
        }
        if (hue<1021){
            r=0;
            g=1020-hue;
            b=255;
            return;
        }
        if (hue<1276){
            r=hue-1020;
            g=0;
            b=255;
            return;
        }
        r=255;
        g=0;
        b=1530-hue; //Looks horrible though
    }

    Color scale(double value){ //Scales color by decimal value
        return Color(r*value,g*value,b*value);
    }

    char* toChars(){
        char* ans = new char[3];
        ans[0]=b;
        ans[1]=g;
        ans[2]=r;

        return ans;
    }
};