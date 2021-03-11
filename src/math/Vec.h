#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <algorithm>

template <typename T>
class Vec {

    public:
        virtual double operator[](int i) const = 0;
        virtual T operator+(const T& otherVec) = 0;
        virtual T operator-(const T& otherVec) = 0;
        virtual T operator*(const double& otherNum) = 0;
        virtual T operator/(const double& otherNum) = 0;
        virtual bool operator==(const T& otherVec) = 0;

        virtual T elemProduct(const T& otherVec) = 0;
        virtual double dot(const T& otherVec) = 0;
        virtual T cross(const T& otherVec) = 0;
        virtual double magnitude() = 0;
        virtual T normalize() = 0;
        virtual void cutToUnit() = 0;
        virtual void write_data(std::ostream& out) = 0;

};

#endif
