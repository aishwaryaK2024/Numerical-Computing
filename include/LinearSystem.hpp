#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H
using namespace std;
#include "Matrix.hpp"

class LinearSystem : public Matrix {
public:
    LinearSystem(const Matrix& m);

    virtual void solve() = 0;
    virtual vector<double> getSolution() = 0;

    void run(const string& filename);

    virtual ~LinearSystem() {}

protected:
    void validateSquare();
    vector<double> backSubstitution();          
    vector<double> forwardSubstitution(const vector<vector<double>>& L,const vector<double>& b);  
};

#endif