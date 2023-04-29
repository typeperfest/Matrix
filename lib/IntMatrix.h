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
    // TODO: check if defautt is valid solution here
    IntMatrix(const IntMatrix& rhs) = default;
    IntMatrix(const IntMatrix&& rhs) noexcept;
    IntMatrix(const size_t rows, const size_t columns) : 
        _data(std::vector<std::vector<int>> ( rows, std::vector<int>(columns) )) {};

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
};
