#ifndef LU_H
#define LU_H
using namespace std;
#include "LinearSystem.hpp"

class LUDecomposition : public LinearSystem {
    vector<std::vector<double>> L, U;
    vector<double> solution;

public:
    LUDecomposition(const Matrix& m);
    void solve() override;
    vector<double> getSolution() override;

private:
    void decompose();
};


#endif