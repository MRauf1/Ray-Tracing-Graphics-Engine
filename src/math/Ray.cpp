#include "Ray.h"

Ray::Ray() {
    this->origin_ = Point3();
    this->direction_ = Vec3();
}

Ray::Ray(Point3 origin, Vec3 direction) {
    this->origin_ = origin;
    this->direction_ = direction;
}

Point3 Ray::origin() const {
    return this->origin_;
}

Vec3 Ray::direction() const {
    return this->direction_;
}

Point3 Ray::at(double t) {
    return (this->origin_ + this->direction_ * t);
}
