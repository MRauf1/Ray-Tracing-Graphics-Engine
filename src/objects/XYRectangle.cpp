#include "XYRectangle.h"

XYRectangle::XYRectangle() {

}

XYRectangle::XYRectangle(Point3 lower_left, Point3 upper_right, Color3 color) {
    this->lower_left_ = lower_left;
    this->upper_right_ = upper_right;
    this->color_ = color;
    this->makeAABB();
}

Point3 XYRectangle::lower_left() const {
    return this->lower_left_;
}

Point3 XYRectangle::upper_right() const {
    return this->upper_right_;
}

bool XYRectangle::isHit(Ray& ray, double minT, double maxT) {
    double t = (this->lower_left_[2] - ray.origin()[2]) / ray.direction()[2];
    if(t < minT || t > maxT) {
        return false;
    }
    double x = ray.origin()[0] + t * ray.direction()[0];
    double y = ray.origin()[1] + t * ray.direction()[1];
    if(x < this->lower_left_[0] || x > this->upper_right_[0] || y < this->lower_left_[1] || y > this->upper_right_[1]) {
        return false;
    }
    this->hitInfo_.hitpoint = ray.at(t);
    this->hitInfo_.normal = Vec3(0.0, 0.0, 1.0);
    this->hitInfo_.t = t;
    // rec.u = (x-x0)/(x1-x0);
    // rec.v = (y-y0)/(y1-y0);
    // rec.t = t;
    // auto outward_normal = vec3(0, 0, 1);
    // rec.set_face_normal(r, outward_normal);
    // rec.mat_ptr = mp;
    // rec.p = r.at(t);
    return true;
}

void XYRectangle::makeAABB() {
    Point3 min_point(this->lower_left_[0], this->lower_left_[1], this->lower_left_[2]);
    Point3 max_point(this->upper_right_[0], this->upper_right_[1], this->lower_left_[2]);
    this->aabb_ = std::make_shared<AABB>(min_point, max_point);
}

std::string XYRectangle::subclass() {
    return "XYRectangle";
}
