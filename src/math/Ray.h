#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {

    private:

        Point3 origin_;
        Vec3 direction_;


    public:

        /**
         * Default Ray constructor
         */
        Ray();

        /**
         * Parameterized Ray constructor
         * @param origin    Origin of the ray
         * @param direction Direction of the ray
         */
        Ray(Point3 origin, Vec3 direction);

        /**
         * Getter for origin
         * @return Origin of the ray
         */
        Point3 origin() const;

        /**
         * Getter for direction
         * @return Direction of the ray
         */
        Vec3 direction() const;


        /**
         * Calculates and returns the point along the ray at value t
         * @param  t Double t at which to evaluate the ray
         * @return   The point on the ray at t
         */
        Point3 at(double t);

};

#endif
