#include "block.h"
#include <cmath>
#include <iostream>

int Block::width() const
{
    return data.size();
}
int Block::height() const
{
    return data[0].size();
}

void Block::render(PNG &im, int column, int row) const
{
    int w = width();
    int h = height();

    for (int x = column; x < column + w; x++) {
        for (int y = row; y < row + h; y++) {
            RGBAPixel pixel = data[x - column][y - row];
            *im.getPixel(x, y) = pixel;
        }
    }
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
    data.resize(width, vector<RGBAPixel>(height));

    for (int x = column; x < width + column; x++) {
        
        for (int y = row; y < height + row; y++) {

            RGBAPixel *pixel = im.getPixel(x, y);
            data[x - column][y - row] = *pixel;
        }
    }
}

void Block::flipVert()
{
    int w = width();
    int h = height();

    for (int y = 0; y < h/2; y++) {

        for (int x = 0; x < w; x++) {

            RGBAPixel temp = data[x][y];
            data[x][y] = data[x][h - y - 1];
            data[x][h - y - 1] = temp;

        }
    }
}

void Block::flipHoriz()
{
    int w = width();
    int h = height();

    for (int x = 0; x < w/2; x++) {

        for (int y = 0; y < h; y++) {

            RGBAPixel temp = data[x][y];
            data[x][y] = data[w -x -1][y];
            data[w -x -1][y] = temp;

        }
    }
}

void Block::rotateRight()
{
    int w = width();
    int h = height();

    for (int x = 0; x < w; x++) {

        for (int y = x; y < h; y++) {

            RGBAPixel temp = data[x][y];
            data[x][y] = data[y][x];
            data[y][x] = temp;

        }
    }
    flipHoriz();
}
