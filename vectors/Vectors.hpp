//
// Created by evgen on 06.02.2022.
//

#ifndef MY_PROJECT_VECTORS_HPP
#define MY_PROJECT_VECTORS_HPP

#include <algorithm>
#include <fstream>
#include <numeric>
#include <sstream>
#include <cmath>

/*
 * CUSTOM FILE WITH SPECIAL FUNCTIONS FOR EASIER USE OF std::vector<>
 */


/**
 * @param first - vector
 * @param number - figure
 * @tparam value_t - type of figures in vector
 * @tparam number_t - type of nuber
 * @warning make sure yoiu can cast number_t to value_t
 * @return production of vector and number
 */
    template<typename value_t, typename number_t>
    std::vector<value_t> operator*(const std::vector<value_t>& first, number_t number) {
        std::vector<value_t> result;
        result.reserve(first.size());
        for (auto& i : first)
            result.push_back((i*static_cast<value_t>(number)));
        return result;
    }

/**
 * @param first - vector
 * @param number - figure
 * @tparam value_t - type of figures in vector
 * @tparam number_t - type of nuber
 * @warning make sure yoiu can cast number_t to value_t
 * @return production of number and vector
 */
    template<typename value_t, typename number_t>
    std::vector<value_t> operator*(number_t number, const std::vector<value_t>& first) {
        return first*number;
    }

/**
 * @param first, second are vectors
 * @return return subtraction of vectors like in linear algebra
*/
template<typename value_t>
std::vector<value_t> operator-(const std::vector<value_t>& first, const std::vector<value_t>& second) {
    return first + (-1)*second;
}

/**
 * @param first, second are vectors
 * @return sum of vectors like in linear algebra
 */
template<typename value_t>
std::vector<value_t> operator+(const std::vector<value_t>& first, const std::vector<value_t>& second) {
    std::vector<value_t> result(first.size());
    std::transform(first.begin(), first.end(), second.begin(), result.begin(), std::plus<>());
    return result;
}

/**
 * @return sequence of instance between start ans stop with step between each neighboring elements
 */
    template<typename value_type>
    std::vector<value_type> sequence(value_type start, value_type stop, value_type step)
    {
        std::vector<value_type> result;
        result.reserve(static_cast<int>((stop - start)/step));
        for (int i = 0, stop_int = static_cast<int>((stop - start)/step); i < stop_int; ++i) {
            result.emplace_back(static_cast<value_type>(start + i * step));
        }
        return std::move(result);
    }

/**
 * Output operator
 * @param v - vector
 * @attention value_t is required to have the similar output operator
 */
    template<typename value_t>
    std::ostream &operator << (std::ostream &os, const std::vector<value_t>& v)
    {
//        os << "[";
        for(int i = 0; i < v.size() - 1; i++)
        {os << v[i] <<" ";};
        os << v[v.size() - 1];
//        os << ']';
        return os;
    }

    template<typename value_t, int N>
    std::ostream &operator << (std::ofstream &os, const std::array<value_t, N> &a) {
        std::vector<value_t> s{};
        for (auto i: a) os << a <<' ';
        return os;
    }
#endif //MY_PROJECT_VECTORS_HPP
