#include "RGBAPixel.h"

int r = 0;
int g = 0;
int b = 0;
double a = 0.0;

RGBAPixel::RGBAPixel() //default constructor
{
    r = 255;
    g = 255;
    b = 255;
}

RGBAPixel::RGBAPixel(int r, int g, int b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

RGBAPixel::RGBAPixel(int r, int g, int b, double a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

RGBAPixel::~RGBAPixel() //destructor
{

}