#ifndef VEC_H
#define VEC_H

template <typename T>
class Vec {

    public:
        virtual T operator+(const T& otherVec) = 0;
        virtual T operator-(const T& otherVec) = 0;
        virtual T operator*(const double& otherNum) = 0;
        virtual T operator/(const double& otherNum) = 0;

};

#endif
