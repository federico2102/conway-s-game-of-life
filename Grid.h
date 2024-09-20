#ifndef GRID_H
#define GRID_H

#include "CircularMatrix.h"

template<typename T>
class Grid {
private:
    int width;
    int height;
    CircularMatrix<T> matrix;

public:
    Grid(int w, int h, T defaultValue = '-');
    T getCell(int x, int y) const;
    void setCell(int x, int y, T value);
    int getWidth() const;
    int getHeight() const;
    bool operator==(const Grid &other) const;
    bool allValuesAreEqualTo(T value) const;
};

template<typename T>
Grid<T>::Grid(const int w, const int h, const T defaultValue) : width(w), height(h), matrix(w, h, defaultValue) {}

template<typename T>
T Grid<T>::getCell(const int x,const int y) const {
    return matrix[x][y];
}

template<typename T>
void Grid<T>::setCell(const int x, const int y, const T value) {
    matrix[x][y] = value;
}

template<typename T>
int Grid<T>::getWidth() const { return width; }

template<typename T>
int Grid<T>::getHeight() const { return height; }

template<typename T>
bool Grid<T>::operator==(const Grid &other) const {
    return width == other.width && height == other.height && matrix == other.matrix;
}

template<typename T>
bool Grid<T>::allValuesAreEqualTo(const T value) const {
    return matrix.allValuesAreEqualTo(value);
}

#endif // GRID_H

