// typeperfest 2023
#include <vector>
#include <iostream>

class IntMatrix {
    std::vector<std::vector<int>> _data;
    size_t rows, columns;

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

// TODO: implement every vector size comparison
IntMatrix::IntMatrix(std::vector<std::vector<int>>& rhs) {

}

IntMatrix::IntMatrix(const IntMatrix&& rhs) {
    this->_data = std::move(rhs._data);
}

IntMatrix& IntMatrix::operator = (const IntMatrix& rhs) {
    _data = rhs._data;
    return *this;
}

IntMatrix& IntMatrix::operator = (const IntMatrix&& rhs) {
    this->_data = std::move(rhs._data);
    return *this;
}

IntMatrix IntMatrix::operator + (const IntMatrix& rhs) {
    // TODO: add size complatibility
    IntMatrix result(*this);
    for (size_t i = 0; i < result._data.size(); ++i) {
        for (size_t j = 0; j < result._data.size(); ++j) {
            result._data[i][j] += rhs._data[i][j];
        }
    }
    return result;
}

IntMatrix IntMatrix::operator - (const IntMatrix& rhs) {
    // TODO: add size complatibility
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