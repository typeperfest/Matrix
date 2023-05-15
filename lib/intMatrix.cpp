#include "IntMatrix.h"

#ifdef SIMD_EXTENSION_ENABLED
    #include "immintrin.h"
#endif

using namespace matrix;

IntMatrix::IntMatrix(std::vector<std::vector<int>>& rhs) : _data(std::vector<std::vector<int>>(rhs.size(),
                                                                 std::vector<int>(rhs.front().size()))) {
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
        _data.emplace_back(l);
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

IntMatrix& IntMatrix::operator = (const IntMatrix& rhs) {
    _data = rhs._data;
    this->rows = rhs.rows;
    this->columns = rhs.columns;
    return *this;
}

IntMatrix& IntMatrix::operator = (IntMatrix&& rhs) noexcept {
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
    for (size_t i = 0; i < result._data.size(); ++i) {
#ifndef SIMD_EXTENSION_ENABLED
        for (size_t j = 0; j < result._data.front().size(); ++j) {
            result._data[i][j] += rhs._data[i][j];
        }
#else  
        // according to suffix 'u'
        // >> mem_addr does not need to be aligned on any particular boundary
        // Was Intel meant data should be aligned? 
        __attribute__((aligned(16))) __m128i* currPackedLhsPtr = (__m128i*)this->_data[i].data();
        __attribute__((aligned(16))) __m128i* currPackedRhsPtr = (__m128i*)rhs._data[i].data();
        __attribute__((aligned(16))) __m128i* currPackedResultPtr = (__m128i*)result._data[i].data(); 
        for (size_t j = 0; j < result._data.front().size() >> 2; j += 4) {
            __m128i rhsPack = _mm_lddqu_si128(currPackedRhsPtr);
            __m128i lhsPack = _mm_lddqu_si128(currPackedLhsPtr);
            __m128i resPack = _mm_add_epi32(rhsPack, lhsPack);
            _mm_storeu_si128(currPackedResultPtr, resPack);
            currPackedLhsPtr += 4;
            currPackedRhsPtr += 4;
            currPackedResultPtr += 4;
        }
        __m128i rhsPack = _mm_lddqu_si128(currPackedRhsPtr);
        __m128i lhsPack = _mm_lddqu_si128(currPackedLhsPtr);
        __m128i resPack = _mm_add_epi32(rhsPack, lhsPack);
        // for (size_t j = 0; j < (result._data.front().size() & 0x3); ++j) {
        //     _mm_storeu_si32(currPackedResultPtr, resPack);
        //     resPack >>= 32;
        //     currPackedResultPtr += 4;
        // }
#endif
    }
    return result;
}

IntMatrix IntMatrix::operator - (const IntMatrix& rhs) {
    if (!isCompatible(rhs, Operation::SUBSTRACTION)) {
        std::runtime_error("matrixes are not compatible");
    }
    IntMatrix result(*this);
#ifndef SIMD_EXTENSION_ENABLED
    for (size_t i = 0; i < result._data.size(); ++i) {
        for (size_t j = 0; j < result._data.front().size(); ++j) {
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

void IntMatrix::print(std::ostream& out) const {
    out << '[' << std::endl;
    out << "rows " << this->rows << std::endl;
    out << "columns " << this->columns << std::endl;
    for (size_t i = 0; i < this->_data.size(); ++i) {
        out << "\t[";
        out << this->_data[i].front();
        for (size_t j = 1; j < this->_data[i].size(); ++j) {
            out << ' ' << this->_data[i][j];
        }
        out << ']' << std::endl;
    }
    out << ']' << std::endl;
}
