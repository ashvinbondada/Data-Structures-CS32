//
//  History.cpp
//  Project-1
//
//  Created by Ashvin Bondada on 1/6/22.
//

#include "History.h"
#include <iostream>
using namespace std;


History::History(int nRows, int nCols)
: m_nRows(nRows), m_nCols(nCols)
{
    // Fill the history grid with dots
for (int r = 0; r < nRows ; r++)
    for (int c = 0; c < nCols; c++)
        m_grid[r][c] = '.';
}

bool History::record(int r, int c) {
    if (r > m_nRows || c > m_nCols) {
        return false;
    }
    // Position (row,col) in the mesa coordinate system is represented in
    // the array element grid[row-1][col-1]
        if (m_grid[r-1][c-1] == '.')
            m_grid[r-1][c-1] = 'A';
        else if (m_grid[r-1][c-1] != 'Z')
            m_grid[r-1][c-1]++;
        return true;
    }

void History::display() const {
    clearScreen();
    for (int r = 0; r < m_nRows ; r++)
    {
        for (int c = 0; c < m_nCols; c++)
            cout << m_grid[r][c];
        cout << endl;
    }
    cout << endl;
}
