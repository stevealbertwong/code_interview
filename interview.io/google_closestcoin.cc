/*
https://www.youtube.com/watch?v=xC8CGv1CyFk&ab_channel=interviewing.io

first, write a for loop to find closest coin on the board 

second, discuss how grid size and density level affect BFS n DFS in terms of O(N)

1) Write a function to determine the coin closest to you from a list of positions using Manhattan Distance

2) Find the cutoff at which to switch over to a breadth first search algorithm

3) Determine which is the optimal coin to collect when there are opponents present (each opponent only collects one coin)



g++ -std=c++14 -Wsizeof-array-argument google_closestcoin.cc -o google_closestcoin

*/
#include <iostream>
#include <vector>

using namespace std;

class Point {
    public:
        int x,y;
        Point() {
            this->x = 0;
            this->y = 0;
        }
        Point( int x, int y) {
            this->x = x;
            this->y = y;
        }
};

class Board{
    public: 
        std::vector<Point> coins;
        
        Point closestPoint(Point myPosition){
            
            uint closestCoinDistance = -1;
            Point closestCoin;

            for (size_t i = 0; i < coins.size(); i++)
            {
                uint xDistance = abs( coins[i].x - myPosition.x );
                uint yDistance = abs( coins[i].y - myPosition.y );
                uint totalDistance = yDistance + xDistance;

                if(closestCoinDistance == -1 || totalDistance < closestCoinDistance){
                    closestCoin.x = coins[i].x;
                    closestCoin.y = coins[i].y;
                }
            }
            return closestCoin;
        }
};



int main(int argc, char const *argv[])
{
    Board myBoard;
    Point myPos(1,1);
    Point pt1(2,4);
    Point pt2(3,10);
    Point pt3(6,7);
    myBoard.coins.push_back(pt1);
    myBoard.coins.push_back(pt2);
    myBoard.coins.push_back(pt3);
    Point closestPt = myBoard.closestPoint(myPos);

    return 0;
}
