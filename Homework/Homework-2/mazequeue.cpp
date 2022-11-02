//
//  mazestack.cpp
//  Homework-2
//
//  Created by Ashvin Bondada on 1/27/22.
//

#include <iostream>
#include <queue>
using namespace std;


class Coord
{
  public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
  private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    //  • empty/undiscovered
    //  @ - available, discovered
    //  X - wall/cant move
    
    queue<Coord> cStack;
    cStack.push(Coord(sr, sc));
    maze[sr][sc] = '@';
    while (!cStack.empty()) {
        Coord curr = cStack.front();
        cStack.pop();
        if (curr.r() == er && curr.c() == ec) {
            return true;
        }
        if (maze[curr.r()][curr.c() - 1] == '.') {     //   moving west
            cStack.push(Coord(curr.r(), curr.c() - 1));
            maze[curr.r()][curr.c() - 1] = '@';
        }
        if (maze[curr.r() + 1][curr.c()] == '.') {     //  moving south
            cStack.push(Coord(curr.r() + 1, curr.c()));
            maze[curr.r() + 1][curr.c()] = '@';
        }
        if (maze[curr.r()][curr.c() + 1] == '.') {     //  moving east
            cStack.push(Coord(curr.r(), curr.c() + 1));
            maze[curr.r()][curr.c() + 1] = '@';
        }
        if (maze[curr.r() - 1][curr.c()] == '.') {     //  moving north
            cStack.push(Coord(curr.r() - 1, curr.c()));
            maze[curr.r() - 1][curr.c()] = '@';
        }
    }
     
    
    return false;
     
};

int main()
        {
            string maze[10] = {
                "XXXXXXXXXX",
                "X.X..X...X",
                "X....XXX.X",
                "X.XXXX.X.X",
                "X......XXX",
                "X.XX.X...X",
                "X.X..X.X.X",
                "X.X.XXXX.X",
                "X.X...X..X",
                "XXXXXXXXXX"
            };

            if (pathExists(maze, 10,10, 4,6, 1,1))
                cout << "Solvable!" << endl;
            else
                cout << "Out of luck!" << endl;
        }

