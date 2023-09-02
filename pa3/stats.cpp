#include "stats.h"
#include <stdio.h>
#include <string.h>

#include "stats.h"

stats::stats(PNG &im)
{

    // Initialize the private vectors so that, for each color, entry
    // (x,y) is the sum of that color value in the rectangle from
    // (0,0) to (x,y). Similarly, for each color, the sumSq vector
    // entry (x,y) is the sum of that color squared over all image
    // pixels from (0,0) to (x,y).
     RGBAPixel* pixel = im.getPixel(0, 0);
    int w = im.width();
    int h = im.height();

    vector<long> height(h, -1);

    sumRed.resize(w, height);
    sumGreen.resize(w, height);
    sumBlue.resize(w, height);
    
    sumsqRed.resize(w, height);
    sumsqGreen.resize(w, height);
    sumsqBlue.resize(w, height);
    

    sumRed.at(0).at(0) = (long) pixel->r;
    sumGreen.at(0).at(0) = (long) pixel->g;
    sumBlue.at(0).at(0) = (long) pixel->b;
    sumsqRed.at(0).at(0) = (long) pixel->r;
    sumsqGreen.at(0).at(0) = (long) pixel->g;
    sumsqBlue.at(0).at(0) = (long) pixel->b;
    long sumR = 0;
    long sumG = 0;
    long sumB = 0;
    long sumSqR = 0;
    long sumSqG = 0;
    long sumSqB = 0;
    long currR = (long) pixel->r;
    long currG = (long) pixel->g;
    long currB = (long) pixel->b;

    long upR = 0;
    long upG = 0;
    long upB = 0;
    long leftR = 0;
    long leftG = 0;
    long leftB = 0;
    long diagR = 0;
    long diagG = 0;
    long diagB = 0;

    long upSqR = 0;
    long upSqG = 0;
    long upSqB = 0;
    long leftSqR = 0;
    long leftSqG = 0;
    long leftSqB = 0;
    long diagSqR = 0;
    long diagSqG = 0;
    long diagSqB = 0;

    pair<int, int> up;
    pair<int, int> left;
    pair<int, int> diag;

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {

            pixel = im.getPixel(i, j);
            currR = pixel->r;
            currG = pixel->g;
            currB = pixel->b;

            up = make_pair(i, j - 1);
            left = make_pair(i - 1, j);
            diag = make_pair(i - 1, j - 1);

            if (i != 0 && j != 0)  {//image not touching edge
                //image not at edge

                upR = sumRed[up.first][up.second];
                //cout << upR << " up " ;
                leftR = sumRed[left.first][left.second];
                //cout << leftR << " left " ;
                diagR = sumRed[diag.first][diag.second];
                //cout << diagR << " diag " ;
                upG = sumGreen[up.first][up.second];
                leftG = sumGreen[left.first][left.second];
                diagG = sumGreen[diag.first][diag.second];
                upB = sumBlue[up.first][up.second];
                leftB = sumBlue[left.first][left.second];
                diagB = sumBlue[diag.first][diag.second];

                upSqR = sumsqRed[up.first][up.second];
                leftSqR = sumsqRed[left.first][left.second];
                diagSqR = sumsqRed[diag.first][diag.second];
                upSqG = sumsqGreen[up.first][up.second];
                leftSqG = sumsqGreen[left.first][left.second];
                diagSqG = sumsqGreen[diag.first][diag.second];
                upSqB = sumsqBlue[up.first][up.second];
                leftSqB = sumsqBlue[left.first][left.second];
                diagSqB = sumsqBlue[diag.first][diag.second];

            }
            if (j == 0 && i != 0) {// y = 0, image at top
                
                leftR = sumRed[left.first][left.second];
                leftG = sumGreen[left.first][left.second];
                leftB = sumBlue[left.first][left.second];

                leftSqR = sumsqRed[left.first][left.second];
                leftSqG = sumsqGreen[left.first][left.second];
                leftSqB = sumsqBlue[left.first][left.second];

                upR = 0;
                upG = 0;
                upB = 0;
                upSqR = 0;
                upSqG = 0;
                upSqB = 0;

                diagR = 0;
                diagG = 0;
                diagB = 0;
                diagSqR = 0;
                diagSqG = 0;
                diagSqB = 0;
                    
                }
            if (i == 0 && j != 0) { //image touch left
                
                //image touch left
                //cout << currR << " curr " ;
                upR = sumRed[up.first][up.second];
                //cout << upR << " up0 " ;
                upG = sumGreen[up.first][up.second];
                upB = sumBlue[up.first][up.second];

                upSqR = sumsqRed[up.first][up.second];
                upSqG = sumsqGreen[up.first][up.second];
                upSqB = sumsqBlue[up.first][up.second]; 

                leftR = 0;
                leftG = 0;
                leftB = 0;
                leftSqR = 0;
                leftSqG = 0;
                leftSqB = 0;

                diagR = 0;
                diagG = 0;
                diagB = 0;
                diagSqR = 0;
                diagSqG = 0;
                diagSqB = 0;


                }

                sumR = currR + upR + leftR - diagR;
                sumRed[i][j] = sumR;
                sumSqR = currR * currR + upSqR + leftSqR - diagSqR;
                sumsqRed[i][j] = sumSqR;

                sumG = currG + upG + leftG - diagG;
                sumGreen[i][j] = sumG;
                sumSqG = currG * currG + upSqG + leftSqG - diagSqG;
                sumsqGreen[i][j] = sumSqG;

                sumB = currB + upB + leftB - diagB;
                sumBlue[i][j] = sumB;
                sumSqB = currB * currB + upSqB + leftSqB - diagSqB;
                sumsqBlue[i][j] = sumSqB;
        }
    }
}

