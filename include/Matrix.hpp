#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
using namespace std;

class Matrix {
protected:
    int rows, cols;
    vector<vector<double>> data;

public:
    Matrix(int r, int c);
    Matrix(const string& filename);

    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
    Matrix operator/(double scalar)   const;
    bool   operator==(const Matrix& m) const;

    double& operator()(int r, int c);
    double  operator()(int r, int c) const;

    bool isSquare() const;
    bool isSymmetric() const;
    bool isIdentity() const;
    bool isNull() const;
    bool isDiagonal() const;
    bool isDiagonalDominant() const;
    bool isTransposeOf(const Matrix& m) const;

    Matrix transpose() const;
    double determinant() const;
    Matrix inverse() const;
    Matrix createAugmented(const Matrix& right) const;
    bool   makeDiagonalDominant();   

    friend ostream& operator<<(ostream& os, const Matrix& m);
    friend istream& operator>>(istream& is,Matrix& m);

    virtual ~Matrix() {}

private:
    double det(vector<vector<double>> mat, int n) const;
};

#endif