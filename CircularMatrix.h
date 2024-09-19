

#ifndef CIRCULARMATRIX_H
#define CIRCULARMATRIX_H
#include <vector>
#include <stdexcept>

template<typename T>
class CircularMatrix {
    int width, height;
    std::vector<std::vector<T>> matrix;

    // MatrixRow class to handle column access and wrap-around for columns
    class MatrixRow {
    private:
        std::vector<T>& row;
        const std::vector<T>& constRow;
        int height;

    public:
        MatrixRow(std::vector<T>& r, int h);
        MatrixRow(const std::vector<T>& r, int h);

        // Overload operator[] for column access with circular indexing
        T& operator[](int j);
        const T& operator[](int j) const;
    };

public:
    CircularMatrix(const CircularMatrix &other);
    CircularMatrix(int w, int h, T value);
    MatrixRow operator[](int i);
    MatrixRow operator[](int i) const;
    bool allValuesAreEqualTo(T value) const;
    bool operator==(const CircularMatrix &other) const;
};

template<typename T>
CircularMatrix<T>::CircularMatrix(const CircularMatrix<T> &other) {
    height = other.height;
    width = other.width;
    matrix = other.matrix;
}

template<typename T>
CircularMatrix<T>::CircularMatrix(const int w, const int h, T value) : width(w), height(h) {
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Grid dimensions must be greater than zero.");
    }
    matrix = std::vector(width, std::vector(height, value));
}

template<typename T>
CircularMatrix<T>::MatrixRow::MatrixRow(std::vector<T>& r, const int h) : row(r), constRow(r), height(h) {}

template<typename T>
CircularMatrix<T>::MatrixRow::MatrixRow(const std::vector<T>& r, const int h) : row(const_cast<std::vector<T>&>(r)),
constRow(r), height(h) {}

template<typename T>
T& CircularMatrix<T>::MatrixRow::operator[](int j) {
    // Ensure the column index wraps around circularly
    j = j % height;
    if (j < 0) j += height;  // Handle negative indices
    return row[j];
}

template<typename T>
const T& CircularMatrix<T>::MatrixRow::operator[](int j) const {
    // Ensure the column index wraps around circularly
    j = j % height;
    if (j < 0) j += height;  // Handle negative indices
    return constRow[j];
}

template<typename T>
typename CircularMatrix<T>::MatrixRow CircularMatrix<T>::operator[](int i) {
    i = i % width;
    if (i < 0) i += width;  // Handle negative indices
    return MatrixRow(matrix[i], height);
}

template<typename T>
typename CircularMatrix<T>::MatrixRow CircularMatrix<T>::operator[](int i) const {
    i = i % width;
    if (i < 0) i += width;  // Handle negative indices
    return MatrixRow(matrix[i], height);
}

template<typename T>
bool CircularMatrix<T>::operator==(const CircularMatrix &other) const {
    if (width != other.width || height != other.height) {
        return false;
    } else {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (matrix[i][j] != other.matrix[i][j]) return false;
            }
        }
    }
    return true;
}

template<typename T>
bool CircularMatrix<T>::allValuesAreEqualTo(T value) const {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (matrix[i][j] != value) return false;
        }
    }
    return true;
}




#endif //CIRCULARMATRIX_H
