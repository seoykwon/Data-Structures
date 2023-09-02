#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG &baseim, const PNG &mazeim, pair<int, int> s)
{
    // start.first = s.first;
    // start.second = s.second;
    start = s;
    base = PNG(baseim);
    maze = PNG(mazeim);
}

void treasureMap::setGrey(PNG &im, pair<int, int> loc)
{

    /* YOUR CODE HERE */
    //you should compute each value as 2*(x/4), where
    // x is the integer value of a colour channel.
    // num&(1<<n)
    // int d = rr gg bb (binary bit)
    //         65 43 21
    // change rgb of image with given d
    int y = loc.first;
    int x = loc.second;
    //RGBAPixel *pixel = im.getPixel(x, y);
    RGBAPixel *pixel = im.getPixel(y, x);

    pixel->r = 2*(pixel->r/4);
    pixel->g = 2*(pixel->g/4);
    pixel->b = 2*(pixel->b/4);
}

// This function takes an image, a location, and an integer value.
// Change the colour channels in loc of the image
// so that they encode the distance d.
// Here's how it's done: Consider
// Consider the value of d%64 to be a 6 bit integer and the pixel in location
// loc to be (r,g,b). The two most significant
// bits of d%64 will be used to set the value of the red channel by
// changing r. The two least significant bits of d%64 will be used
// to set the value of the blue channel by changing b. And the remaining
// two bits of d%64 will be used to set the value of the green channel
// by changing g.
//
// Now consider the value of any colour channel, x, represented as an
// 8 bit binary number. To encode d, simply replace the 2 lower order
// bits in x with the corresponding bits from d, as described above.
void treasureMap::setLOB(PNG &im, pair<int, int> loc, int d)
{
    /* YOUR CODE HERE */
    // num&(1<<n)
    // int d = rr gg bb (binary bit)
    //         65 43 21
    // change rgb of image with given d
    /*
    int y = loc.first;
    int x = loc.second;
    RGBAPixel* pixel = im.getPixel(x, y);
    d = d%64;
    int mask = 252; //0xfc, 111100
    int redBit1 = d & 0x30;//110000 //d & (1 << 5);
    //int redBit2 = d & (1 << 6);
    cout << redBit1 << " r1 ";
    //cout << redBit2 << " r2 ";

    int greenBit1 = d & 0x0c; //001100
    //int greenBit2 = d & (1 << 4);
    cout << greenBit1 << " g1 ";
    //cout << greenBit2 << " g2 ";

    int blueBit1 = d & 0x03; //000011
    //int blueBit2 = d & (1 << 2);

    cout << blueBit1 << " b1 ";
    //cout << blueBit2 << " b2 ";

    //((10010100 <<8) + 01110100) & (1111111111110000)

    int red = (pixel->r << 8 +redBit1) & mask;
    int green = (pixel->g << 8 +greenBit1) & mask;
    int blue = (pixel->b << 8 +blueBit1) & mask;
    
    //needs to fix
    pixel->r = red;
    pixel->g = green;
    pixel->b = blue; */

    RGBAPixel* pixel = im.getPixel(loc.first, loc.second);
    pixel->r = ((pixel->r >> 2) << 2) + ((d / 16) % 4);
    pixel->g = (pixel->g & 0xFC) + ((d / 4) % 4);
    pixel->b = (pixel->b & 0xFC) + (d % 4);
}



PNG treasureMap::renderMap()
{
    
    // step 0 = make a copy of the base image.
    // PNG copy = _copy(base);
    PNG copy = PNG(base);

    // step 1 = initialize working vectors
    // a. Define a 2d vector whose dimensions are the same as the image, and whose
    //       values are boolean. Use this vector to indicate whether or not a location
    //       has been visited by the traversal.
    vector<vector<bool>> visited;
    visited.resize(copy.width(), vector<bool>(copy.height()));

    // b. Define a 2d vector whose dimensions are the same as the image, and whose
    //       values are integers. This structure will be used to store the length of the
    //       shortest path between the current location and the start location.
    vector<vector<int>> pathDist;
    pathDist.resize(copy.width(), vector<int>(copy.height()));
    // vector<vector<int>> pathDist(copy.height(), vector<int>(1, copy.width()));

    // step 2 = initialize a queue whose purpose is to orchestrate the traversal.
    // template <class T>
    // Queue<T> toExplore;
    Queue<pair<int, int>> toExplore;

    // step 3 = start location setup
    //       a. mark the start location as visited (structure in step 1a)
    //       b. set the distance to the start to be 0 (structure in step 1b)
    //       c. encode the distance within the start location's lower order bits of the treasure map
    //           (structure in step 0)
    //       d. enqueue the start location. (structure in step 2)
    visited[start.first][start.second] = true;
    pathDist[start.first][start.second] = 0;
    setLOB(copy, start, 0);
    toExplore.enqueue(start);

    // step 4
    //      While the queue is not empty:
    //       a. set the current location, curr, to the value at the front of the queue (and dequeue).
    //
    while (!toExplore.isEmpty())
    {
        pair<int, int> curr = toExplore.peek();
        toExplore.dequeue();
        // b. for each compass neighbor, p, of curr in the order of left, below, right, above:
        vector<pair<int, int>> neigh = neighbors(curr); // gives int position

        //          i. if p is "good" (defined below) then
        //              1) mark p's location as visited
        //              2) set p's distance to the start to be curr's distance, + 1.
        //              3) encode the distance in the lower order bits of the treasure map
        //              4) enqueue p

        for (auto neighbor : neighbors(curr)) {
            if (good(visited, curr, neighbor))
            {
                visited[neighbor.first][neighbor.second] = true;
                
                pathDist[neighbor.first][neighbor.second] = pathDist[curr.first][curr.second] + 1;
                
                setLOB(copy, neighbor, pathDist[neighbor.first][neighbor.second]);
                toExplore.enqueue(neighbor);
            }
        }
    }

    // step 5
    return copy;

}

