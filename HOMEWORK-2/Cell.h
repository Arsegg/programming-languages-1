#ifndef _HOMEWORK_2_CELL_H_
#define _HOMEWORK_2_CELL_H_

// Class represent state of point
class Cell {
public:
    int x;
    int y;
    bool alive;

    Cell(int x, int y, bool alive = true) : x(x), y(y), alive(alive) {
    }

    Cell() : Cell(0, 0, false) {
    }

    friend bool operator==(const Cell &cell1, const Cell &cell2) {
        return cell1.x == cell2.x && cell1.y == cell2.y;
    }
};

#endif //_HOMEWORK_2_CELL_H_
