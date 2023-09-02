
#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

#include "sqtree.h"

TEST_CASE("sqtree::basic ctor render","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/colour.png");

    SQtree t1(img); // defaults to tolerance=0.0

    PNG out = t1.render();

    REQUIRE(out==img);
}


TEST_CASE("sqtree::basic copy","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/colour.png");

    SQtree t1(img);
    SQtree t1copy(t1);

    PNG out = t1copy.render();

    REQUIRE(out==img);
}

TEST_CASE("sqtree::tolerance construction and render","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/rocky_bullwinkle.png");
    
    SQtree t1(img,4000.0); 
    PNG result = t1.render();

    // REMOVE FOR TESTING
    //    result.writeToFile("images/soln/rb4000.png");

    PNG expected; 
    expected.readFromFile("images/soln/rb4000.png");

    REQUIRE(expected==result);
}

TEST_CASE("sqtree::size check","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/rocky_bullwinkle.png");
    
    SQtree t1(img,4000.0); 
    int result = t1.size();

    // REMOVE FOR TESTING
    //   cerr << "rb4000 size = " << result << endl;

    int expected = 15423;

    REQUIRE(expected==result);
}

TEST_CASE("sqtree::big tolerance construction and render","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/van.png");
    
    SQtree t1(img,5590.0);
    PNG result = t1.render();

    // REMOVE FOR TESTING
        result.writeToFile("images/soln/van5590.png");

    PNG expected; 
    expected.readFromFile("images/soln/van5590.png");

    REQUIRE(expected==result);
}

TEST_CASE("sqtree::big size check","[weight=1][part=sqtree]"){
    PNG img;
    img.readFromFile("images/orig/van.png");
    
    SQtree t1(img,5590.0); 
    int result = t1.size();

    // REMOVE FOR TESTING
    // cerr << "van5590 size = " << result << endl;

    int expected = 31755;

    REQUIRE(expected==result);
}


