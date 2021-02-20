#include "Plane.h"

Plane::Plane() {
    this->color_ = Color3(0.0, 0.0, 0.0);
    this->position_ = Point3(0.0, 0.0, 0.0);
    this->normal_ = Vec3(0.0, 0.0, -1.0);
}

Plane::Plane(Color3 color, Point3 position, Vec3 normal) {
    this->color_ = color;
    this->position_ = position;
    this->normal_ = normal;
}

Point3 Plane::position() const {
    return this->position_;
}

Vec3 Plane::normal() const {
    return this->normal_;
}

bool Plane::isHit(Ray& ray, double minT, double maxT) {
    bool isHit = ray.direction().dot(this->normal_) != 0;
    double t = ((this->position_ - ray.origin()).dot(this->normal_) / (ray.direction().dot(this->normal_)));

    if(t >= minT && t <= maxT) {
        this->hitInfo_.hitpoint = ray.at(t);
        this->hitInfo_.t = t;
        return true;
    }
    return false;
}
