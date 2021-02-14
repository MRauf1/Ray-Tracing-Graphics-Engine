#ifndef VEC3_H
#define VEC3_H

#include "Vec.h"

class Vec3 : public Vec<Vec3> {

    private:
        double data[3];

    public:
        Vec3(double data[3]);
        Vec3 operator+(const Vec3& otherVec) override;
        Vec3 operator-(const Vec3& otherVec) override;
        Vec3 operator*(const double& otherNum) override;
        Vec3 operator/(const double& otherNum) override;

};

#endif
