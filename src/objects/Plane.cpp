#include "Plane.h"

Plane::Plane() {
    this->color_ = Color3(0.0, 0.0, 0.0);
    this->position_ = Point3(0.0, 0.0, 0.0);
    this->normal_ = Vec3(0.0, 0.0, -1.0);
    this->makeAABB();
}

Plane::Plane(Color3 color, Point3 position, Vec3 normal) {
    this->color_ = color;
    this->position_ = position;
    this->normal_ = normal;
    this->makeAABB();
}

Point3 Plane::position() const {
    return this->position_;
}

Vec3 Plane::normal() const {
    return this->normal_;
}

bool Plane::isHit(Ray& ray, double minT, double maxT) {
    // Check if there is a hit and calculate t
    bool isHit = ray.direction().dot(this->normal_) != 0;
    double t = ((this->position_ - ray.origin()).dot(this->normal_) / (ray.direction().dot(this->normal_)));
    // If the hit is valid, store the info and return true
    if(isHit && t >= minT && t <= maxT) {
        this->hitInfo_.hitpoint = ray.at(t);
        this->hitInfo_.normal = this->normal_;
        this->hitInfo_.t = t;
        return true;
    }
    // Otherwise, return false
    return false;
}

void Plane::makeAABB() {
    this->aabb_ = nullptr;
}

std::string Plane::subclass() {
    return "Plane";
}
