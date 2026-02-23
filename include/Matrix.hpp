#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
using namespace std;

class Matrix {
protected:
    int rows, cols;
    vector<vector<double>> data;

public:
    Matrix(int r, int c);

    void read();
    void display() const;

    Matrix add(const Matrix &m) const;
    Matrix subtract(const Matrix &m) const;

    virtual void info();
};

class GEMatrix : public Matrix {
public:
    GEMatrix(int r, int c);

    void gaussianElimination();
    vector<double> backSubstitution();
    void info() override;
};

#endif