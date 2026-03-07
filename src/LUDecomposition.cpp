#include "../include/LUDecomposition.hpp"

LUDecomposition::LUDecomposition(const Matrix& m) : LinearSystem(m) {
    L.assign(rows, std::vector<double>(rows, 0));
    U.assign(rows, std::vector<double>(rows, 0));
}


Doolittle::Doolittle(const Matrix& m) : LUDecomposition(m) {}

void Doolittle::decompose() {
    for (int i = 0; i < rows; i++) {

        L[i][i] = 1;
        for (int j = i; j < rows; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++)
                sum += L[i][k] * U[k][j];
            U[i][j] = data[i][j] - sum;
        }

        for (int j = i + 1; j < rows; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++)
                sum += L[j][k] * U[k][i];
            if (U[i][i] == 0)
                throw std::runtime_error("Zero pivot in Doolittle");
            L[j][i] = (data[j][i] - sum) / U[i][i];
        }
    }
}

void Doolittle::solve() {
    decompose();

    std::vector<double> b(rows);
    for (int i = 0; i < rows; i++)
        b[i] = data[i][cols - 1];

    std::vector<double> y = forwardSubstitution(L, b);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++)
            data[i][j] = U[i][j];
        data[i][cols - 1] = y[i];
    }

    solution = backSubstitution();
}

std::vector<double> Doolittle::getSolution() { return solution; }



Crout::Crout(const Matrix& m) : LUDecomposition(m) {}

void Crout::decompose() {
    for (int i = 0; i < rows; i++) {

        
        U[i][i] = 1;

        for (int j = i; j < rows; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++)
                sum += L[j][k] * U[k][i];
            L[j][i] = data[j][i] - sum;
        }

        for (int j = i + 1; j < rows; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++)
                sum += L[i][k] * U[k][j];
            if (L[i][i] == 0)
                throw std::runtime_error("Zero pivot in Crout");
            U[i][j] = (data[i][j] - sum) / L[i][i];
        }
    }
}

void Crout::solve() {
    decompose();

    std::vector<double> b(rows);
    for (int i = 0; i < rows; i++)
        b[i] = data[i][cols - 1];

    std::vector<double> y = forwardSubstitution(L, b);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++)
            data[i][j] = U[i][j];
        data[i][cols - 1] = y[i];
    }

    solution = backSubstitution();
}

std::vector<double> Crout::getSolution() { return solution; }


Cholesky::Cholesky(const Matrix& m) : LUDecomposition(m) {}

bool Cholesky::isSymmetric() {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            if (data[i][j] != data[j][i])
                return false;
    return true;
}

void Cholesky::decompose() {
    if (!isSymmetric())
        throw std::runtime_error("Matrix must be symmetric for Cholesky");

    for (int i = 0; i < rows; i++) {

     
        double sum = 0;
        for (int k = 0; k < i; k++)
            sum += L[i][k] * L[i][k];

        double val = data[i][i] - sum;
        if (val <= 0)
            throw std::runtime_error("Matrix must be positive definite for Cholesky");

        L[i][i] = std::sqrt(val);

        for (int j = i + 1; j < rows; j++) {
            double sum2 = 0;
            for (int k = 0; k < i; k++)
                sum2 += L[j][k] * L[i][k];
            L[j][i] = (data[j][i] - sum2) / L[i][i];
        }
    }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < rows; j++)
            U[i][j] = L[j][i];
}

void Cholesky::solve() {
    decompose();

    std::vector<double> b(rows);
    for (int i = 0; i < rows; i++)
        b[i] = data[i][cols - 1];

    
    std::vector<double> y = forwardSubstitution(L, b);


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++)
            data[i][j] = U[i][j];
        data[i][cols - 1] = y[i];
    }

    solution = backSubstitution();
}

std::vector<double> Cholesky::getSolution() { return solution; }