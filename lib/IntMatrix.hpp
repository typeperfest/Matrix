// typeperfest 2023
#include <vector>
#include <iostream>
#include <algorithm>

enum class Operation {
    ADDITION,
    SUBSTRACTION,
    MULTIPLICATION
};

class IntMatrix {
    std::vector<std::vector<int>> _data;
    size_t rows, columns;
    // TODO: implement funcion
    int calculateMultipliedMember(const IntMatrix& other, const size_t row, const size_t column);

// Constructors
public:
    IntMatrix() = default;
    explicit IntMatrix(std::vector<std::vector<int>>& rhs); 
    IntMatrix(const IntMatrix& rhs) = default;
    IntMatrix(const IntMatrix&& rhs) noexcept;
    IntMatrix(const size_t rows, const size_t columns) : 
        _data(std::vector<std::vector<int>> ( rows, std::vector<int>(columns) )) {};

// Assignation operators
public:
    IntMatrix& operator = (const IntMatrix& rhs);
    IntMatrix& operator = (const IntMatrix&& rhs) noexcept; 

// Arithmetic operators
public:
    IntMatrix operator + (const IntMatrix& rhs);
    IntMatrix operator - (const IntMatrix& rhs);
    IntMatrix operator * (const IntMatrix& rhs);

    bool operator == (const IntMatrix& rhs) const;
    bool operator != (const IntMatrix& rhs) const;

// Helper functions
public:
    bool isCompatible(const IntMatrix& rhs, const Operation operation) const;
};

IntMatrix::IntMatrix(std::vector<std::vector<int>>& rhs) :_data(std::vector<std::vector<int>>(0)) {
    size_t firstSize = rhs[0].size();
    for (size_t i = 0; i < rhs.size(); ++i) {
        if (rhs[i].size() != firstSize) {
            throw std::runtime_error("matrix does not have rectangle format");
        }
    }
    this->_data = rhs;
    this->columns = firstSize;
    this->rows = rhs.size();
}
 
bool IntMatrix::isCompatible(const IntMatrix& rhs, const Operation operation) const {
    if (operation != Operation::MULTIPLICATION) {
        return this->columns == rhs.columns && this->rows == rhs.rows;
    } else {
        return this->rows == rhs.columns && this->columns == rhs.rows;
    }
}

IntMatrix::IntMatrix(const IntMatrix&& rhs) {
    this->_data = std::move(rhs._data);
    this->rows = rhs.rows;
    this->columns = rhs.columns;
}

IntMatrix& IntMatrix::operator = (const IntMatrix& rhs) {
    _data = rhs._data;
    this->rows = rhs.rows;
    this->rows = rhs.columns;
    return *this;
}

IntMatrix& IntMatrix::operator = (const IntMatrix&& rhs) {
    this->_data = std::move(rhs._data);
    this->rows = rhs.rows;
    this->rows = rhs.columns;
    return *this;
}

IntMatrix IntMatrix::operator + (const IntMatrix& rhs) {
    if (!isCompatible(rhs, Operation::ADDITION)) {
        std::runtime_error("addition operation cannot be performed on unmatching matrixes");
    }
    IntMatrix result(*this);
    for (size_t i = 0; i < result._data.size(); ++i) {
        for (size_t j = 0; j < result._data.size(); ++j) {
            result._data[i][j] += rhs._data[i][j];
        }
    }
    return result;
}

IntMatrix IntMatrix::operator - (const IntMatrix& rhs) {
    if (!isCompatible(rhs, Operation::SUBSTRACTION)) {
        std::runtime_error("substraction operation cannot be performed on unmatching matrixes");
    }
    IntMatrix result(*this);
    for (size_t i = 0; i < result._data.size(); ++i) {
        for (size_t j = 0; j < result._data.size(); ++j) {
            result._data[i][j] -= rhs._data[i][j];
        }
    }
    return result;
}

IntMatrix IntMatrix::operator * (const IntMatrix& rhs) {
    if (!isCompatible(rhs, Operation::MULTIPLICATION)) {
        std::runtime_error("multiplication operation cannot be performed on unmatching matrixes");
    }
    IntMatrix result(this->rows, rhs.columns);
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < rhs.columns; ++j) {
            // TODO: Attach function call to result
            calculateMultipliedMember(i, j);
        }
    }
}
