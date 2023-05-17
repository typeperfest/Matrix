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

template<bool isComplementOfTwo>
void matrix::IntMatrix::addMatrixByMembersCode(const IntMatrix& rhs, const IntMatrix* result) {
    // according to suffix 'u'
    // >> mem_addr does not need to be aligned on any particular boundary
    // Was Intel meant data does not need to be aligned? 
    for (size_t i = 0; i < result->_data.size(); ++i) {
        auto currLhsDataPtr = this->_data[i].data();
        auto currRhsDataPtr = rhs._data[i].data();
        auto currResultDataPtr = result->_data[i].data(); 
        __m128i* currPackedLhsPtr = (__m128i*)currLhsDataPtr;
        __m128i* currPackedRhsPtr = (__m128i*)currRhsDataPtr;
        __m128i* currPackedResultPtr = (__m128i*)currResultDataPtr; 
        __m128i rhsPack = _mm_lddqu_si128(currPackedRhsPtr);
        __m128i lhsPack = _mm_lddqu_si128(currPackedLhsPtr);
        __m128i resPack;
        for (size_t j = 0; j < result->_data.front().size() >> 2; ++j) {
            if constexpr (isComplementOfTwo) {
                resPack = _mm_sub_epi32(lhsPack, rhsPack);
            } else {
                resPack = _mm_add_epi32(rhsPack, lhsPack);
            }
            _mm_storeu_si128(currPackedResultPtr, resPack);
            currLhsDataPtr += sizeof(__m128i) / sizeof(int); // 4
            currRhsDataPtr += sizeof(__m128i) / sizeof(int);
            currResultDataPtr += sizeof(__m128i) / sizeof(int);
            currPackedLhsPtr = (__m128i*)currLhsDataPtr;
            currPackedRhsPtr = (__m128i*)currRhsDataPtr;
            currPackedResultPtr = (__m128i*)currResultDataPtr; 
            rhsPack = _mm_lddqu_si128(currPackedRhsPtr);
            lhsPack = _mm_lddqu_si128(currPackedLhsPtr);
        }
        if constexpr (isComplementOfTwo) {
            resPack = _mm_sub_epi32(lhsPack, rhsPack);
        } else {
            resPack = _mm_add_epi32(rhsPack, lhsPack);
        }
        for (size_t j = 0; j < (result->_data.front().size() % 4); ++j) {
            _mm_storeu_si32((__m128i*)currResultDataPtr, resPack);
            resPack = _mm_bsrli_si128(resPack, sizeof(int));
            currResultDataPtr += 1;
        }
    }
}


IntMatrix IntMatrix::operator + (const IntMatrix& rhs) {
    if (!isCompatible(rhs, Operation::ADDITION)) {
        std::runtime_error("matrixes are not compatible");
    }
    IntMatrix result(*this);
#ifndef SIMD_EXTENSION_ENABLED
    for (size_t i = 0; i < result._data.size(); ++i) {
        for (size_t j = 0; j < result._data.front().size(); ++j) {
            result._data[i][j] += rhs._data[i][j];
        }
    }
#else  
    addMatrixByMembersCode<false>(rhs, &result);
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
        for (size_t j = 0; j < result._data.front().size(); ++j) {
            result._data[i][j] -= rhs._data[i][j];
        }
    }
#else
    addMatrixByMembersCode<true>(rhs, &result);
#endif
    return result;
}

IntMatrix IntMatrix::operator * (const IntMatrix& rhs) {
    if (!isCompatible(rhs, Operation::MULTIPLICATION)) {
        std::runtime_error("matrixes are not compatible");
    }
    IntMatrix result(this->rows, rhs.columns);
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < rhs.columns; ++j) {
            auto multiplicationResultMember = calculateMultipliedMember(rhs, i, j);
            result._data[i][j] = multiplicationResultMember;
        }
    }
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
