#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
using namespace std;

class Matrix {
protected:
    int rows, cols;
    vector<vector<double>> data;

public:
    Matrix(int rows, int cols);

    void read();
    void display() const;

    Matrix add(const Matrix &m) const;
    Matrix subtract(const Matrix &m) const;

    virtual void info();
};


class GEMatrix : public Matrix {
public:
    GEMatrix(int rows, int cols);

    void gaussianElimination();
    void info() override;
};

#endif
