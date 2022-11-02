//
//  main.cpp
//  homework-3-Problem-3
//
//  Created by Ashvin Bondada on 2/8/22.
//
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
//    If the start location is equal to the ending location, then we've
//            solved the maze, so return true.
    Coord curr(sr, sc);
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = '@';
    if (maze[curr.r()][curr.c() - 1] == '.') {     //   moving west
        pathExists(maze, nRows, nCols, curr.r(), curr.c() - 1, er, ec);
        return true;
    }
    if (maze[curr.r() + 1][curr.c()] == '.') {     //  moving south
        pathExists(maze, nRows, nCols, curr.r() + 1, curr.c(), er, ec);
        return true;
    }
    if (maze[curr.r()][curr.c() + 1] == '.') {     //  moving east
        pathExists(maze, nRows, nCols, curr.r(), curr.c() + 1, er, ec);
        return true;
    }
    if (maze[curr.r() - 1][curr.c()] == '.') {     //  moving north
        pathExists(maze, nRows, nCols, curr.r() - 1, curr.c(), er, ec);
        return true;
    }
    return false;
}