long stats::getSum(char channel, pair<int, int> ul, int w, int h)
{

    // Returns the sums of all pixel values in one color channel.
    // Useful in computing the average color of a rectangle.
    // @param channel is one of r, g, or b
    // @param ul is (x,y) of the upper left corner of the rectangle
    // @param w,h are the width and height of the rectangle

    long sum = 0;
    vector<vector <long>> vec;
    int x = ul.first; // x value of start position 
    int y = ul.second; // y value



    if (channel == 'r') {
        vec = sumRed;
    } else if (channel == 'g') {
        vec = sumGreen;
    } else {
        vec = sumBlue;
    }

    long curr = vec[x+w-1][y+h-1];
    //cout << w << " , " << h << " // w&h // ";
    //cout << curr << " curr ";
    long left;
    long up;
    long diag;

    if (x == 0 && y == 0) { //(0,0)
        sum = curr;
    } else if (x != 0 && y != 0) { //not touching edge
        up = vec.at(x+w-1).at(y-1);
        diag = vec.at(x-1).at(y-1);
        left = vec.at(x-1).at(y+h-1);
        sum = curr - left - up + diag;
    } else if (x == 0) { //touch left
        up = vec.at(x+w-1).at(y-h);
        sum = curr - up;
    } else { //touch up
        left = vec.at(x-w).at(y+h-1);
        sum = curr - left;         
    }

    //cout << sum << " sum ";
    return sum;  
}

long stats::getSumSq(char channel, pair<int, int> ul, int w, int h)
{

    // Returns the sums of squares of all pixel values in one color
    // channel.
    // Useful in computing the variance of a rectangle
    // @param channel is one of r, g, or b
    // @param ul is (x,y) of the upper left corner of the rectangle
    // @param w,h are the width and height of the rectangle

    long sum = 0;
    vector<vector <long>> vec;
    int x = ul.first; // x value of start position
    int y = ul.second; // y value



    if (channel == 'r') {
        vec = sumsqRed;
    } else if (channel == 'b') {
        vec = sumsqBlue;
    } else {
        vec = sumsqGreen;
    }

    long curr = vec[x+w-1][y+h-1];
    long left;
    long up;
    long diag;

    if (x == 0 && y == 0) {
        sum = curr;
    } else if (x != 0 && y != 0) {
        long up = vec.at(x+w-1).at(y-1);
        long diag = vec.at(x-1).at(y-1);
        long left = vec.at(x-1).at(y+h-1);
        sum = curr - left - up + diag;
    } else if (x == 0 && y != 0) {
        long up = vec.at(x+w-1).at(y-1);
        sum = curr - up;
    } else { //y==0 && x != 0
        long left = vec.at(x-1).at(y+h-1);
        sum = curr - left;         
    }

    return sum; 
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int w, int h)
{

    // Given a rectangle, compute its sum of squared deviations from avg,
    // over all pixels and all color channels.
    // @param ul is (x,y) of the upper left corner of the rectangle
    // @param w,h are the width and height of the rectangle
    
    long area = (long) abs(w * h);
    //cout << area << " area ";
    long rSumSq = getSumSq('r', ul, w, h);
    //cout << rSumSq << " RsqSum ";
    long gSumSq = getSumSq('g', ul, w, h);
    //cout << gSumSq << " GsqSum ";
    long bSumSq = getSumSq('b', ul, w, h);
    //cout << bSumSq << " BsqSum ";

    long rSqSum = getSum('r', ul, w, h);
    long gSqSum = getSum('g', ul, w, h);
    long bSqSum = getSum('b', ul, w, h);

    rSqSum *= rSqSum;
    gSqSum *= gSqSum;
    bSqSum *= bSqSum;

    long rVar = rSumSq - rSqSum/area;
    long gVar = gSumSq - gSqSum/area;
    long bVar = bSumSq - bSqSum/area;

    return (double) rVar + gVar + bVar;
    //return 0;
}


RGBAPixel stats::getAvg(pair<int, int> ul, int w, int h)
{

    // Given a rectangle, return the average color value over the rectangle
    // as a pixel.
    // Each color component of the pixel is the average value of that
    // component over the rectangle.
    // @param ul is (x,y) of the upper left corner of the rectangle
    // @param w,h are the width and height of the rectangle
    int area = w * h;
    cout << ul.first << ", " << ul.second << " /ul/ ";
    cout << area << " area ";
    RGBAPixel pixel = RGBAPixel(0, 0, 0);
    long aveR = getSum('r', ul, w, h)/area;
    //cout << aveR << " aveR ";
    long aveG = getSum('g', ul, w, h)/area;
    cout << aveG << " aveG ";
    long aveB = getSum('b', ul, w, h)/area;

    pixel.r = aveR;
    pixel.g = aveG;
    pixel.b = aveB;

    return pixel;
}

void stats::printVector(char c, PNG im) {
    int x = im.width();
    int y = im.height();

    vector<vector<int>> v;

    /*if (c == 'r') {
        v = sumRed;
    } else if (c == 'g') {
        v = sumGreen;
    } else (c == 'b') {
        v = sumBlue;
    }*/

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            //cout << sumRed[i][j] << " (" << i << ", " << j << ") ";
            cout << sumGreen[i][j] << " (" << i << ", " << j << ") ";
            //cout << sumBlue[i][j] << " blue ";

            //cout << sumsqRed[i][j] << " (" << i << ", " << j << ") ";
            //cout << sumsqGreen[i][j] << " greensq ";
            //cout << sumsqBlue[i][j] << " (" << i << ", " << j << ") ";

        }
    }

}
