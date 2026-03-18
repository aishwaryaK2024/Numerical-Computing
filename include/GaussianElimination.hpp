#ifndef GE_H
#define GE_H

#include "LinearSystem.hpp"

class GaussianElimination : public LinearSystem {
    bool usePivot;
    std::vector<double> solution;

public:
    GaussianElimination(const Matrix& m, bool pivot = true);
    void solve() override;
    std::vector<double> getSolution() override;
};

#endif 