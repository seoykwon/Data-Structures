// File:        testblock.cpp
// Date:        2022-09-18 23:52
// Description: Catch test cases for Block class

#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

#include <iostream>
#include <algorithm>

#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "block.h"

using namespace cs221util;
using namespace std;

TEST_CASE("Block::build-dimensions full PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  RGBAPixel* p = img.getPixel(0, 0);
    p->r = 0; p->g = 0; p->b = 0;
  p = img.getPixel(1, 0);
    p->r = 127; p->g = 0; p->b = 0;
  p = img.getPixel(0, 1);
    p->r = 0; p->g = 127; p->b = 0;
  p = img.getPixel(1, 1);
    p->r = 0; p->g = 0; p->b = 127;
  
  Block b;
  b.build(img, 0,0,2, 2);

  REQUIRE(b.width() == 2);
  REQUIRE(b.height() == 2);
}

TEST_CASE("Block::build-dimensions partial PNG", "[weight=1][part=block]") {

  PNG img(4, 4);

  RGBAPixel* p;
  for (unsigned int y = 0; y < img.height(); y++)
  {
    for (unsigned int x = 0; x < img.width(); x++)
    {
      p = img.getPixel(x, y);
        p->r = 60 * max(x,y); p->g = 60*x; p->b = 60 * y;
    }
  }

  Block b;
  b.build(img, 1,0,3, 4);

  REQUIRE(b.width() == 3);
  REQUIRE(b.height() == 4);
}

TEST_CASE("Block::build-render full PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  RGBAPixel* p = img.getPixel(0, 0);
    p->r = 0; p->g = 0; p->b = 0;
  p = img.getPixel(1, 0);
    p->r = 127; p->g = 0; p->b = 0;
  p = img.getPixel(0, 1);
    p->r = 0; p->g = 127; p->b = 0;
  p = img.getPixel(1, 1);
    p->r = 0; p->g = 0; p->b = 127;

  Block b;
  b.build(img, 0,0,2, 2);

  PNG outimg(2, 2);
  b.render(outimg, 0,0);

  RGBAPixel* p0 = outimg.getPixel(0, 0);
  RGBAPixel* p1 = outimg.getPixel(1, 0);
  RGBAPixel* p2 = outimg.getPixel(0, 1);
  RGBAPixel* p3 = outimg.getPixel(1, 1);

  REQUIRE(b.width() == 2);
  REQUIRE(b.height() == 2);

  RGBAPixel* p0e = img.getPixel(0, 0);
  RGBAPixel* p1e = img.getPixel(1, 0);
  RGBAPixel* p2e = img.getPixel(0, 1);
  RGBAPixel* p3e = img.getPixel(1, 1);
  REQUIRE(*p0 == *p0e);
  REQUIRE(*p1 == *p1e);
  REQUIRE(*p2 == *p2e);
  REQUIRE(*p3 == *p3e);
}

