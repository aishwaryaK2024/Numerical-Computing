#include "Matrix.hpp"

int main() {

    int n;
    cout << "Enter number of equations: ";
    cin >> n;

    GEMatrix A(n, n+1);

    cout << "Enter augmented matrix:\n";
    A.read();

    cout << "\nOriginal Matrix:\n";
    A.display();

    A.gaussianElimination();

    cout << "\nUpper Triangular Matrix:\n";
    A.display();

    vector<double> solution = A.backSubstitution();

    cout << "\nSolution:\n";
    for(int i=0;i<n;i++)
        cout << "x" << i+1 << " = " << solution[i] << endl;

    return 0;
}