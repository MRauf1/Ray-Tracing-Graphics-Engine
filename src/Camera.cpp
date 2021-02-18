#include "Camera.h"

Camera::Camera() {
    this->aspect_ratio_ = 16.0 / 9.0;
    this-> viewport_height_ = 2.0;
    this->viewport_width_ = this->viewport_height_ * this->aspect_ratio_;
    this->focal_length_ = 1.0;
    this->position_ = Point3({0.0, 0.0, 0.0});
    this->hor_direction_ = Vec3(this->viewport_width_, 0.0, 0.0);
    this->ver_direction_ = Vec3(0.0, this->viewport_height_, 0.0);
    this->lower_left_ = this->position_ - this->hor_direction_ / 2 - this->ver_direction_ / 2 - Vec3(0.0, 0.0, this->focal_length_);
}

Camera::Camera(double aspect_ratio, double viewport_height, double focal_length, Point3 position) {
    this->aspect_ratio_ = aspect_ratio;
    this-> viewport_height_ = viewport_height;
    this->viewport_width_ = this->viewport_height_ * this->aspect_ratio_;
    this->focal_length_ = focal_length;
    this->position_ = position;
    this->hor_direction_ = Vec3(this->viewport_width_, 0.0, 0.0);
    this->ver_direction_ = Vec3(0.0, this->viewport_height_, 0.0);
    this->lower_left_ = this->position_ - this->hor_direction_ / 2 - this->ver_direction_ / 2 - Vec3(0.0, 0.0, this->focal_length_);
}

double Camera::aspect_ratio() const {
    return this->aspect_ratio_;
}

double Camera::viewport_height() const {
    return this->viewport_height_;
}

double Camera::viewport_width() const {
    return this->viewport_width_;
}

double Camera::focal_length() const {
    return this->focal_length_;
}

Point3 Camera::position() const {
    return this->position_;
}

Vec3 Camera::hor_direction() const {
    return this->hor_direction_;
}

Vec3 Camera::ver_direction() const {
    return this->ver_direction_;
}

Point3 Camera::lower_left() const {
    return this->lower_left_;
}
