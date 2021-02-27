#ifndef HITINFO_H
#define HITINFO_H

#include "../math/Vec3.h"

// Struct which stores information regarding the hit of a ray with a surface
struct HitInfo {
    Point3 hitpoint;
    Vec3 normal;
    double t;
};

#endif
