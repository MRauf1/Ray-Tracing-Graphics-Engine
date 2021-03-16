#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include <cmath>

class Sphere : public Object {

    private:

        Point3 center_;
        double radius_;


    public:

        /**
         * Default Sphere constructor
         */
        Sphere();

        /**
         * Parameterized Sphere constructor
         * @param color  Color of the Sphere
         * @param center Center of the Sphere
         * @param radius Radius of the Sphere
         */
        Sphere(Color3 color, Point3 center, double radius);

        /**
         * Getter for center
         * @return Center of the Sphere
         */
        Point3 center() const;

        /**
         * Getter for radius
         * @return Radius of the Sphere
         */
        double radius() const;


        /**
         * Given the ray, check whether the ray hits the sphere
         * If it does, check whether it hits within the appropriate
         * t value (using minT and maxT)
         * If it does, return true and store the hit information inside
         * plane's hitInfo variable
         * Otherwise, return false
         * @param  ray  Ray to test the hit for
         * @param  minT Minimum t value to be considered a hit
         * @param  maxT Maximum t value to be considered a hit
         * @return      [description]
         */
        bool isHit(Ray& ray, double minT, double maxT) override;

        void makeAABB() override;

};

#endif
