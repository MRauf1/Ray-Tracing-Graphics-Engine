#ifndef VEC_H
#define VEC_H

#include <iostream>

template <typename T>
class Vec {

    public:
        virtual double operator[](int i) const = 0;
        virtual T operator+(const T& otherVec) = 0;
        virtual T operator-(const T& otherVec) = 0;
        virtual T operator*(const double& otherNum) = 0;
        virtual T operator/(const double& otherNum) = 0;

        virtual double dot(const T& otherVec) = 0;
        virtual void write_data(std::ostream& out) = 0;

};

#endif
