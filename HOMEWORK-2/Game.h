#ifndef _HOMEWORK_2_GAME_H_
#define _HOMEWORK_2_GAME_H_

#include "Cell.h"
#include "Array.h"
#include "Board.h"

class Game {
public:
    Game(const Array<Cell> &cells);

    void tick(); // do cycle of game

    void show(); // show coordinates of board

    void show(int minX, int minY, int maxX, int maxY); // show state of board by coordinates

    int births() const; // get count of births

    int deaths() const; // get count of deaths

private:
    Board<bool> _board;
    Array<Cell> _cells;
    static const int _moves[8][2];
    int _births;
    int _deaths;
};

#endif //_HOMEWORK_2_GAME_H_

