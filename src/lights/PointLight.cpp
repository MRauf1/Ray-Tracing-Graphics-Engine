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

Ray PointLight::lightDirection(Point3& point, bool addEpsilon) {
    // Check whether to add an epsilon
    if(addEpsilon) {
        Vec3 direction(this->position_ - point);
        double epsilon = 0.00001;
        return Ray(point + (direction * epsilon), direction);
    } else {
        return Ray(point, this->position_ - point);
    }
}
