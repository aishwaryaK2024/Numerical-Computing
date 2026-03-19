#include "../include/LinearSystem.hpp"
using namespace std;
LinearSystem::LinearSystem(const Matrix& m) : Matrix(m) { validateSquare(); }

void LinearSystem::validateSquare() {
    if (cols != rows + 1)
        throw std::runtime_error("Matrix must be augmented (n x n+1)");
}

vector<double> LinearSystem::backSubstitution() {
    vector<double> x(rows);
    for (int i = rows - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < rows; j++) sum += data[i][j] * x[j];
        x[i] = (data[i][cols - 1] - sum) / data[i][i];
    }
    return x;
}

vector<double> LinearSystem::forwardSubstitution(const vector<vector<double>>& L,const vector<double>& b) {
    vector<double> y(rows);
    for (int i = 0; i < rows; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) sum += L[i][j] * y[j];
        y[i] = b[i] - sum;
    }
    return y;
}


void LinearSystem::writeToFile(const string& filename) {
    solve();

    vector<double> sol = getSolution();
    
    ofstream out(filename);
    if (!out) throw runtime_error("Cannot open file: " + filename);
    for (int i = 0; i < (int)sol.size(); i++)
        out << "x[" << i + 1 << "] = " << sol[i] << "\n";
    cout << "Saved to " << filename << "\n";
}