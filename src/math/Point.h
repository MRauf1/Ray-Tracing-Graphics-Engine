#ifndef POINT_H
#define POINT_H

template <typename T>
class Point {

    public:
        virtual T operator+(const T& otherPoint) = 0;
        virtual T operator-(const T& otherPoint) = 0;
        virtual T operator*(const double& otherNum) = 0;
        virtual T operator/(const double& otherNum) = 0;

};

#endif
