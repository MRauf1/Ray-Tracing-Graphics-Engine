#include "XYRectangleLight.h"

XYRectangleLight::XYRectangleLight() {

}

XYRectangleLight::XYRectangleLight(Point3 lower_left, Point3 upper_right, Color3 color) {
    this->lower_left_ = lower_left;
    this->upper_right_ = upper_right;
    this->color_ = color;
}

Point3 XYRectangleLight::lower_left() const {
    return this->lower_left_;
}

Point3 XYRectangleLight::upper_right() const {
    return this->upper_right_;
}

Color3 XYRectangleLight::color() const {
    return this->color_;
}

Ray XYRectangleLight::lightDirection(Point3& point, bool addEpsilon) {
    // Initialize random number generator using Uniform distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_x(this->lower_left_[0], this->upper_right_[0]);
    std::uniform_real_distribution<> dis_y(this->lower_left_[1], this->upper_right_[1]);
    // Find the hitpoint on the rectangle
    Point3 hitpoint(dis_x(gen), dis_y(gen), this->lower_left_[2]);
    if(addEpsilon) {
        Vec3 direction(hitpoint - point);
        double epsilon = 0.00001;
        return Ray(point + (direction * epsilon), direction);
    } else {
        return Ray(point, hitpoint - point);
    }
}
