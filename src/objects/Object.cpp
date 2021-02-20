#include "Object.h"

Color3 Object::color() const {
    return this->color_;
}

HitInfo Object::hitInfo() const {
    return this->hitInfo_;
}
