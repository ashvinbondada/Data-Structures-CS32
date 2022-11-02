//
//  History.hpp
//  Project-1
//
//  Created by Ashvin Bondada on 1/6/22.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History {
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_nRows;
        int m_nCols;
        char m_grid[MAXROWS][MAXCOLS];
    };

#endif /* History_h */
