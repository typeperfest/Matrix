// typeperfest 2023
#include <vector>
#include <iostream>

class IntMatrix {
    std::vector<std::vector<int>> _data;

public:
    IntMatrix() = default;
    explicit IntMatrix(std::vector<std::vector<int>>& rhs) : _data(rhs) {}; 
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
    IntMatrix result(*this);
    for (int i = 0; i < result._data.size(); ++i) {
        for (int j = 0; j < result._data.size(); ++j) {
            result._data[i][j] += rhs._data[i][j];
        }
    }
    return result;
}

IntMatrix IntMatrix::operator - (const IntMatrix& rhs) {
    IntMatrix result(*this);
    for (int i = 0; i < result._data.size(); ++i) {
        for (int j = 0; j < result._data.size(); ++j) {
            result._data[i][j] -= rhs._data[i][j];
        }
    }
    return result;
}

IntMatrix IntMatrix::operator * (const IntMatrix& rhs) {

}
