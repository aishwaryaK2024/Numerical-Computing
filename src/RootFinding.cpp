#include <iostream>
#include <cmath>
#include "RootFinding.hpp"


RootFinding::RootFinding(double t) {
    tol = t;
}

double RootFinding::f(double x) {
    return 4*x*x*x - 3*x;
}

void RootFinding::findInterval(double &a, double &b) {
    for (int i = -10; i < 10; i++) {
        if (f(i) * f(i+1) < 0) {
            a = i;
            b = i + 1;
            return;
        }
    }
}

void BisectionMethod::solve() {
    double a, b, m;

    findInterval(a, b);

    while ((b - a) > tol) {
        m = (a + b) / 2;

        if (f(a) * f(m) < 0)
            b = m;
        else
            a = m;
    }

    cout << "Bisection Root = " << m << endl;
}

double NewtonRphson::df(double x) {
    return 12*x*x - 3;
}

void NewtonRphson::solve() {
    double x0 = 1;   
    double x1;

    while (true) {
        x1 = x0 - f(x0) / df(x0);

        if (abs(x1 - x0) < tol)
            break;

        x0 = x1;
    }

    cout << "Newton Root = " << x1 << endl;
}
