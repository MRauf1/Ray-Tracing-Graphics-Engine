#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"

class Triangle : public Object {

    private:
        Point3 point1_;
        Point3 point2_;
        Point3 point3_;

    public:
        Triangle();
        Triangle(Color3 color, Point3 point1, Point3 point2, Point3 point3);
        Point3 point1() const;
        Point3 point2() const;
        Point3 point3() const;

        bool isHit(Ray& ray, double minT, double maxT) override;

};

#endif
