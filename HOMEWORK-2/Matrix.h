#ifndef _HOMEWORK_2_MATRIX_H_
#define _HOMEWORK_2_MATRIX_H_

#include <cassert>
#include "Array.h"

// Dynamically expanding matrix
// Matrix a(2, 2);
// Matrix b(2, Array(2));
// a == b == {{0, 0}, {0, 0}};
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


#endif //_HOMEWORK_2_MATRIX_H_