TEST_CASE("Block::build-render partial PNG", "[weight=1][part=block]") {

  PNG img(4, 4);

  RGBAPixel* p;
  for (unsigned int y = 0; y < img.height(); y++)
  {
    for (unsigned int x = 0; x < img.width(); x++)
    {
      p = img.getPixel(x, y);
        p->r = 60 * max(x,y); p->g = 60*x; p->b = 60 * y;
    }
  }

  Block b;
  b.build(img, 2,2,2, 2);

  PNG outimg(4, 4);
  b.render(outimg, 2,2);

  REQUIRE(b.width() == 2);
  REQUIRE(b.height() == 2);

  for (unsigned int y = 0; y < img.height(); y++)
  {
    for (unsigned int x = 0; x < 2; x++)
    {
        p = outimg.getPixel(x, y);
        REQUIRE(p->r == 0);
        REQUIRE(p->g == 0);
        REQUIRE(p->b == 0);
    }
  }
  for (unsigned int x = 0; x < img.width(); x++)
  {
    for (unsigned int y = 0; y < 2; y++)
    {
        p = outimg.getPixel(x, y);
        REQUIRE(p->r == 0);
        REQUIRE(p->g == 0);
        REQUIRE(p->b == 0);
    }
  }

  RGBAPixel* p0 = outimg.getPixel(2, 2);
  RGBAPixel* p1 = outimg.getPixel(3, 2);
  RGBAPixel* p2 = outimg.getPixel(2, 3);
  RGBAPixel* p3 = outimg.getPixel(3, 3);

  RGBAPixel* p0e = img.getPixel(2, 2);
  RGBAPixel* p1e = img.getPixel(3, 2);
  RGBAPixel* p2e = img.getPixel(2, 3);
  RGBAPixel* p3e = img.getPixel(3, 3);

  /**
  * Here we're just comparing the out pixels
  * to the expected ("e") versions of the pixel
  * from the initial image.
  */
  REQUIRE(*p0 == *p0e);
  REQUIRE(*p1 == *p1e);
  REQUIRE(*p2 == *p2e);
  REQUIRE(*p3 == *p3e);

}

TEST_CASE("Block::build-flip vert full PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  RGBAPixel* p = img.getPixel(0, 0);
    p->r = 0; p->g = 0; p->b = 0;
  p = img.getPixel(1, 0);
    p->r = 127; p->g = 0; p->b = 0;
  p = img.getPixel(0, 1);
    p->r = 0; p->g = 127; p->b = 0;
  p = img.getPixel(1, 1);
    p->r = 0; p->g = 0; p->b = 127;

  Block b;
  b.build(img, 0,0,2, 2);
  b.flipVert();

  PNG outimg(2, 2);
  b.render(outimg, 0,0);

  REQUIRE(*(outimg.getPixel(0,0)) == *(img.getPixel(0,1)));
  REQUIRE(*(outimg.getPixel(0,1)) == *(img.getPixel(0,0)));
  REQUIRE(*(outimg.getPixel(1,0)) == *(img.getPixel(1,1)));
  REQUIRE(*(outimg.getPixel(1,1)) == *(img.getPixel(1,0)));

}
TEST_CASE("Block::build-flip vert part PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  RGBAPixel* p = img.getPixel(0, 0);
    p->r = 0; p->g = 0; p->b = 0;
  p = img.getPixel(1, 0);
    p->r = 127; p->g = 0; p->b = 0;
  p = img.getPixel(0, 1);
    p->r = 0; p->g = 127; p->b = 0;
  p = img.getPixel(1, 1);
    p->r = 0; p->g = 0; p->b = 127;

  Block b;
  b.build(img, 1,0,1, 2);
  b.flipVert();

  PNG outimg(1, 2);
  b.render(outimg, 0,0);

  REQUIRE(*(outimg.getPixel(0,0)) == *(img.getPixel(1,1)));
  REQUIRE(*(outimg.getPixel(0,1)) == *(img.getPixel(1,0)));

}

TEST_CASE("Block::build-flip vert odd PNG", "[weight=1][part=block]") {

  PNG img(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      RGBAPixel *p = img.getPixel(i,j);
        p->r = 60 * max(i,j); p->g = 60*i; p->b = 60 * j;
    }
  }

  Block b;
  b.build(img, 1,0,1, 3);
  b.flipVert();

  PNG outimg(1, 3);
  b.render(outimg, 0,0);

  REQUIRE(*(outimg.getPixel(0,0)) == *(img.getPixel(1,2)));
  REQUIRE(*(outimg.getPixel(0,1)) == *(img.getPixel(1,1)));
  REQUIRE(*(outimg.getPixel(0,2)) == *(img.getPixel(1,0)));

}
// -------------------- new

