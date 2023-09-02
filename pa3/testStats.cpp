
#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

#include "stats.h"
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
using namespace cs221util;
using namespace std;

/*
  TEST_CASE("Stats::1x1 area","[weight=1][part=stats]"){

  PNG im(1,1);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100; p->g = 150; p->b = 200;
  stats s(im);
  pair<int,int> ul(0,0);
  pair<int,int> lr(0,0);

  REQUIRE(s.rectArea(ul,lr)==1);
  }
*/

TEST_CASE("Stats::1x1 avg","[weight=1][part=stats]"){

  PNG im(1,1);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100; p->g = 150; p->b = 200;
  stats s(im);
  pair<int,int> ul(0,0);

  REQUIRE(s.getAvg(ul,1,1)==*p);
}

TEST_CASE("Stats::1x1 var","[weight=1][part=stats]"){

  PNG im(1,1);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100; p->g = 150; p->b = 200;
  stats s(im);
  pair<int,int> ul(0,0);

  REQUIRE(s.getVar(ul,1,1)==0);
}
// ======================

/*
  TEST_CASE("Stats::size 1x2,(0,0)(1,0) area","[weight=1][part=stats]"){

  PNG im(2,1);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(1,0);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(0,0);pair<int,int> lr(1,0);

  REQUIRE(s.rectArea(ul,lr)==2);
  }
*/
TEST_CASE("Stats::size 1x2,(0,0)(1,0) avg","[weight=1][part=stats]"){

  PNG im(2,1);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(1,0);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(0,0);

  RGBAPixel avg((p->r + q->r)/2,(p->g + q->g)/2,(p->b + q->b)/2);
  REQUIRE(s.getAvg(ul,2,1)==avg);
}

TEST_CASE("Stats::size 1x2,(0,0)(1,0) var","[weight=1][part=stats]"){

  PNG im(2,1);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(1,0);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(0,0);

  REQUIRE(9063 - s.getVar(ul,2,1) <= 3);
  REQUIRE(9063 - s.getVar(ul,2,1) >= 0);
}
// ======================

/*
  TEST_CASE("Stats::size 1x2,(1,0)(1,0) area","[weight=1][part=stats]"){

  PNG im(2,1);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(1,0);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(1,0);pair<int,int> lr(1,0);

  REQUIRE(s.rectArea(ul,lr)==1);
  }
*/

TEST_CASE("Stats::size 1x2,(1,0)(1,0) avg","[weight=1][part=stats]"){

  PNG im(2,1);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(1,0);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(1,0);

  RGBAPixel avg((p->r + q->r)/2,(p->g + q->g)/2,(p->b + q->b)/2);

  REQUIRE(s.getAvg(ul,1,1)==*q);
}

TEST_CASE("Stats::size 1x2,(1,0)(1,0) var","[weight=1][part=stats]"){

  PNG im(2,1);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(1,0);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(1,0);

  REQUIRE(s.getVar(ul,1,1)==0);
}
// ======================
/*
  TEST_CASE("Stats::size 2x1,(0,0)(0,1) area","[weight=1][part=stats]"){

  PNG im(1,2);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(0,1);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(0,0);pair<int,int> lr(0,1);

  RGBAPixel avg((p->r + q->r)/2,(p->g + q->g)/2,(p->b + q->b)/2);

  REQUIRE(s.rectArea(ul,lr)==2);
  }
*/

TEST_CASE("Stats::size 2x1,(0,0)(0,1) avg","[weight=1][part=stats]"){

  PNG im(1,2);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(0,1);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(0,0);

  RGBAPixel avg((p->r + q->r)/2,(p->g + q->g)/2,(p->b + q->b)/2);

  REQUIRE(s.getAvg(ul,1,2)==avg);
}
TEST_CASE("Stats::size 2x1,(0,0)(0,1) var","[weight=1][part=stats]"){

  PNG im(1,2);
  RGBAPixel * p = im.getPixel(0,0);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(0,1);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(0,0);

  RGBAPixel avg((p->r + q->r)/2,(p->g + q->g)/2,(p->b + q->b)/2);

  REQUIRE(9063 - s.getVar(ul,1,2) <= 3);
  REQUIRE(9063 - s.getVar(ul,1,2) >= 0);
}
// ======================

/*
  TEST_CASE("Stats::size 2x1,(0,1)(0,1) area","[weight=1][part=stats]"){

  PNG im(1,2);
  RGBAPixel * p = im.getPixel(0,1);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(0,1);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(0,1);pair<int,int> lr(0,1);

  REQUIRE(s.rectArea(ul,lr)==1);
  }
*/

