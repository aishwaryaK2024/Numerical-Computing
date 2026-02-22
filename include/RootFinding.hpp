#ifndef ROOTFINDING_HPP
#define ROOTFINDING_HPP
#include <iostream>
#include <cmath>
using namespace std;

class RootFinding {
protected:
    double tol;

public:
    RootFinding(double t = 0.0001);
    double f(double x);         
    void findInterval(double &a, double &b); 
    virtual void solve() = 0;   
};


class BisectionMethod : public RootFinding {
public:
    void solve();
};


class NewtonRphson : public RootFinding {
public:
    double df(double x);  
    void solve();
};

#endif


