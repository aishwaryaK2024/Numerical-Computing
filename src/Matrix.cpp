#include "matrix.hpp"

Matrix::Matrix(int rows, int cols) {
    this->rows = rows;   
    this->cols = cols;  

    data.resize(rows, vector<double>(cols));
}


void Matrix::read() {
    cout << "Enter elements:\n";
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            cin >> data[i][j];
}


void Matrix::display() const {
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++)
            cout << data[i][j] << " ";
        cout << endl;
    }
}


Matrix Matrix::add(const Matrix &m) const {
    Matrix result(rows, cols);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] + m.data[i][j];

    return result;
}


Matrix Matrix::subtract(const Matrix &m) const {
    Matrix result(rows, cols);

    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] - m.data[i][j];

    return result;
}


void Matrix::info() {
    cout << "This is Matrix class\n";
}



GEMatrix::GEMatrix(int rows, int cols)
    : Matrix(rows, cols) {}


void GEMatrix::gaussianElimination() {

    for(int k = 0; k < rows - 1; k++) {
        for(int i = k + 1; i < rows; i++) {

            double factor = data[i][k] / data[k][k];

            for(int j = k; j < cols; j++)
                data[i][j] -= factor * data[k][j];
        }
    }
}

void GEMatrix::info() {
    cout << "This is GEMatrix (Gaussian Elimination Matrix)\n";
}
