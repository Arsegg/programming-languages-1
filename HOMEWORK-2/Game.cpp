#include <iostream>
#include "Game.h"

const int Game::_moves[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

Game::Game(const Array<Cell> &cells) : _cells(cells) {
    _births = 0;
    _deaths = 0;
    for (int i = 0; i < _cells.size(); i++) {
        const int x = _cells[i].x;
        const int y = _cells[i].y;
        const bool alive = _cells[i].alive;
        if (alive) {
            _board.set(x, y, true);
            _births++;
        } else {
            _deaths++;
        }
    }
}

// do cycle of game
void Game::tick() {
    Array<Cell> newCells;
    for (int i = 0; i < _cells.size(); i++) {
        const int x = _cells[i].x;
        const int y = _cells[i].y;
        const bool alive = _cells[i].alive;
        if (!alive) {
            continue;
        }
        newCells.append(Cell(x, y, true));
        for (int i = 0; i < 8; i++) {
            const int dx = x + _moves[i][0];
            const int dy = y + _moves[i][1];
            const bool newAlive = _board.get(dx, dy);
            const Cell cell(dx, dy, newAlive);
            if (!newCells.contains(cell) && !newAlive) {
                newCells.append(cell);
            }
        }
    }
    Board<bool> newBoard;
    for (int i = 0; i < newCells.size(); i++) {
        const int x = newCells[i].x;
        const int y = newCells[i].y;
        const bool alive = _board.get(x, y);
        int neighbours = 0;
        for (int i = 0; i < 8; i++) {
            if (_board.get(x + _moves[i][0], y + _moves[i][1])) {
                neighbours++;
            }
        }
        if (alive && (neighbours < 2 || neighbours > 3)) {
            newCells[i].alive = false;
        } else if (!alive && neighbours == 3) {
            newCells[i].alive = true;
        }
        if (!newCells[i].alive && alive) {
            _deaths++;
        } else if (newCells[i].alive && !alive) {
            _births++;
        }
        newBoard.set(x, y, newCells[i].alive);
    }
    _board = newBoard;
    _cells = newCells;
}

// show coordinates of board
void Game::show() {
    std::cout << _board.minY() << " " << _board.minX() << " " << _board.maxY() << " " << _board.maxX() << "\n";
}

// show state of board by coordinates
void Game::show(int minX, int minY, int maxX, int maxY) {
    _board.show(minX, minY, maxX, maxY);
}

// get count of births
int Game::births() const {
    return _births;
}

// get count of deaths
int Game::deaths() const {
    return _deaths;
}