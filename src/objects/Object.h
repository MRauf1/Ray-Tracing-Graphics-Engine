#ifndef OBJECT_H
#define OBJECT_H

#include "../math/Vec3.h"
#include "../math/Ray.h"
#include "../data_structures/AABB.h"
#include "Material.h"
#include "HitInfo.h"
#include <memory>
#include <iostream>

class Object {

    protected:

        Color3 color_;
        HitInfo hitInfo_;
        std::shared_ptr<AABB> aabb_;
        Material material_;


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

        /**
         * Getter for AABB
         * @return Pointer to the AABB of the object
         */
        std::shared_ptr<AABB> aabb() const;

        Material material() const;

        /**
         * < operator for Object
         * @param  Object  Object to compare against
         * @return         Bool for whether current object is less than the other
         */
        bool operator<(const Object& object) const;

        /**
         * Given the ray, check whether the ray hits the object
         * If it does, check whether it hits within the appropriate
         * t value (using minT and maxT)
         * If it does, return true and store the hit information inside
         * plane's hitInfo variable
         * Otherwise, return false
         * @param  ray  Ray to test the hit for
         * @param  minT Minimum t value to be considered a hit
         * @param  maxT Maximum t value to be considered a hit
         * @return      Bool for whether the object was hit or not
         */
        virtual bool isHit(Ray& ray, double minT, double maxT) = 0;

        /**
         * Creates and stores the AABB for the object
         */
        virtual void makeAABB() = 0;

        /**
         * Getter for which subclass the object is
         * @return String representing the subclass name
         */
        virtual std::string subclass() = 0;

};

#endif
