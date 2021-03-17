#ifndef OBJECT_H
#define OBJECT_H

#include "../math/Vec3.h"
#include "../math/Ray.h"
#include "../data_structures/AABB.h"
#include "HitInfo.h"
#include <memory>
#include <iostream>

class Object {

    protected:

        Color3 color_;
        HitInfo hitInfo_;
        std::shared_ptr<AABB> aabb_;


    public:

        /**
         * Getter for color
         * @return Color of the object
         */
        Color3 color() const;

        /**
         * Getter for hitInfo
         * @return hitInfo struct instance containing hit information
         */
        HitInfo hitInfo() const;

        std::shared_ptr<AABB> aabb() const;

        bool operator<(const Object& object) const;

        virtual bool isHit(Ray& ray, double minT, double maxT) = 0;
        virtual void makeAABB() = 0;

};

#endif
