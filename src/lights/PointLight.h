#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "../math/Vec3.h"
#include "../math/Ray.h"

class PointLight {

    private:
        Point3 position_;

    public:
        PointLight();
        PointLight(Point3 position);
        Point3 position() const;

        Ray lightDirection(Point3& point);

};

#endif
