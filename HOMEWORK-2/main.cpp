#include <ctime>
#include <iostream>
#include <random>

#include "Game.h"
#include "Util.h"

using namespace std;

int main() {
    srand(time(0));

    int n;
    cout << "Enter count of alive cells: ";
    cin >> n;

    bool isRandom;
    cout << "Enter 1 for random initial position, 0 for custom initial position: ";
    cin >> isRandom;
    int minX;
    int minY;
    int maxX;
    int maxY;
    if (isRandom) {
        cout << "Enter minX, minY, maxX, maxY: ";
        cin >> minX >> minY >> maxX >> maxY;
    }
    Array<Cell> cells(n);
    for (int i = 0; i < n; i++) {
        Cell cell;
        if (isRandom) {
            cell.x = randint(minX, maxX);
            cell.y = randint(minY, maxY);
            cell.alive = true;
        } else {
            cout << "Enter x, y, state of " << i << "th cell: ";
            cin >> cell.x >> cell.y >> cell.alive;
        }
        cells[i] = cell;
    }
    int steps;
    cout << "Enter count of simulation steps: ";
    cin >> steps;

    Game game(cells);
    int births = game.births();
    int deaths = game.deaths();
    bool stable = false;
    int index;
    int alive = births - deaths;
    for (int i = 0; i < steps; i++) {
        game.tick();
        const int newBirths = game.births();
        const int newDeaths = game.deaths();
        const int newAlive = newBirths - newDeaths;
        if (i % 10 == 9) {
            cout << i + 1 << "th step\n";
            cout << newBirths << " total births, " << newDeaths << " total deaths\n";
            cout << newBirths - births << " births, " << newDeaths - deaths << " deaths\n";
            cout << ((double) (newBirths - births) / (newDeaths - deaths)) << " births/deaths ratio\n";
            cout << newAlive << " alive cells\n";
            cout << "\n";
        }
        if (alive != newAlive) {
            stable = false;
        }
        if (!stable && alive == newAlive) {
            stable = true;
            index = i;
        }
        alive = newAlive;
        births = newBirths;
        deaths = newDeaths;
    }
    cout << "Population growth by " << alive << " cells\n";
    if (stable) {
        cout << "Stable state at " << index << "th step\n";
    }
    cout << "Field (minX, minY, maxX, maxY): ";
    game.show();
    cout << "P.S. You can just copy previous values to next query and see all field :)\n\n";
    while (true) {
        int minX;
        int minY;
        int maxX;
        int maxY;
        cout << "Enter minX, minY, maxX, maxY (\"0 0 0 0\" for exit): ";
        cin >> minX >> minY >> maxX >> maxY;
        if (minX == minY && minY == maxX && maxX == maxY && maxY == 0) {
            break;
        }
        game.show(minX, minY, maxX, maxY);
    }
}