TEST_CASE("Stats::size 2x1,(0,1)(0,1) avg","[weight=1][part=stats]"){

  PNG im(1,2);
  RGBAPixel * p = im.getPixel(0,1);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(0,1);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(0,1);

  REQUIRE(s.getAvg(ul,1,1)==*q);
}

TEST_CASE("Stats::size 2x1,(0,1)(0,1) var","[weight=1][part=stats]"){

  PNG im(1,2);
  RGBAPixel * p = im.getPixel(0,1);
  p->r = 100;p->g = 150;p->b = 200;
  RGBAPixel * q = im.getPixel(0,1);
  q->r = 50;q->g = 75;q->b = 100;
  stats s(im);
  pair<int,int> ul(0,1);

  REQUIRE(s.getVar(ul,1,1)==0);
}
// ======================

/*
  TEST_CASE("Stats::size 2x3,(0,0)(2,1) area","[weight=1][part=stats]"){

  PNG im(3,2);

  for (int i = 0; i < 2; i++){
  for (int j = 0; j < 3; j++) {
  RGBAPixel *p = im.getPixel(j,i);
  p->r = 100*i;p->g = 100*j; p->b = 100*i + j;
  }
  }
  stats s(im);
  pair<int,int> ul(0,0);pair<int,int> lr(2,1);

  REQUIRE(s.rectArea(ul,lr)==6);
  }
*/

TEST_CASE("Stats::size 3x2,(0,0)(2,1) avg","[weight=1][part=stats]"){

  PNG im(3,2);

  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 3; j++) {
      RGBAPixel * p = im.getPixel(j,i);
      p->r = 100*i;p->g = 100*j; p->b = 100*i + j;
    }
  }
  stats s(im);
  pair<int,int> ul(0,0);

  RGBAPixel p(50,100,51);
  REQUIRE(s.getAvg(ul,3,2)==p);
}

TEST_CASE("Stats::size 3x2,(0,0)(2,1) var","[weight=1][part=stats]"){

  PNG im(3,2);

  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 3; j++) {
      RGBAPixel *p = im.getPixel(j,i);
      p->r = 100*i;p->g = 100*j; p->b = 100*i + j;
    }
  }
  stats s(im);
  pair<int,int> ul(0,0);

  REQUIRE(70004 - s.getVar(ul,3,2)<=3);
  REQUIRE(70004 - s.getVar(ul,3,2)>=0);
}
// ======================
/*
  TEST_CASE("Stats::size 2x3,(0,1)(1,1) area","[weight=1][part=stats]"){

  PNG im(3,2);

  for (int i = 0; i < 2; i++){
  for (int j = 0; j < 3; j++) {
  RGBAPixel *p = im.getPixel(j,i);
  p->r = 100*i;p->g = 100*j; p->b = 100*i + j;
  }
  }
  stats s(im);
  pair<int,int> ul(0,1);pair<int,int> lr(1,1);

  REQUIRE(s.rectArea(ul,lr)==2);
  }
*/

TEST_CASE("Stats::size 3x2,(0,1)(1,1) avg","[weight=1][part=stats]"){

  PNG im(3,2);

  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 3; j++) {
      RGBAPixel * p = im.getPixel(j,i);
      p->r = 100*i;p->g = 100*j; p->b = 100*i + j;
    }
  }
  stats s(im);
  RGBAPixel p(100,50,100);
  pair<int,int> ul(0,1);

  REQUIRE(s.getAvg(ul,2,1)==p);
}

TEST_CASE("Stats::size 3x2,(0,1)(1,1) var","[weight=1][part=stats]"){

  PNG im(3,2);

  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 3; j++) {
      RGBAPixel *p = im.getPixel(j,i);
      p->r = 100*i;p->g = 100*j; p->b = 100*i + j;
    }
  }
  stats s(im);
  pair<int,int> ul(0,1);

  REQUIRE(5001 - s.getVar(ul,2,1)<=3);
  REQUIRE(5001 - s.getVar(ul,2,1)>=0);
}
//**********************

/*
  TEST_CASE("Stats::size 2x3,(1,0)(1,1) area","[weight=1][part=stats]"){

  PNG im(3,2);

  for (int i = 0; i < 2; i++){
  for (int j = 0; j < 3; j++) {
  RGBAPixel *p = im.getPixel(j,i);
  p->r = 100*i;p->g = 100*j; p->b = 100*i + j;
  }
  }
  stats s(im);
  pair<int,int> ul(1,0);pair<int,int> lr(1,1);

  REQUIRE(s.rectArea(ul,lr)==2);
  }
*/

