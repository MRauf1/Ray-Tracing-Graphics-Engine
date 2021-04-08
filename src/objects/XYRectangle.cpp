#include "XYRectangle.h"

XYRectangle::XYRectangle() {

}

XYRectangle::XYRectangle(Color3 color, Material material, Point3 lower_left, Point3 upper_right) {
    this->color_ = color;
    this->material_ = material;
    this->lower_left_ = lower_left;
    this->upper_right_ = upper_right;
    this->makeAABB();
}

Point3 XYRectangle::lower_left() const {
    return this->lower_left_;
}

Point3 XYRectangle::upper_right() const {
    return this->upper_right_;
}

bool XYRectangle::isHit(Ray& ray, double minT, double maxT) {
    // Code for the rectangle hit is taken and modified from Peter Shirley's
    // "Ray Tracing The Next Week"
    // Calculate t
    double t = (this->lower_left_[2] - ray.origin()[2]) / ray.direction()[2];
    if(t < minT || t > maxT) {
        return false;
    }
    double x = ray.origin()[0] + t * ray.direction()[0];
    double y = ray.origin()[1] + t * ray.direction()[1];
    if(x < this->lower_left_[0] || x > this->upper_right_[0] || y < this->lower_left_[1] || y > this->upper_right_[1]) {
        return false;
    }
    // Store the hit information
    this->hitInfo_.hitpoint = ray.at(t);
    this->hitInfo_.normal = Vec3(0.0, 0.0, 1.0);
    this->hitInfo_.t = t;
    return true;
}

void XYRectangle::makeAABB() {
    // Construct the AABB for the rectangle
    Point3 min_point(this->lower_left_[0], this->lower_left_[1], this->lower_left_[2]);
    Point3 max_point(this->upper_right_[0], this->upper_right_[1], this->lower_left_[2]);
    this->aabb_ = std::make_shared<AABB>(min_point, max_point);
}

std::string XYRectangle::subclass() {
    return "XYRectangle";
}
