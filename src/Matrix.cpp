#include "Matrix.hpp"

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(rows, vector<double>(cols));
}

void Matrix::read() {
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            cin >> data[i][j];
}

void Matrix::display() const {
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++)
            cout << data[i][j] << " ";
        cout << endl;
    }
}

Matrix Matrix::add(const Matrix &m) const {
    Matrix result(rows, cols);
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            result.data[i][j] = data[i][j] + m.data[i][j];
    return result;
}

Matrix Matrix::subtract(const Matrix &m) const {
    Matrix result(rows, cols);
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            result.data[i][j] = data[i][j] - m.data[i][j];
    return result;
}

void Matrix::info() {
    cout << "Base Matrix Class\n";
}

GEMatrix::GEMatrix(int r, int c) : Matrix(r,c) {}

void GEMatrix::gaussianElimination() {
    for(int k=0;k<rows-1;k++){
        for(int i=k+1;i<rows;i++){
            double factor = data[i][k] / data[k][k];
            for(int j=k;j<cols;j++)
                data[i][j] -= factor * data[k][j];
        }
    }
}


vector<double> GEMatrix::backSubstitution() {
    vector<double> x(rows);

    for(int i=rows-1;i>=0;i--){
        x[i] = data[i][cols-1];
        for(int j=i+1;j<rows;j++)
            x[i] -= data[i][j] * x[j];

        x[i] /= data[i][i];
    }

    return x;
}

void GEMatrix::info() {
    cout << "Gaussian Elimination Matrix\n";
}