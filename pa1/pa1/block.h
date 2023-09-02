
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
using namespace std;
using namespace cs221util;

class Block
{

public:
   /** 
    * Creates a block that is width x height pixels in size
    * starting at (x, y) on img. Assumes that the requested
    * block fits on the image. (inputs are feasible)
    */
   void build(PNG &img, int x, int y, int width, int height);

   /** 
    * Renders the given block onto img with its upper
    * left corner at (x, y). Assumes block fits on the 
    * image.
    */
   void render(PNG &img, int x, int y) const;

   /**
    * Rotates the block by 90 degrees clockwise, or
    * to the right. Assumes square blocks.
    */
   void rotateRight();

   /**
    * Turns the block upside down by a simple reflection
    * across the horizontal axis through its middle.
    */
   void flipVert();

   /**
    * Flips the block horizontally by a simple reflection
    * across the vertical axis through its middle.
    */
   void flipHoriz();

   // Return the width and height of the block.
   int width() const;
   int height() const;

private:
   vector<vector<RGBAPixel>> data;
};
#endif
