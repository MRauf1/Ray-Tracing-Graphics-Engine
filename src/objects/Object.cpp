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
