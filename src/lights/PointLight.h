#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "../math/Vec3.h"
#include "../math/Ray.h"

class PointLight {

    private:
        Point3 position_;
        Color3 color_;

    public:
        PointLight();
        PointLight(Point3 position, Color3 color);
        Point3 position() const;
        Color3 color() const;

        Ray lightDirection(Point3& point, bool addEpsilon);

};

#endif
