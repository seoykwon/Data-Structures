#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H
//#include what do I include?

#pragma once

class RGBAPixel
{

public:
    //range [0, 255]
    int r;
    int g;
    int b;
    double a;
    
    RGBAPixel();
    RGBAPixel(int r, int g, int b);
    RGBAPixel(int r, int g, int b, double a);
    ~RGBAPixel();


private:

};

#endif