TEST_CASE("Stats::size 3x2,(1,0)(1,1) avg","[weight=1][part=stats]"){

  PNG im(3,2);

  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 3; j++) {
      RGBAPixel * p = im.getPixel(j,i);
      p->r = 100*i;p->g = 100*j; p->b = 100*i + j;
    }
  }
  stats s(im);
  pair<int,int> ul(1,0);
  RGBAPixel p(50,100,51);

  REQUIRE(s.getAvg(ul,1,2)==p);
}

TEST_CASE("Stats::size 3x2,(1,0)(1,1) var","[weight=1][part=stats]"){

  PNG im(3,2);

  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 3; j++) {
      RGBAPixel *p = im.getPixel(j,i);
      p->r = 100*i;p->g = 100*j; p->b = 100*i + j;
    }
  }
  stats s(im);
  pair<int,int> ul(1,0);

  REQUIRE(10000 - s.getVar(ul,1,2)<=3);
  REQUIRE(10000 - s.getVar(ul,1,2)>=0);
}
//**********************

/*
  TEST_CASE("Stats::size 4x3,(1,1)(2,3) area","[weight=1][part=stats]"){

  PNG im(3,4);

  for (int i = 0; i < 4; i++){
  for (int j = 0; j < 3; j++) {
  RGBAPixel *p = im.getPixel(j,i);
  p->r = 50*i;p->g = 100*j; p->b = 50*i + j;
  }
  }
  stats s(im);
  pair<int,int> ul(1,1);pair<int,int> lr(2,3);

  REQUIRE(s.rectArea(ul,lr)==6);
  }
*/

TEST_CASE("Stats::size 3x4,(1,1)(2,3) avg","[weight=1][part=stats]"){

  PNG im(3,4);

  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 3; j++) {
      RGBAPixel *p = im.getPixel(j,i);
      p->r = 50*i;p->g = 100*j; p->b = 50*i + j;
    }
  }
  stats s(im);
  pair<int,int> ul(1,1);pair<int,int> lr(2,3);
  RGBAPixel p(100,150,101);

  REQUIRE(s.getAvg(ul,2,3)==p);
}

TEST_CASE("Stats::size 3x4,(1,1)(2,3) var","[weight=1][part=stats]"){

  PNG im(3,4);

  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 3; j++) {
      RGBAPixel *p = im.getPixel(j,i);
      p->r = 50*i;p->g = 100*j; p->b = 50*i + j;
    }
  }
  stats s(im);
  pair<int,int> ul(1,1);

  REQUIRE(35002 - s.getVar(ul,2,3)<=3);
  REQUIRE(35002 - s.getVar(ul,2,3)>=0);
}
//**********************
/*
  TEST_CASE("Stats::large image, build","[weight=1][part=stats]"){

  PNG im;
  im.readFromFile("images/ada.png");

  stats s(im);
  pair<int,int> ul(0,0);
  pair<int,int> lr(im.width() -1,im.height()-1);

  REQUIRE(s.rectArea(ul,lr) == im.width() * im.height());

  }
*/

TEST_CASE("stats::getAvg","[weight=1][part=stats]"){
    PNG data; data.resize(2,2);
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j++){
            RGBAPixel * p = data.getPixel(i,j);
            p->r = 20 * i + 3 * j;
            p->g = 3 * i + 20 * j;
            p->b = 23 * i + 23 * j;
            p->a = 1.0;
        }
    }
    stats s(data);
    pair<int,int> ul(0,0);
    RGBAPixel result = s.getAvg(ul,2,2);
    RGBAPixel expected(11,11,23);

    REQUIRE(result == expected);
}


TEST_CASE("stats::getVar","[weight=1][part=stats]"){
    PNG data; data.resize(2,2);
    for (int i = 0; i < 2; i ++){
        for (int j = 0; j < 2; j++){
            RGBAPixel * p = data.getPixel(i,j);
            p->r = 20 * i + 3 * j;
            p->g = 3 * i + 20 * j;
            p->b = 23 * i + 23 * j;
            p->a = 1.0;
        }
    }
    stats s(data);
    pair<int,int> ul(0,0);
    double result = s.getVar(ul,2,2);

    REQUIRE(result == 1876);
}
