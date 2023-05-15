// typeperfest 2023
#include <vector>
#include <iostream>
#include <algorithm>

#define SIMD_EXTENSION_ENABLED

enum class Operation {
    ADDITION,
    SUBSTRACTION,
    COMPARISON,
    MULTIPLICATION
};

namespace matrix {

class IntMatrix {
    std::vector<std::vector<int>> _data;
    size_t rows, columns;
    // TODO: implement funcion
    int calculateMultipliedMember(const IntMatrix& other, const size_t row, const size_t column);

// Constructors
public:
    IntMatrix() = default;
    explicit IntMatrix(std::vector<std::vector<int>>& rhs);
    explicit IntMatrix(std::initializer_list<std::initializer_list<int>> list);
    // TODO: check if defautt is valid solution here // seems to be not
    IntMatrix(const IntMatrix& rhs) : _data(rhs._data), columns(rhs.columns), rows(rhs.rows) {};
    IntMatrix(const IntMatrix&& rhs) noexcept;
    IntMatrix(const size_t rows, const size_t columns) : 
        _data(std::vector<std::vector<int>> ( rows, std::vector<int>(columns) )), columns(columns), rows(rows) {};

// Assignation operators
public:
    IntMatrix& operator = (const IntMatrix& rhs);
    IntMatrix& operator = (const IntMatrix&& rhs) noexcept;

// Getters & Setters
public:
    std::vector<int> getRow (const size_t index) const;
    std::vector<int> getColumn (const size_t index) const;

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
    bool print(std::ostream& out) const;
};

} // end namespace matrix
