#include "PointLight.h"

PointLight::PointLight() {

}

PointLight::PointLight(Point3 position, Color3 color) {
    this->position_ = position;
    this->color_ = color;
}

Point3 PointLight::position() const {
    return this->position_;
}

Color3 PointLight::color() const {
    return this->color_;
}

Ray PointLight::lightDirection(Point3& point) {
    Ray ray(point, this->position_ - point);
    return ray;
}