TEST_CASE("Block::build-flip horiz full PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  RGBAPixel* p = img.getPixel(0, 0);
    p->r = 0; p->g = 0; p->b = 0;
  p = img.getPixel(1, 0);
    p->r = 127; p->g = 0; p->b = 0;
  p = img.getPixel(0, 1);
    p->r = 0; p->g = 127; p->b = 0;
  p = img.getPixel(1, 1);
    p->r = 0; p->g = 0; p->b = 127;

  Block b;
  b.build(img, 0,0,2, 2);
  b.flipHoriz();

  PNG outimg(2, 2);
  b.render(outimg, 0,0);

  REQUIRE(*(outimg.getPixel(0,0)) == *(img.getPixel(1,0)));
  REQUIRE(*(outimg.getPixel(0,1)) == *(img.getPixel(1,1)));
  REQUIRE(*(outimg.getPixel(1,0)) == *(img.getPixel(0,0)));
  REQUIRE(*(outimg.getPixel(1,1)) == *(img.getPixel(0,1)));

}
TEST_CASE("Block::build-flip horiz part PNG", "[weight=1][part=block]") {

  PNG img(2, 2);

  RGBAPixel* p = img.getPixel(0, 0);
    p->r = 0; p->g = 0; p->b = 0;
  p = img.getPixel(1, 0);
    p->r = 127; p->g = 0; p->b = 0;
  p = img.getPixel(0, 1);
    p->r = 0; p->g = 127; p->b = 0;
  p = img.getPixel(1, 1);
    p->r = 0; p->g = 0; p->b = 127;

  Block b;
  b.build(img, 0,1,2, 1);
  b.flipHoriz();

  PNG outimg(2, 1);
  b.render(outimg, 0,0);

  REQUIRE(*(outimg.getPixel(0,0)) == *(img.getPixel(1,1)));
  REQUIRE(*(outimg.getPixel(1,0)) == *(img.getPixel(0,1)));

}

TEST_CASE("Block::build-flip horiz odd PNG", "[weight=1][part=block]") {

  PNG img(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      RGBAPixel *p = img.getPixel(i,j);
        p->r = 60 * max(i,j); p->g = 60*i; p->b = 60 * j;
    }
  }

  Block b;
  b.build(img, 0,1,3, 1);
  b.flipHoriz();

  PNG outimg(3, 1);
  b.render(outimg, 0,0);

  REQUIRE(*(outimg.getPixel(0,0)) == *(img.getPixel(2,1)));
  REQUIRE(*(outimg.getPixel(1,0)) == *(img.getPixel(1,1)));
  REQUIRE(*(outimg.getPixel(2,0)) == *(img.getPixel(0,1)));

}

TEST_CASE("Block::build-rotate right odd PNG", "[weight=1][part=block]") {

  PNG img(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      RGBAPixel *p = img.getPixel(i,j);
        p->r = 60 * max(i,j); p->g = 60*j; p->b = 60 * i;
    }
  }

  Block b;
  b.build(img, 0,0,3, 3);
  b.rotateRight();

  PNG outimg(3, 3);
  b.render(outimg, 0,0);


  REQUIRE(*(outimg.getPixel(0,0)) == *(img.getPixel(0,2)));
  REQUIRE(*(outimg.getPixel(1,0)) == *(img.getPixel(0,1)));
  REQUIRE(*(outimg.getPixel(2,0)) == *(img.getPixel(0,0)));
  REQUIRE(*(outimg.getPixel(0,1)) == *(img.getPixel(1,2)));
  REQUIRE(*(outimg.getPixel(1,1)) == *(img.getPixel(1,1)));
  REQUIRE(*(outimg.getPixel(2,1)) == *(img.getPixel(1,0)));
  REQUIRE(*(outimg.getPixel(0,2)) == *(img.getPixel(2,2)));
  REQUIRE(*(outimg.getPixel(1,2)) == *(img.getPixel(2,1)));
  REQUIRE(*(outimg.getPixel(2,2)) == *(img.getPixel(2,0)));

}
