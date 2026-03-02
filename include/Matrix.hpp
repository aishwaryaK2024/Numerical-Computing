#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

class Matrix {
protected:
    int rows, cols;
    std::vector<std::vector<double>> data;

public:
    Matrix(int r, int c);
    Matrix(const std::string& filename);

    void display() const;
    Matrix createAugmented(const Matrix& right) const;

    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
    Matrix operator/(double scalar) const;
    bool   operator==(const Matrix& m) const;
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    virtual ~Matrix() {}
};

#endif