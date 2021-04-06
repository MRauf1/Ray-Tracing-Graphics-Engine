#include "Sphere.h"

Sphere::Sphere() {
    this->color_ = Color3(0.0, 0.0, 0.0);
    this->center_ = Point3(0.0, 0.0, 0.0);
    this->radius_ = 1.0;
    this->makeAABB();
}

Sphere::Sphere(Color3 color, Point3 center, double radius) {
    this->color_ = color;
    this->center_ = center;
    this->radius_ = radius;
    this->makeAABB();
}

Point3 Sphere::center() const {
    return this->center_;
}

double Sphere::radius() const {
    return this->radius_;
}

bool Sphere::isHit(Ray& ray, double minT, double maxT) {
    // The formulas are from Peter Shirley's "Ray Tracing in One Weekend"
    Vec3 ac = ray.origin() - this->center_;
    double a = ray.direction().dot(ray.direction());
    double b = 2.0 * ray.direction().dot(ac);
    double c = ac.dot(ac) - (this->radius_ * this->radius_);
    double discriminant = b * b - 4.0 * a * c;
    // Check if there is a hit and calculate t
    // USE THE OPTIMIZATION DISCUSSED IN LECTURES
    bool isHit = discriminant >= 0;
    double t = isHit ? (-b - std::sqrt(discriminant)) / (2.0 * a) : -1.0;
    // If the hit is valid, store the info and return true
    if(isHit && t >= minT && t <= maxT) {
        this->hitInfo_.hitpoint = ray.at(t);
        this->hitInfo_.normal = this->hitInfo_.hitpoint - this->center_;
        this->hitInfo_.t = t;
        return true;
    }
    // Otherwise, return false
    return false;
}

void Sphere::makeAABB() {
    Point3 min_point(this->center_[0] - this->radius_, this->center_[1] - this->radius_, this->center_[2] - this->radius_);
    Point3 max_point(this->center_[0] + this->radius_, this->center_[1] + this->radius_, this->center_[2] + this->radius_);
    this->aabb_ = std::make_shared<AABB>(min_point, max_point);
}

std::string Sphere::subclass() {
    return "Sphere";
}
