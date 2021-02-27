#ifndef OBJECT_H
#define OBJECT_H

#include "../math/Vec3.h"
#include "../math/Ray.h"
#include "HitInfo.h"

class Object {

    protected:
        
        Color3 color_;
        HitInfo hitInfo_;


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

        virtual bool isHit(Ray& ray, double minT, double maxT) = 0;

};

#endif
