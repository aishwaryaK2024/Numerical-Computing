#ifndef LU_H
#define LU_H

#include "LinearSystem.hpp"
#include <cmath>

using namespace std;

class LUDecomposition : public LinearSystem {
protected:
    vector<vector<double>> L, U;

public:
    LUDecomposition(const Matrix& m);

    void solve() override;
    vector<double> getSolution() override;

    virtual ~LUDecomposition() {}
};


class Doolittle : public LUDecomposition {
    vector<double> solution;

public:
    Doolittle(const Matrix& m);

    void solve() override;
    vector<double> getSolution() override;

private:
    void decompose();
};


class Crout : public LUDecomposition {
    vector<double> solution;

public:
    Crout(const Matrix& m);

    void solve() override;
    vector<double> getSolution() override;

private:
    void decompose();
};


class Cholesky : public LUDecomposition {
    vector<double> solution;

public:
    Cholesky(const Matrix& m);

    void solve() override;
    vector<double> getSolution() override;

private:
    void decompose();
    bool isSymmetric();
};

#endif