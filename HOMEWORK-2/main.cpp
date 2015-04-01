#include <ctime>
#include <cstdio>
#include <iostream>
#include <cassert>
#include <random>

using namespace std;

template<class T=int>
class Array {
public:
    Array(int size = 0, const T &value = T()) {
        assert(size >= 0);

        _size = size;
        _capacity = size >= 10 ? size : 10;
        _array = new T[_capacity];

        for (int i = 0; i < size; i++) {
            _array[i] = value;
        }
    }

    virtual ~Array() {
        delete[] _array;
    }

    // get count of array elements
    int size() const {
        return _size;
    }

    // resize count of array elements
    int size(int size, const T &value = T()) {
        assert(size >= 0);

        ensureCapacity(size);
        for (int i = _size; i < size; i++) {
            _array[i] = value;
        }
        _size = size;
    }

    // clear array
    void clear() {
        _size = 0;
    }

    // append element to tail of array
    void append(const T &value) {
        ensureCapacity(_size + 1);

        _array[_size++] = value;
    }

    // get element by index
    T &get(int index) {
        assert(index >= 0 && index < _size);

        return _array[index];
    }

    // set element by index
    void set(int index, const T &value = T()) {
        assert(index >= 0 && index < _size);

        _array[index] = value;
    }

    // array contains given element?
    bool contains(const T &value) {
        for (int i = 0; i < _size; i++) {
            if (value == _array[i]) {
                return true;
            }
        }
        return false;
    }

    T &operator[](int index) {
        assert(index >= 0 && index < _size);

        return _array[index];
    }

    Array &operator=(const Array &array) {
        _size = array._size;
        _capacity = array._capacity;
        delete[] _array;
        _array = new T[_capacity];
        for (int i = 0; i < _size; i++) {
            _array[i] = array._array[i];
        }

        return *this;
    }

private:
    int _size;
    int _capacity;
    T *_array;

    void ensureCapacity(int capacity) {
        if (capacity <= _capacity) {
            return;
        }
        int newCapacity = _capacity;
        while (newCapacity < capacity) {
            newCapacity *= 2;
        }
        T *newArray = new T[newCapacity];
        for (int i = 0; i < _size; i++) {
            newArray[i] = _array[i];
        }
        delete[] _array;
        _array = newArray;
        _capacity = newCapacity;
    }
};

template<class T=int>
class Matrix {
public:
    Matrix(int size = 0, const Array<T> &value = Array<T>()) {
        _size = size;
        _capacity = size >= 10 ? size : 10;
        _matrix = new Row[_capacity];
        for (int i = 0; i < size; i++) {
            _matrix[i] = value;
        }
    }

    Matrix(int sizeX, int sizeY, const T &value = T()) : Matrix(sizeX, Row(sizeY, value)) {
    }

    virtual ~Matrix() {
        delete[] _matrix;
    }

    // get count of array elements
    int size() const {
        return _size;
    }

    // resize count of array elements
    int size(int sizeX, int sizeY, const T &value = T()) {
        assert(sizeX >= 0 && sizeY >= 0);

        ensureCapacity(sizeX);
        for (int i = 0; i < _size; i++) {
            _matrix[i].size(sizeY);
        }
        for (int i = _size; i < sizeX; i++) {
            _matrix[i] = Row(sizeY, value);
        }
        _size = sizeX;
    }

    // get element by index
    T &get(int x, int y) {
        assert(x >= 0 && x < _size && y >= 0 && y < _matrix[x].size());

        return _matrix[x][y];
    }

    // set element by index
    void set(int x, int y, const T &value = T()) {
        assert(x >= 0 && x < _size && y >= 0 && y < _matrix[x].size());

        _matrix[x][y] = value;
    }

    Array<T> &operator[](int index) {
        assert(index >= 0 && index < _size);

        return _matrix[index];
    }

    Matrix &operator=(const Matrix &matrix) {
        _size = matrix._size;
        _capacity = matrix._capacity;
        delete[] _matrix;
        _matrix = new Row[_capacity];
        for (int i = 0; i < _size; i++) {
            _matrix[i] = matrix._matrix[i];
        }
    }

    typedef Array<T> Row; // Row is Array<T>

private:
    Row *_matrix;
    int _size;
    int _capacity;

    void ensureCapacity(int capacity) {
        if (capacity <= _capacity) {
            return;
        }
        int newCapacity = _capacity;
        while (newCapacity < capacity) {
            newCapacity *= 2;
        }
        Row *newMatrix = new Row[newCapacity];
        for (int i = 0; i < _size; i++) {
            newMatrix[i] = _matrix[i];
        }
        delete[] _matrix;
        _matrix = newMatrix;
        _capacity = newCapacity;
    }
};

template<class T=int>
class Board {
public:
    // board constains element by index
    bool contains(int x, int y) {
        return x >= _minX && x <= _maxX && y >= _minY && y <= _maxY;
    }

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
                cout << (get(j, i) ? "O" : ".");
            }
            cout << "\n";
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

    int minX() const {
        return _minX;
    }

    int minY() const {
        return _minY;
    }

    int maxX() const {
        return _maxX;
    }

    int maxY() const {
        return _maxY;
    }

private:
    Matrix<T> _lt;        // left-top
    Matrix<T> _rt;        // right-top
    Matrix<T> _lb;        // left-bottom
    Matrix<T> _rb;        // right-bottom
    int _minX = -1;
    int _minY = -1;
    int _maxX = 1;
    int _maxY = 1;

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

class Cell {
public:
    int x;
    int y;
    bool alive;

    Cell(int x, int y, bool alive = true) : x(x), y(y), alive(alive) {
    }

    Cell() : x(0), y(0), alive(false) {
    }

    friend bool operator==(const Cell &cell1, const Cell &cell2) {
        return cell1.x == cell2.x && cell1.y == cell2.y;
    }
};

class Game {
public:
    Game(const Array<Cell> &cells) : _cells(cells) {
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
    void tick() {
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
    void show() {
        cout << _board.minY() << " " << _board.minX() << " " << _board.maxY() << " " << _board.maxX() << "\n";
    }

    // show state of board by coordinates
    void show(int minX, int minY, int maxX, int maxY) {
        _board.show(minX, minY, maxX, maxY);
    }

    // get count of births
    int births() const {
        return _births;
    }

    // get count of deaths
    int deaths() const {
        return _deaths;
    }

private:
    Board<bool> _board;
    Array<Cell> _cells;
    static const int _moves[8][2];
    int _births;
    int _deaths;
};

const int Game::_moves[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

// random integer from l to r inclusive
int randint(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main() {
    srand(time(0));

    clock_t begin = clock();

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

    // "Glider": just uncomment below code.
    /*cells = Array<Cell>();
    cells.append(Cell(1, -1));
    cells.append(Cell(2, -1));
    cells.append(Cell(3, -1));
    cells.append(Cell(3, -2));
    cells.append(Cell(2, -3));*/

    // "Blinker": just uncomment below code.
    /*cells = Array<Cell>();
    cells.append(Cell(1, 1));
    cells.append(Cell(2, 1));
    cells.append(Cell(3, 1));*/


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

    cout << "\nTime passed: " << (double) (clock() - begin) / CLOCKS_PER_SEC
            << " sec\nPress any key...";
    /*cin.clear();
    fflush(stdin);
    getchar();*/
}