#include "IntMatrix.h"

#ifdef SIMD_EXTENSION_ENABLED
    #include "immintrin.h"
#endif

using namespace matrix;

IntMatrix::IntMatrix(std::vector<std::vector<int>>& rhs) : _data(std::vector<std::vector<int>>(0)) {
    size_t firstSize = rhs[0].size();
    for (size_t i = 0; i < rhs.size(); ++i) {
        if (rhs[i].size() != firstSize) {
            throw std::runtime_error("matrix does not fit rectangle format");
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
    size_t rowsCount = 0;
    for (auto& l : listLists) {
        _data.push_back(l);
        ++rowsCount;
    }
    this->columns = firstSize;
    this->rows = rowsCount;
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
    this->columns = rhs.columns;
    return *this;
}

IntMatrix& IntMatrix::operator = (const IntMatrix&& rhs) noexcept {
    this->_data = std::move(rhs._data);
    this->rows = rhs.rows;
    this->columns = rhs.columns;
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
#ifndef SIMD_EXTENSION_ENABLED
    for (size_t i = 0; i < result._data.size(); ++i) {
        for (size_t j = 0; j < result._data.size(); ++j) {
            result._data[i][j] += rhs._data[i][j];
        }
    }
#else
    // emplement here
#endif
    return result;
}

IntMatrix IntMatrix::operator - (const IntMatrix& rhs) {
    if (!isCompatible(rhs, Operation::SUBSTRACTION)) {
        std::runtime_error("matrixes are not compatible");
    }
    IntMatrix result(*this);
#ifndef SIMD_EXTENSION_ENABLED
    for (size_t i = 0; i < result._data.size(); ++i) {
        for (size_t j = 0; j < result._data[i].size(); ++j) {
            result._data[i][j] -= rhs._data[i][j];
        }
    }
#else
    // implement here
#endif
    return result;
}

IntMatrix IntMatrix::operator * (const IntMatrix& rhs) {
    if (!isCompatible(rhs, Operation::MULTIPLICATION)) {
        std::runtime_error("matrixes are not compatible");
    }
    IntMatrix result(this->rows, rhs.columns);
#ifndef SIMD_EXTENSION_ENABLED
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < rhs.columns; ++j) {
            // TODO: Attach function call to result
            auto multiplicationResultMember = calculateMultipliedMember(rhs, i, j);
            result._data[i][j] = multiplicationResultMember;
        }
    }
#else 
    // implement here
#endif
    return result;
}

int IntMatrix::calculateMultipliedMember(const IntMatrix& other, const size_t row, const size_t column) {
    int result = 0;
    if (this->rows != other.columns) {
        throw std::runtime_error("calculator error");
    }
    for (size_t i = 0; i < this->columns; ++i) {
        result += this->_data[row][i] * other._data[i][column];
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

bool IntMatrix::print(std::ostream& out) const {
    out << '[' << std::endl;
    out << "rows " << this->rows << std::endl;
    out << "columns " << this->columns << std::endl;
    for (size_t i = 0; i < this->_data.size(); ++i) {
        out << "\t[";
        out << this->_data.front().front();
        for (size_t j = 1; j < this->_data[i].size(); ++j) {
            out << ' ' << this->_data[i][j];
        }
        out << ']' << std::endl;
    }
    out << ']' << std::endl;
}
