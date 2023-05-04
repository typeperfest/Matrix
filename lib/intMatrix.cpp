#include "IntMatrix.h"

IntMatrix::IntMatrix(std::vector<std::vector<int>>& rhs) : _data(std::vector<std::vector<int>>(0)) {
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

IntMatrix::IntMatrix(std::initializer_list<std::initializer_list<int>> listLists) {
    size_t firstSize = listLists.begin()->size();
    for (auto& l : listLists) {
        if (l.size() != firstSize) {
            throw std::runtime_error("matrix does not fit rectangle format");
        }
    }
    for (auto& l : listLists) {
        _data.push_back(l);
    }
}
 
bool IntMatrix::isCompatible(const IntMatrix& rhs, const Operation operation) const {
    if (operation != Operation::MULTIPLICATION) {
        return this->columns == rhs.columns && this->rows == rhs.rows;
    } else {
        return this->rows == rhs.columns && this->columns == rhs.rows;
    }
}

IntMatrix::IntMatrix(const IntMatrix&& rhs) noexcept {
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

IntMatrix& IntMatrix::operator = (const IntMatrix&& rhs) noexcept {
    this->_data = std::move(rhs._data);
    this->rows = rhs.rows;
    this->rows = rhs.columns;
    return *this;
}

std::vector<int> IntMatrix::getRow(const size_t index) const {
    return _data[index];
} 

std::vector<int> IntMatrix::getColumn(const size_t index) const {
    std::vector<int> result(this->rows);
    for (int i = 0; i < this->rows; ++i) {
        result[i] = _data[i][index];
    }
    return result;
}

IntMatrix IntMatrix::operator + (const IntMatrix& rhs) {
    if (!isCompatible(rhs, Operation::ADDITION)) {
        std::runtime_error("matrixes are not compatible");
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
        std::runtime_error("matrixes are not compatible");
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
        std::runtime_error("matrixes are not compatible");
    }
    IntMatrix result(this->rows, rhs.columns);
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < rhs.columns; ++j) {
            // TODO: Attach function call to result
            auto multiplicationResultMember = calculateMultipliedMember(rhs, i, j);
            result._data[i][j] = multiplicationResultMember;
        }
    }
    return result;
}

int IntMatrix::calculateMultipliedMember(const IntMatrix& other, const size_t row, const size_t column) {
    int result = 0;
    for (size_t i = 0; i < row; ++i) {
        result += this->_data[row][i] * other._data[column][i];
    }
    return result;
}

bool IntMatrix::operator == (const IntMatrix& rhs) const {
    if (!isCompatible(rhs, Operation::COMPARISON)) {
        throw std::runtime_error("matrixes are not compatible");
    }
    return this->_data == rhs._data;
}

bool IntMatrix::operator != (const IntMatrix& rhs) const {
    if (!isCompatible(rhs, Operation::COMPARISON)) {
        throw std::runtime_error("matrixes are not compatible");
    }
    return this->_data != rhs._data;
}
