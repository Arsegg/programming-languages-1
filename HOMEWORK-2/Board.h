#ifndef _HOMEWORK_2_BOARD_H_
#define _HOMEWORK_2_BOARD_H_

#include <iostream>
#include "Matrix.h"

// Dynamically expanding matrix
// Matrix expands in all directions
// Board a;
// a.set(-5, -5, 123);
// a.set(5, 5, 321);
// a.set(5, -5, 456);
// a.set(-5, 5, 654);
template<class T=int>
class Board {
public:
    // get element by index or create it
    T &get(int x, int y) {
        ensureCapacity(x, y);

        if (x >= 0) {
            if (y >= 0) {
                return _rt[x][y];
            } else {
                return _rb[x][-y];
            }
        } else {
            if (y >= 0) {
                return _lt[-x][y];
            } else {
                return _lb[-x][-y];
            }
        }
    }

    // set element by index or create it
    void set(int x, int y, const T &value = T()) {
        ensureCapacity(x, y);

        if (x >= 0) {
            if (y >= 0) {
                _rt[x][y] = value;
            } else {
                _rb[x][-y] = value;
            }
        } else {
            if (y >= 0) {
                _lt[-x][y] = value;
            } else {
                _lb[-x][-y] = value;
            }
        }
    }

    // show coordinates of board
    void show(int minX, int minY, int maxX, int maxY) {
        for (int j = maxY; j >= minY; j--) {
            for (int i = minX; i <= maxX; i++) {
                std::cout << (get(j, i) ? "O" : ".");
            }
            std::cout << "\n";
        }
    }

    Board &operator=(const Board &board) {
        _lt = board._lt;
        _rt = board._rt;
        _lb = board._lb;
        _rb = board._rb;
        _minX = board._minX;
        _minY = board._minY;
        _maxX = board._maxX;
        _maxY = board._maxY;
    }

    // minimal x coordinate
    int minX() const {
        return _minX;
    }

    // minimal y coordinate
    int minY() const {
        return _minY;
    }

    // maximal x coordinate
    int maxX() const {
        return _maxX;
    }

    // maximal y coordinate
    int maxY() const {
        return _maxY;
    }

private:
    Matrix<T> _lt;        // left-top
    Matrix<T> _rt;        // right-top
    Matrix<T> _lb;        // left-bottom
    Matrix<T> _rb;        // right-bottom
    int _minX = -1;       // minimal x coordinate
    int _minY = -1;       // minimal y coordinate
    int _maxX = 1;        // maximal x coordinate
    int _maxY = 1;        // maximal y coordinate

    void ensureCapacity(int x, int y) {
        if (x < _minX) {
            _minX = x;
        }
        if (x > _maxX) {
            _maxX = x;
        }
        if (y < _minY) {
            _minY = y;
        }
        if (y > _maxY) {
            _maxY = y;
        }
        _lt.size(-_minX + 1, _maxY + 1);
        _rt.size(_maxX + 1, _maxY + 1);
        _lb.size(-_minX + 1, -_minY + 1);
        _rb.size(_maxX + 1, -_minY + 1);
    }
};


#endif //_HOMEWORK_2_BOARD_H_
