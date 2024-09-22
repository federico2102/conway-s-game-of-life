#ifndef CIRCULARMATRIX_MAP_H
#define CIRCULARMATRIX_MAP_H

#include <map>
#include <stdexcept>

template<typename T>
class CircularMatrix {
    int width, height;
    std::map<int, std::map<int, T>> matrix;
    const T defaultValue;

public:
    CircularMatrix(int w, int h, T value);

    class CircularRow {
        std::map<int, T>& row;
        const std::map<int, T>& constRow;
        int height;
        const T& defaultValue; // Store a reference to the default value

    public:
        CircularRow(std::map<int, T>& r, int h, const T& defaultVal);
        CircularRow(const std::map<int, T>& r, int h, const T& defaultVal);

        T& operator[](int j);
        const T& operator[](int j) const;
    };

    CircularRow operator[](int i);
    CircularRow operator[](int i) const;

    bool allValuesAreEqualTo(T value) const;
    bool operator==(const CircularMatrix &other) const;
};

// Constructor
template<typename T>
CircularMatrix<T>::CircularMatrix(int w, int h, T value)
    : width(w), height(h), defaultValue(value) {
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Grid dimensions must be greater than zero.");
    }
}

// Non-const access
template<typename T>
typename CircularMatrix<T>::CircularRow CircularMatrix<T>::operator[](int i) {
    i = (i % width + width) % width; // Circular access
    return CircularRow(matrix[i], height, defaultValue); // Pass defaultValue
}

// Const access
template<typename T>
typename CircularMatrix<T>::CircularRow CircularMatrix<T>::operator[](int i) const {
    i = (i % width + width) % width; // Circular access
    auto it = matrix.find(i);
    if (it != matrix.end()) {
        return CircularRow(it->second, height, defaultValue);
    }
    return CircularRow(std::map<int, T>(), height, defaultValue); // Return empty or default row
}

// Constructor for non-const row
template<typename T>
CircularMatrix<T>::CircularRow::CircularRow(std::map<int, T>& r, int h, const T& defaultVal)
    : row(r), constRow(r), height(h), defaultValue(defaultVal) {}

// Constructor for const row
template<typename T>
CircularMatrix<T>::CircularRow::CircularRow(const std::map<int, T>& r, int h, const T& defaultVal)
    : row(const_cast<std::map<int, T>&>(r)), constRow(r), height(h), defaultValue(defaultVal) {}

// Non-const operator[]
template<typename T>
T& CircularMatrix<T>::CircularRow::operator[](int j) {
    j = (j % height + height) % height; // Circular access
    if (!row.contains(j)) {
        row[j] = defaultValue; // Initialize with default value
    }
    return row[j];
}

// Const operator[]
template<typename T>
const T& CircularMatrix<T>::CircularRow::operator[](int j) const {
    j = (j % height + height) % height; // Circular access
    if (!constRow.contains(j)) {
        return defaultValue; // Return default value if element not present
    }
    return constRow.at(j);
}

// Check if all values are equal to a specific value
template<typename T>
bool CircularMatrix<T>::allValuesAreEqualTo(T value) const {
    for (const auto& row : matrix) {
        for (const auto& col : row.second) {
            if (col.second != value) return false;
        }
    }
    return true;
}

// Equality comparison operator
template<typename T>
bool CircularMatrix<T>::operator==(const CircularMatrix &other) const {
    return width == other.width && height == other.height && matrix == other.matrix;
}

#endif // CIRCULARMATRIX_MAP_H
