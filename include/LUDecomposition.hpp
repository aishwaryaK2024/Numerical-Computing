#ifndef LU_H
#define LU_H

#include "LinearSystem.hpp"
#include <cmath>

class LUDecomposition : public LinearSystem {
protected:
    std::vector<std::vector<double>> L, U;

public:
    LUDecomposition(const Matrix& m);

    virtual void solve() = 0;                      // pure virtual
    virtual std::vector<double> getSolution() = 0; // pure virtual

    virtual ~LUDecomposition() {}
};


class Doolittle : public LUDecomposition {
    std::vector<double> solution;

public:
    Doolittle(const Matrix& m);

    void solve() override;
    std::vector<double> getSolution() override;

private:
    void decompose();
};


class Crout : public LUDecomposition {
    std::vector<double> solution;

public:
    Crout(const Matrix& m);

    void solve() override;
    std::vector<double> getSolution() override;

private:
    void decompose();
};


class Cholesky : public LUDecomposition {
    std::vector<double> solution;

public:
    Cholesky(const Matrix& m);

    void solve() override;
    std::vector<double> getSolution() override;

private:
    void decompose();
    bool isSymmetric();
};

#endif