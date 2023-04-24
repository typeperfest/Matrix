// typeperfest 2023
#include <vector>
#include <iostream>

class IntMatrix {
    std::vector<std::vector<int>> _data;
    size_t _rows, _columns;

public:
    IntMatrix();
    explicit IntMatrix(std::vector<std::vector<int>>& rhs); 
    IntMatrix(const IntMatrix& rhs);
    IntMatrix(const IntMatrix&& rhs);

public:
    IntMatrix& operator = (const IntMatrix& rhs);
    IntMatrix& operator = (const IntMatrix&& rhs); 

public:
    IntMatrix operator + (const IntMatrix& rhs);
    IntMatrix operator - (const IntMatrix& rhs);
    IntMatrix operator * (const IntMatrix& rhs);

    bool operator == (const IntMatrix& rhs) const;
    bool operator != (const IntMatrix& rhs) const;
};

IntMatrix::IntMatrix() {

}

IntMatrix::IntMatrix(std::vector<std::vector<int>>& rhs) {

}

IntMatrix::IntMatrix(const IntMatrix& rhs) {

}

IntMatrix::IntMatrix(const IntMatrix&& rhs) {

}

IntMatrix& IntMatrix::operator = (const IntMatrix& rhs) {

}

IntMatrix& IntMatrix::operator = (const IntMatrix&& rhs) {

}

IntMatrix IntMatrix::operator + (const IntMatrix& rhs) {

}

IntMatrix IntMatrix::operator - (const IntMatrix& rhs) {

}

IntMatrix IntMatrix::operator * (const IntMatrix& rhs) {

}
