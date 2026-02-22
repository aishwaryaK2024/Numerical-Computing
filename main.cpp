#include "matrix.hpp"

int main() {

    int r, c;
    cout << "Enter rows and cols: ";
    cin >> r >> c;

    GEMatrix A(r, c);
    GEMatrix B(r, c);

    cout << "Matrix A:\n";
    A.read();


    cout << "Matrix B:\n";
    B.read();

    cout << "\nAddition:\n";
    Matrix C = A.add(B);
    C.display();

    cout << "\nSubtraction:\n";
    Matrix D = A.subtract(B);
    D.display();

    cout << "\nGaussian Elimination of A:\n";
    A.gaussianElimination();
    A.display();

   

    return 0;
}
