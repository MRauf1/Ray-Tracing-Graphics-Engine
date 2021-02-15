#ifndef RAY_H
#define RAY_H

#include "Vec3.cpp"

class Ray {

    private:
        Point3 origin_;
        Vec3 direction_;

    public:
        Ray();
        Ray(Point3 origin, Vec3 direction);
        Point3 origin() const;
        Vec3 direction() const;

        Point3 at(double t);

};

#endif
