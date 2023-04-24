// typeperfest 2023
#include <vector>
#include <iostream>

enum Operation {
    ADDITION,
    SUBSTRACTION,
    MULTIPLICATION
};

class IntMatrix {
    std::vector<std::vector<int>> _data;
    size_t rows, columns;

    bool checkCompatibility(IntMatrix& rhs, Operation operation) const;

public:
    IntMatrix() = default;
    explicit IntMatrix(std::vector<std::vector<int>>& rhs); 
    IntMatrix(const IntMatrix& rhs) = default;
    IntMatrix(const IntMatrix&& rhs) noexcept;

public:
    IntMatrix& operator = (const IntMatrix& rhs);
    IntMatrix& operator = (const IntMatrix&& rhs) noexcept; 

public:
    IntMatrix operator + (const IntMatrix& rhs);
    IntMatrix operator - (const IntMatrix& rhs);
    IntMatrix operator * (const IntMatrix& rhs);

    bool operator == (const IntMatrix& rhs) const;
    bool operator != (const IntMatrix& rhs) const;
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

bool IntMatrix::checkCompatibility(IntMatrix& rhs, Operation operation) const {
    if (operation != MULTIPLICATION) {
        if (this->columns != rhs.columns || this->rows != rhs.rows) {
            std::runtime_error("Compatibility violation");
        }
    } else {
        if (this->rows != rhs.columns || this->columns != rhs.rows) {
            std::runtime_error("multiplication operation cannot be performed on unmatching matrixes");
        }
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
    if (this->columns != rhs.columns || this->rows != rhs.rows) {
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
    if (this->columns != rhs.columns || this->rows != rhs.rows) {
        std::runtime_error("substraction operation cannot be performed on unmatching matrixes");
    }
    IntMatrix result(*this);
    if (this->_data.size() != )
    for (size_t i = 0; i < result._data.size(); ++i) {
        for (size_t j = 0; j < result._data.size(); ++j) {
            result._data[i][j] -= rhs._data[i][j];
        }
    }
    return result;
}


IntMatrix IntMatrix::operator * (const IntMatrix& rhs) {

}