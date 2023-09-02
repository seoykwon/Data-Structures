/**
 * @file RGBAPixel.cpp
 * Implementation of the RGBAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1
 * 
 * Color difference functions adapted from pam.h (copyright notice below)
 * 
 * Copyright (C) 1989, 1991 by Jef Poskanzer.
 * Copyright (C) 1997 by Greg Roelofs.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  This software is provided "as is" without express or
 * implied warranty.
 */

#include "RGBAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs221util {
  RGBAPixel::RGBAPixel() {
    r = 0;
    g = 0;
    b = 0;
    a = 1.0;
  }

  RGBAPixel::RGBAPixel(int red, int green, int blue){
    r = red;
    g = green;
    b = blue;
    a = 1.0;
  }
  RGBAPixel::RGBAPixel(int red, int green, int blue, double alpha){
    r = red;
    g = green;
    b = blue;
    a = alpha;
  }

  double RGBAPixel::dist(const RGBAPixel& other) const {
    // original pam.h assumes RGB values range from 0 to 1.
    
    // also pre-multiply alpha
    double dbl_r_this = (double)this->r / 255.0 * this->a;
    double dbl_r_other = (double)other.r / 255.0 * other.a;
    double dbl_g_this = (double)this->g / 255.0 * this->a;
    double dbl_g_other = (double)other.g / 255.0 * other.a;
    double dbl_b_this = (double)this->b / 255.0 * this->a;
    double dbl_b_other = (double)other.b / 255.0 * other.a;

    double delta_a = this->a - other.a;

    // compute maximum of each channel blended on white, and blended on black
    // red channel
    double black = dbl_r_this - dbl_r_other;
    double white = black + delta_a;
    double diff_r = max(black * black, white * white);
    // green channel
    black = dbl_g_this - dbl_g_other;
    white = black + delta_a;
    double diff_g = max(black * black, white * white);
    // blue channel
    black = dbl_b_this - dbl_b_other;
    white = black + delta_a;
    double diff_b = max(black * black, white * white);
    
    return diff_r + diff_g + diff_b;
  }


  bool RGBAPixel::operator== (RGBAPixel const & other) const {
    // thank/blame Wade for the following function
    // adapted by cinda to allow for slight deviations in RGB

    if ( a == 0 ) { return true; }
    if (fabs(a - other.a) > 0.01) { return false; }

    if (fabs(r - other.r) > 2) { return false; } 
    if (fabs(g - other.g) > 2) { return false; } 
    if (fabs(b - other.b) > 2) { return false; } 

    return true;
}

  bool RGBAPixel::operator!= (RGBAPixel const & other) const {
    return !(*this == other);
  }

  bool RGBAPixel::operator<  (RGBAPixel const & other) const {
    // Cinda is not sure where this is used. Fairly arb total
    // order is reflected here. R->G->B.
      if (*this == other) { return false; }

      if (r < other.r)
          return true;
      else if ((r == other.r) && (g < other.g))
          return true;
      else if ((r == other.r) && (g == other.g) && (b < other.b))
          return true;

      return false;
  }

  std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel) {
    out << "(" << (int)pixel.r << ", " << (int)pixel.g << ", " << (int)pixel.b << (pixel.a != 1 ? ", " + std::to_string(pixel.a) : "") << ")";

    return out;
  }


}
