#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object {

    private:
        Point3 position_;
        Vec3 normal_;

    public:
        Plane();
        Plane(Color3 color, Point3 position, Vec3 normal);
        Point3 position() const;
        Vec3 normal() const;

        bool isHit(Ray& ray, double minT, double maxT) override;

};

#endif
