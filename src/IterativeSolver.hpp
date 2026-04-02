#ifndef ITERATIVESOLVER_H
#define ITERATIVESOLVER_H

#include "LinearSystem.hpp"
#include <cmath>

class IterativeSolver : public LinearSystem {
protected:
    int maxIter;
    double tol;
    std::vector<double> solution;

public:
    IterativeSolver(const Matrix& m, int maxIter = 1000, double tol = 1e-6);

    virtual std::vector<double> solve() = 0;
    //virtual std::vector<double> getSolution() = 0;

    virtual ~IterativeSolver() {}
};


class GaussJacobi : public IterativeSolver {
public:
    GaussJacobi(const Matrix& m, int maxIter = 1000, double tol = 1e-6);
    std::vector<double> solve() override;
    //std::vector<double> getSolution() override;
};


class GaussSeidel : public IterativeSolver {
public:
    GaussSeidel(const Matrix& m, int maxIter = 1000, double tol = 1e-6);
    std::vector<double> solve() override;
    //std::vector<double> getSolution() override;
};

#endif