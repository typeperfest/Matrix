// typeperfest 2023
#include <vector>
#include <iostream>

namespace matrix {

enum class Operation {
    ADDITION,
    SUBSTRACTION,
    COMPARISON,
    MULTIPLICATION
};

class IntMatrix {
    std::vector<std::vector<int>> _data;
    size_t rows, columns;
    // TODO: implement funcion
private:
    int calculateMultipliedMember(const IntMatrix& other, const size_t row, const size_t column);
    template<Operation operation>
    void SSEperformOperation(const IntMatrix& rhs, const IntMatrix* result);

// Constructors
public:
    IntMatrix() = default;
    explicit IntMatrix(std::vector<std::vector<int>>& rhs);
    explicit IntMatrix(std::initializer_list<std::initializer_list<int>> list);
    // TODO: check if defautt is valid solution here // seems to be not
    IntMatrix(const IntMatrix& rhs) : _data(rhs._data), rows(rhs.rows), columns(rhs.columns) {};
    IntMatrix(const IntMatrix&& rhs) : _data(std::move(rhs._data)), rows(rhs.rows), columns(rhs.columns) {};
    IntMatrix(const size_t rows, const size_t columns) : 
        _data(std::vector<std::vector<int>> ( rows, std::vector<int>(columns) )), rows(rows), columns(columns) {};

// Assignation operators
public:
    IntMatrix& operator = (const IntMatrix& rhs);
    IntMatrix& operator = (IntMatrix&& rhs) noexcept;

// Getters & Setters
public:
    std::vector<int> getRow (size_t index) const;
    std::vector<int> getColumn (size_t index) const;

// Arithmetic operators
public:
    IntMatrix operator + (const IntMatrix& rhs);
    IntMatrix operator - (const IntMatrix& rhs);
    IntMatrix operator * (const IntMatrix& rhs);

    bool operator == (const IntMatrix& rhs) const;
    bool operator != (const IntMatrix& rhs) const;

// Helper functions
public:
    bool isCompatible(const IntMatrix& rhs, Operation operation) const;
    void print(std::ostream& out) const;
};

} // end namespace matrix
