#ifndef AABB_H
#define AABB_H

#include "../math/Vec3.h"
#include "../math/Ray.h"

class AABB {

    private:

        Point3 min_point_;
        Point3 max_point_;


    public:

        /**
         * Default AABB constructor
         */
        AABB();

        /**
         * Parameterized AABB constructor
         * @param min_point Minimum point of AABB
         * @param max_point Maximum point of AABB
         */
        AABB(Point3 min_point, Point3 max_point);

        /**
         * Getter for minimum point
         * @return Minimum point of AABB
         */
        Point3 min_point() const;

        /**
         * Getter for maximum point
         * @return Maximum point of AABB
         */
        Point3 max_point() const;

        /**
         * Checks if the AABB is hit by the ray
         * @param  ray  Ray to check collision with
         * @return   Bool for whether the ray collided with AABB
         */
        bool isHit(Ray& ray);

};

#endif
