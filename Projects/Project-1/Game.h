//
//  Game.hpp
//  Project-1
//
//  Created by Ashvin Bondada on 1/5/22.
//

#ifndef Game_h
#define Game_h
//#include "Mesa.h"

class Mesa;

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

        // Mutators
    void play();

  private:
    Mesa* m_mesa;
};

int decodeDirection(char dir);

#endif /* Game_hpp */