//draws the entire maze on a copy of the base image by darkening the locations
// so it's visible as a shadow.
PNG treasureMap::renderMaze()
{
    PNG copy = PNG(base);
 
    vector<vector<bool>> visited;
    visited.resize(copy.width(), vector<bool>(copy.height()));

    Queue<pair<int, int>> toExplore;

    visited[start.first][start.second] = true;

    toExplore.enqueue(start);
    
    // This function also draws a red 7px x 7px square at the start                                                                                    
    // location. If the start location is near the edge of the image,
    // just draw the existing portion of the square. The start 
    // should be at the center of the square.
    //drawSquare(copy);

    while (!toExplore.isEmpty())
    {
        pair<int,int> curr = toExplore.peek();
        toExplore.dequeue();
        
        for (auto neighbor : neighbors(curr)) {
            if (good(visited, curr, neighbor))
            {
                setGrey(copy, neighbor);
                visited[neighbor.first][neighbor.second] = true;
                toExplore.enqueue(neighbor);
            }
        }
    }

    drawSquare(&copy);

    // step 5
    return copy;

}

// tests next, a neighbor (adjacent vertex) of curr to see if it is
// 1. within the image, 2. unvisited, and 3. the same colour as curr in
// the maze image (member var).  An entry in table v is true if a cell
// has previously been visited, and false, otherwise. Colour sameness is
// measured using the == operator on RGBAPixel values.
bool treasureMap::good(vector<vector<bool>> &v, pair<int, int> curr, pair<int, int> next)
{
    /* YOUR CODE HERE */
    // input(if visited, curr position, neighbor)
    /*
    int y = next.first;
    int x = next.second;
    if (y <= (int)base.height() && x <= (int)base.width())
    {
        vector<bool> row = v.at(y);
        bool isVisited = row.at(x);
        if (!isVisited)
        {
            if (maze.getPixel(x, y) == maze.getPixel(curr.second, curr.first))
            {
                return true;
            }
        }
    }
    return false;*/

    if (next.first >= 0 && next.first < (int)base.width() && next.second >= 0 && next.second < (int)base.height())
    {
        if (v[next.first][next.second] == false)
        {
            if (*maze.getPixel(curr.first, curr.second) == *maze.getPixel(next.first, next.second))
            {
                return true;
            }
        }
    }
    return false;
}

vector<pair<int, int>> treasureMap::neighbors(pair<int, int> curr)
{

    /* YOUR CODE HERE */
    vector<pair<int, int>> neigh;
    int col = curr.first;
    int row = curr.second;
    pair<int, int> left(col, row - 1);
    pair<int, int> below(col - 1, row);
    pair<int, int> right(col, row + 1);
    pair<int, int> above(col + 1, row);
    neigh.push_back(left);
    neigh.push_back(below);
    neigh.push_back(right);
    neigh.push_back(above);
    return neigh;

}

template <class T>
T treasureMap::trav2DArray(vector<vector<T>> v, pair<int, int> loc)
{
    vector<T> row = v.at(loc.first);
    return row.at(loc.second);
}

bool treasureMap::isInBound(string direc) {
    //PNG copy = PNG(base);
    int w = base.width();
    int h = base.height();
    int y = start.first;
    int x = start.second;

    if (direc == "left") {
        if((x-3) < 0) {
            return false;
        }

    }else if (direc == "below") {
        if((y - 3) < 0) {
            return false;
        }
    }else if (direc == "right") {
        if((x+3 > w)) {
            return false;
        }
    }else if (direc == "above") {
        if((y+3 > h)) {
            return false;
        }
    }else {
        return true;
    }
    
}

bool treasureMap::outOfBound(int x, int y) {
    int w = base.width();
    int h = base.height();


    bool xOut = (x > w) || (x < 0);
    bool yOut = (y > h) || (y < 0);

    if (xOut || yOut) {
        return true;
    } else {
        return false;
    }
    
}

void treasureMap::drawSquare(PNG* im) {

    RGBAPixel* pixel;
    for (int i = start.first - 3; i <= start.first + 3; i++) {
        for (int j = start.second - 3; j <= start.second + 3; j++) {
            if (i < (int)im->width() && j < (int)im->height() && i >= 0 && j >= 0) {
                pixel = im->getPixel(i , j);
                pixel->r = 255;
                pixel->b = 0;
                pixel->g = 0;
            
            }
        }
    }


}
