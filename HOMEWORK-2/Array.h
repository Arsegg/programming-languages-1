#ifndef _HOMEWORK_2_ARRAY_H_
#define _HOMEWORK_2_ARRAY_H_

#include <cassert>

// Dynamically expanding array
// The idea is similar to std::vector
// Array a(3);
// a == {0, 0, 0};
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

#endif //_HOMEWORK_2_ARRAY_H_
