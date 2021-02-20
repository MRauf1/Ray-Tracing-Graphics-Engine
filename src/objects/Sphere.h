#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include <cmath>

class Sphere : public Object {

    private:
        Point3 center_;
        double radius_;

    public:
        Sphere();
        Sphere(Color3 color, Point3 center, double radius);
        Point3 center() const;
        double radius() const;

        bool isHit(Ray& ray, double minT, double maxT) override;

};

#endif
