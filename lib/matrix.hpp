// typeperfest 2023
#include <vector>
#include <iostream>

template <typename T>
class Matrix {
    std::vector<std::vector<T>> _data;
    size_t _rows, _columns;

public:
    Matrix();
    explicit Matrix(std::vector<std::vector<T>> rhs);
    Matrix(const Matrix<T>& rhs);

public:
    Matrix<T> operator + (const Matrix<T>& rhs);
    Matrix<T> operator - (const Matrix<T>& rhs);
    Matrix<T> operator * (const Matrix<T>& rhs);

    bool operator == (const Matrix<T> rhs) const;
    bool operator != (const Matrix<T> rhs) const;
};

template <typename T>
Matrix<T>::Matrix() {
    
}