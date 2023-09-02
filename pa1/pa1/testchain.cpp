#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

// headers from PA's main.cpp
#include "chain.h"
#include "block.h"
#include "cs221util/PNG.h"
#include <iostream>

using namespace cs221util;
using namespace std;

// chain copy constructor
TEST_CASE("chain::basic copy constructor", "[weight=1][part=chain]")
{

    PNG pngin;
    pngin.readFromFile("img-input/jingle-dresssmall.png");

    Chain c(pngin, 32, 15);
    Chain d(c);

    PNG orig = c.render(32,15);
    PNG result = d.render(32,15);

    REQUIRE(result == orig);
}


TEST_CASE("chain::basic odd reverse", "[weight=1][part=chain]")
{
    PNG img;
    img.readFromFile("img-input/jingle-dresssmall.png");

    int cols = 3;
    int rows = 5;
    Chain c(img, cols,rows);

    c.reverse();
    PNG res = c.render(cols,rows);

    //res.writeToFile("img-soln/jdsoddreverse.png");
    PNG expected; expected.readFromFile("img-soln/jdsoddreverse.png");
    
    REQUIRE(res == expected);
}

TEST_CASE("chain::basic even reverse", "[weight=1][part=chain]")
{
    PNG img;
    img.readFromFile("img-input/jingle-dresssmall.png");
    int cols = 3;
    int rows = 10;
    Chain c(img, cols,rows);

    c.reverse();
    PNG res = c.render(cols,rows);

    //res.writeToFile("img-soln/jdsevenreverse.png");
    PNG expected; expected.readFromFile("img-soln/jdsevenreverse.png");
    REQUIRE(res == expected);

}


TEST_CASE("chain::basic rotate k = 1", "[weight=1][part=chain]")
{
    PNG img;
    img.readFromFile("img-input/jingle-dresssmall.png");
    int cols = 2;
    int rows = 10;

    Chain c(img, cols,rows);
    c.rotate(1);

    PNG res = c.render(cols,rows);

    REQUIRE(res == img);
    
}


TEST_CASE("chain::basic rotate k = 2", "[weight=1][part=chain]")
{
    PNG img;
    img.readFromFile("img-input/jingle-dresssmall.png");
    int cols = 2;
    int rows = 4;

    Chain c(img, cols,rows);
    c.rotate(2);

    PNG res = c.render(cols,rows);


    //res.writeToFile("img-soln/jdsrotate2.png");
    PNG expected; expected.readFromFile("img-soln/jdsrotate2.png");

    REQUIRE(res == expected);
    
}

TEST_CASE("chain::long rotate k = 12", "[weight=1][part=chain]")
{
    PNG img;
    img.readFromFile("img-input/jingle-dresssmall.png");
    int cols = 12;
    int rows = 5;

    Chain c(img, cols,rows);
    c.rotate(12);

    PNG res = c.render(cols,rows);


    //res.writeToFile("img-soln/jdsrotate12.png");
    PNG expected; expected.readFromFile("img-soln/jdsrotate12.png");

    REQUIRE(res == expected);
    
}

TEST_CASE("chain::basic odd rotate k = 2", "[weight=1][part=chain]")
{
    int cols = 5;
    PNG img(cols, 1);
    img.getPixel(0, 0)->r = 0;
    img.getPixel(1, 0)->r = 10;
    img.getPixel(2, 0)->r = 20;
    img.getPixel(3, 0)->r = 30;
    img.getPixel(4, 0)->r = 40;

    Chain c(img, cols,1);
    c.rotate(2);

    PNG res = c.render(cols,1);
    RGBAPixel *p0 = res.getPixel(0, 0);
    RGBAPixel *p1 = res.getPixel(1, 0);
    RGBAPixel *p2 = res.getPixel(2, 0);
    RGBAPixel *p3 = res.getPixel(3, 0);
    RGBAPixel *p4 = res.getPixel(4, 0);

    REQUIRE(p0->r == 10);
    REQUIRE(p1->r == 0);
    REQUIRE(p2->r == 30);
    REQUIRE(p3->r == 20);
    REQUIRE(p4->r == 40);
}

 //* Composite Tests 

TEST_CASE("chain::mirror large even", "[weight=1][part=chain]")
{
    int cols = 10;
    PNG img(cols, cols);
    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            img.getPixel(x, y)->r = x;
        }
    }

    Chain c(img, cols,cols);
    c.reverse();

    PNG res = c.render(cols,cols);
    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            int hVal = cols - 1 - x;
            RGBAPixel *pr = res.getPixel(x, y);
            REQUIRE(pr->r == hVal);
        }
    }
}

TEST_CASE("chain::mirror large odd", "[weight=1][part=chain]")
{
    int cols = 15;
    PNG img(cols, cols);
    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            img.getPixel(x, y)->r = x;
        }
    }

    Chain c(img, cols,cols);
    c.reverse();

    PNG res = c.render(cols,cols);
    for (int x = 0; x < cols; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            int hVal = cols - 1 - x;
            RGBAPixel *pr = res.getPixel(x, y);
            REQUIRE(pr->r == hVal);
        }
    }
}
