#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

/*
decoder::decoder(const PNG &tm, pair<int, int> s) : start(s), mapImg(tm){

    start = s;
    mapImg = tm;

    vector<vector<bool>> isVisited(mapImg.width(), vector<bool>(mapImg.height(), false));
    vector<vector<int>> distance(mapImg.width(), vector<int>(mapImg.height(), 0));
    // vector<vector<int>> distance(mapImg.width(), vector<int> (mapImg.height(), 0));
    vector<vector<pair<int, int>>> origins(mapImg.width(), vector<pair<int, int>>(mapImg.height(), make_pair(0, 0)));
    Queue<pair<int, int>> myQueue;

    //Stack<pair<int, int>> path; //e
    //pair<int, int> maxDistance; //e
    
    isVisited[start.first][start.second] = true;
    distance[start.first][start.second] = 0;
    origins[start.first][start.second] = start;
    //maxDistance = start; //e
    pathPts.push_back(start);
    myQueue.enqueue(start); 

    while (!myQueue.isEmpty())
    {
        pair<int, int> curr = myQueue.dequeue();
        for (pair<int, int> neighbor : neighbors(curr))
        {
            if (good(isVisited, distance, curr, neighbor))
            {
                origins
         [neighbor.first][neighbor.second] = curr;
                pathPts.push_back(neighbor);
                isVisited[neighbor.first][neighbor.second] = true;
                distance[neighbor.first][neighbor.second] = distance[curr.first][curr.second] + 1;
                //if (distance[neighbor.first][neighbor.second] >= distance[maxDistance.first][maxDistance.second])
                //{
                //    maxDistance = neighbor; // still on the maze
                //}
                myQueue.enqueue(neighbor);
            }
        }
    }

    //finds i of treasure in pathPtrs //CHANGE UP LATER
      int value = 0;
      for (int i = 0; i < pathLength(); i++) {
         pair<int, int> compare = pathPts[value];
         pair<int, int> curr = pathPts[i];

         if (distance[curr.first][curr.second] >= distance[compare.first][compare.second]) {
            value = i;
         }
      }    


      Stack<pair<int, int>> path;
      pair<int, int> solution = pathPts[value];
      
      path.push(solution);
      while (path.peek() != start) {
         solution = origins
[solution.first][solution.second];
         path.push(solution);
      }

      vector<pair<int, int>> newVector;
      while (!path.isEmpty()) {
         newVector.push_back(path.pop());
      }

      pathPts = newVector;

    
    curr = maxDistance;
    while (curr != start)
    {
        path.push(curr);
        curr = make_pair(origins
[curr.first][curr.second].first, origins
[curr.first][curr.second].second);
    }
    path.push(curr);
    while (!path.isEmpty())
    {
        pathPts.push_back(path.pop()); // made a pathPts which contains the solution (start to end)
    }
} 

*/

decoder::decoder(const PNG &tm, pair<int, int> s)
    : start(s), mapImg(tm)
{

   mapImg = tm;
   start = s;
   
   vector<vector<bool>> isVisited;
   isVisited.resize(mapImg.width(), vector<bool>(mapImg.height()));
   
   vector<vector<int>> distance;
   distance.resize(mapImg.width(), vector<int>(mapImg.height()));
   vector<vector<pair<int, int>>> origins;
   origins.resize(mapImg.width(), vector<pair<int, int>>(mapImg.height()));

   isVisited[start.first][start.second] = true;
   distance[start.first][start.second] = 0;

   Queue<pair<int, int>> myQueue;
   myQueue.enqueue(start);

   pair<int, int> curr;
   while (!myQueue.isEmpty()) {
      curr = myQueue.dequeue();
      for (auto neighbor : neighbors(curr)) {
         if (good(isVisited, distance, curr, neighbor)) {
               isVisited[neighbor.first][neighbor.second] = true;
               distance[neighbor.first][neighbor.second] = distance[curr.first][curr.second] + 1;
               origins[neighbor.first][neighbor.second] = curr;
               myQueue.enqueue(neighbor);
         }
      }
   }
   int longPath = -1;
   pair<int, int> treasureLocation = make_pair(-1, -1);
   for (int i = 0; i < mapImg.width(); i++) {
      for (int j = 0; j < mapImg.height(); j++) {
         if (distance[i][j] >= longPath) {
               longPath = distance[i][j];
               treasureLocation = make_pair(i, j);
         }
      }
   }

   pathPts = vector<pair<int, int>>(longPath + 1);
   pathPts[longPath] = treasureLocation;

   for (int i = longPath - 1; i >= 0; i--)
   {
      pair<int, int> curr = pathPts[i + 1];
      pathPts[i] = origins[curr.first][curr.second];
   }
}

