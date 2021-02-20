#ifndef HITINFO_H
#define HITINFO_H

#include "../math/Vec3.h"

struct HitInfo {
    Point3 hitpoint;
    Vec3 normal;
    double t;
};

#endif
