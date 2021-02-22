#include "Sphere.h"

Sphere::Sphere() {
    this->color_ = Color3(0.0, 0.0, 0.0);
    this->center_ = Point3(0.0, 0.0, 0.0);
    this->radius_ = 1.0;
}

Sphere::Sphere(Color3 color, Point3 center, double radius) {
    this->color_ = color;
    this->center_ = center;
    this->radius_ = radius;
}

Point3 Sphere::center() const {
    return this->center_;
}

double Sphere::radius() const {
    return this->radius_;
}

bool Sphere::isHit(Ray& ray, double minT, double maxT) {
    Vec3 ac = ray.origin() - this->center_;
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * ray.direction().dot(ac);
    double c = ac.dot(ac) - (this->radius_ * this->radius_);
    double discriminant = b * b - 4.0 * a * c;
    bool isHit = discriminant > 0;
    double t = isHit ? (-b - std::sqrt(discriminant)) / (2.0 * a) : -1.0;

    if(isHit && t >= minT && t <= maxT) {
        this->hitInfo_.hitpoint = ray.at(t);
        this->hitInfo_.normal = this->hitInfo_.hitpoint - this->center_;
        this->hitInfo_.t = t;
        return true;
    }
    return false;
}