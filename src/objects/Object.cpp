#include "Object.h"

Color3 Object::color() const {
    return this->color_;
}

HitInfo Object::hitInfo() const {
    return this->hitInfo_;
}

std::shared_ptr<AABB> Object::aabb() const {
    return this->aabb_;
}

bool Object::operator<(const Object& object) const {
    double curr = (this->aabb_->max_point()[0] - this->aabb_->min_point()[0]) / 2;
    double other = (object.aabb()->max_point()[0] - object.aabb()->min_point()[0]) / 2;
    std::cout << (curr) << "," << (other) << std::endl;
    return curr < other;
}
