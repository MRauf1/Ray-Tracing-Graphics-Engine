#include "PointLight.h"

PointLight::PointLight() {

}

PointLight::PointLight(Point3 position) {
    this->position_ = position;
}

Point3 PointLight::position() const {
    return this->position_;
}

Ray PointLight::lightDirection(Point3& point) {
    Ray ray(point, this->position_ - point);
    return ray;
}
