#include "../include/GaussianElimination.hpp"
#include <cmath>

GaussianElimination::GaussianElimination(const Matrix& m, bool pivot)
    : LinearSystem(m), usePivot(pivot) {}

void GaussianElimination::solve() {
    for (int k = 0; k < rows - 1; k++) {
        if (usePivot) {
            int maxRow = k;
            for (int i = k + 1; i < rows; i++)
                if (std::abs(data[i][k]) > std::abs(data[maxRow][k])) maxRow = i;
            std::swap(data[k], data[maxRow]);
        }
        if (data[k][k] == 0) throw std::runtime_error("Zero pivot");
        for (int i = k + 1; i < rows; i++) {
            double factor = data[i][k] / data[k][k];
            for (int j = k; j < cols; j++)
                data[i][j] -= factor * data[k][j];
        }
    }
    solution = backSubstitution();   
}

std::vector<double> GaussianElimination::getSolution() { return solution; }