#include "Camera.h"

Camera::Camera() {
    this->aspect_ratio_ = 16.0 / 9.0;
    this->viewport_height_ = 2.0;
    this->viewport_width_ = this->viewport_height_ * this->aspect_ratio_;
    this->focal_length_ = 1.0;
    this->position_ = Point3({0.0, 0.0, 0.0});
    this->x_dir_ = Vec3(1.0, 0.0, 0.0);
    this->y_dir_ = Vec3(0.0, 1.0, 0.0);
    this->z_dir_ = Vec3(0.0, 0.0, 1.0);
    this->view_dir_ = Vec3(0.0, 0.0, -1.0);
    this->up_dir_ = Vec3(0.0, 1.0, 0.0);
    this->lower_left_ = this->position_ - this->x_dir_ / 2 - this->y_dir_ / 2 - Vec3(0.0, 0.0, this->focal_length_);
    this->projection_ = PERSPECTIVE;
    // Create the orthonormal basis for the camera
    this->createOrthonormalBasis();
}

Camera::Camera(double aspect_ratio, double viewport_height, double focal_length,
               Point3 position, Vec3 view_dir, Vec3 up_dir, Projection projection) {
    this->aspect_ratio_ = aspect_ratio;
    this->viewport_height_ = viewport_height;
    this->viewport_width_ = this->viewport_height_ * this->aspect_ratio_;
    this->focal_length_ = focal_length;
    this->position_ = position;
    this->x_dir_ = Vec3(this->viewport_width_, 0.0, 0.0);
    this->y_dir_ = Vec3(0.0, this->viewport_height_, 0.0);
    this->z_dir_ = Vec3(0.0, 0.0, 1.0);
    this->view_dir_ = view_dir;
    this->up_dir_ = up_dir;
    this->lower_left_ = this->position_ - this->x_dir_ / 2 - this->y_dir_ / 2 - Vec3(0.0, 0.0, this->focal_length_);
    this->projection_ = projection;
    // Create the orthonormal basis for the camera
    this->createOrthonormalBasis();
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

Vec3 Camera::x_dir() const {
    return this->x_dir_;
}

Vec3 Camera::y_dir() const {
    return this->y_dir_;
}

Vec3 Camera::z_dir() const {
    return this->z_dir_;
}

Vec3 Camera::view_dir() const {
    return this->view_dir_;
}

Vec3 Camera::up_dir() const {
    return this->up_dir_;
}

Point3 Camera::lower_left() const {
    return this->lower_left_;
}

Projection Camera::projection() const {
    return this->projection_;
}

Ray Camera::createRay(double u, double v) {
    // Calculate the grid coordinates
    Vec3 x_step(this->viewport_width_, 0.0, 0.0);
    Vec3 y_step(0.0, this->viewport_height_, 0.0);
    Vec3 gridInfo = this->lower_left_ + x_step * u + y_step * v;
    // Use the orthonormal basis of the camera and modify the grid
    // coordinates accordingly
    gridInfo = (this->x_dir_ * gridInfo[0]) + (this->y_dir_ * gridInfo[1]) + (this->z_dir_ * gridInfo[2]);
    // Ray for Perspective projection or Orthographic projection
    if(this->projection_ == PERSPECTIVE) {
        Ray ray(this->position_, gridInfo);
        return ray;
    } else if(this->projection_ == ORTHOGRAPHIC) {
        Ray ray(gridInfo, this->view_dir_);
        return ray;
    }
}

void Camera::createOrthonormalBasis() {
    // The formulas are from the lecture slides
    Point3 origin(0.0, 0.0, 0.0);
    this->z_dir_ = (origin - this->view_dir_).normalize();
    this->x_dir_ = (this->up_dir_.cross(this->z_dir_)).normalize();
    this->y_dir_ = this->z_dir_.cross(this->x_dir_);
}