PNG decoder::renderSolution()
{
   PNG copy = mapImg;
   for (int i = 0; i < (int)pathLength(); i++) {
      RGBAPixel *pixel = copy.getPixel(pathPts[i].first, pathPts[i].second); // removed .at[x]
      pixel->r = 255;
      pixel->g = 0;
      pixel->b = 0;
   }
   return copy; 
}

PNG decoder::renderMaze()
{

   PNG copy = mapImg;
   vector<vector<bool>> isVisited;
   isVisited.resize(mapImg.width(), vector<bool>(mapImg.height()));
   
   vector<vector<int>> distance;
   distance.resize(mapImg.width(), vector<int>(mapImg.height()));
   
   Queue<pair<int, int>> myQueue;

   isVisited[start.first][start.second] = true;
   myQueue.enqueue(start);

   pair<int, int> curr;
   while (!myQueue.isEmpty()) {
      curr = myQueue.dequeue();
      for (auto neighbor : neighbors(curr)) {
         if (good(isVisited, distance, curr, neighbor))
         { // functions parameters edit accordingly
               isVisited[neighbor.first][neighbor.second] = true;
               setGrey(copy, neighbor);
               myQueue.enqueue(neighbor);
               distance[neighbor.first][neighbor.second] = distance[curr.first][curr.second] + 1;
         }
      }
   }

   // draw square
   for (int i = start.first - 3; i <= start.first + 3; i++) {
      for (int j = start.second - 3; j <= start.second + 3; j++) {
         if (i >= 0 && i < (int)copy.width() && j >= 0 && j < (int)copy.height()) {
               RGBAPixel* pixel = copy.getPixel(i , j);
               pixel->r = 255;
               pixel->b = 0;
               pixel->g = 0;
         
         }
      }
   }

   return copy;
}

void decoder::setGrey(PNG &im, pair<int, int> loc)
{

    RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
    pixel->r = 2 * (pixel->r / 4);
    pixel->g = 2 * (pixel->g / 4);
    pixel->b = 2 * (pixel->b / 4);
}

pair<int,int> decoder::findSpot(){

   return pathPts.back();

}

int decoder::pathLength(){
   return pathPts.size();
}


bool decoder::good(vector<vector<bool>> &isVisited, vector<vector<int>> &d, pair<int, int> curr, pair<int, int> next)
{

   if (next.first >= 0 && next.first < (int)mapImg.width() && next.second >= 0 && next.second < (int)mapImg.height()) {
      if (!isVisited[next.first][next.second]) {
         if (compare(*mapImg.getPixel(next.first, next.second), d[curr.first][curr.second])) {
            return true;
         }
      }
   }
   return false;
}


vector<pair<int, int>> decoder::neighbors(pair<int, int> curr)
{

    vector<pair<int, int>> result;

    result.push_back(make_pair(curr.first - 1, curr.second)); // Left
    result.push_back(make_pair(curr.first, curr.second + 1)); // Below
    result.push_back(make_pair(curr.first + 1, curr.second)); // Right
    result.push_back(make_pair(curr.first, curr.second - 1)); // Above

    return result;
}


bool decoder::compare(RGBAPixel neighbor, int d)
{

    return (d + 1) % 64 == (neighbor.r % 4) * 16 + (neighbor.g % 4) * 4 + (neighbor.b % 4); // d+1 and next RGBA Pixel have to be the same
}