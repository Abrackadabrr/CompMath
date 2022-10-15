//
// Created by evgen on 13.10.2022.
//

#include <cmath>
#include <iostream>

#include "CompMath/SolversNonlinearEquation/SimpleIteration.h"

double phi1(double x) {
    return 1/std::sqrt(8*M_E) * std::exp(x*x);
}

double phi2(double x) {
    return x + std::exp(1.5)/2 * x*std::exp(-x*x) - (1/std::sqrt(32*M_E) * std::exp(1.5));
}

int main() {
    double initial2 = 1.3;
    double initial1 = 0.3;
    auto firstRoot = SimpleIteration<double>(phi1, initial1, 3);
    auto secondRoot = SimpleIteration<double>(phi2, initial2, 2);
    std::cout<< "Полуширина на полувысоте = " << - firstRoot + secondRoot << std::endl;
}