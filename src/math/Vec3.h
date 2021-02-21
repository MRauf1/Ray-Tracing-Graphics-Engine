#ifndef VEC3_H
#define VEC3_H

#include "Vec.h"
#include <cmath>

class Vec3 : public Vec<Vec3> {

    private:
        double data_[3];

    public:
        Vec3();
        Vec3(double data[3]);
        Vec3(double x, double y, double z);
        double x() const;
        double y() const;
        double z() const;

        double operator[](int i) const override;
        Vec3 operator+(const Vec3& otherVec) override;
        Vec3 operator-(const Vec3& otherVec) override;
        Vec3 operator*(const double& otherNum) override;
        Vec3 operator/(const double& otherNum) override;

        double dot(const Vec3& otherVec) override;
        Vec3 cross(const Vec3& otherVec) override;
        double magnitude() override;
        Vec3 normalize() override;
        void write_data(std::ostream& out) override;

};

using Point3 = Vec3;
using Color3 = Vec3;

#endif
