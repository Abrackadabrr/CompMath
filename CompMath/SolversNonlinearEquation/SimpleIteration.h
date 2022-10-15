//
// Created by evgen on 13.10.2022.
//

#ifndef LABS_COMP_MATH_SIMPLEITERATION_H
#define LABS_COMP_MATH_SIMPLEITERATION_H

#include <functional>

template<typename Type>
Type SimpleIteration(const std::function<Type(Type)>& phi, const Type& initial_approx, int N) {
    Type result = initial_approx;
    for (int i = 0; i < N; i++){
        result = phi(result);
    }
    return result;
}

#endif //LABS_COMP_MATH_SIMPLEITERATION_H
