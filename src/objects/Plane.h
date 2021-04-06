#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object {

    private:

        Point3 position_;
        Vec3 normal_;


    public:

        /**
         * Default Plane constructor
         */
        Plane();

        /**
         * Parameterized Plane constructor
         * @param color    Color of the plane
         * @param position Position of the plane
         * @param normal   Normal of the plane
         */
        Plane(Color3 color, Point3 position, Vec3 normal);

        /**
         * Getter for position
         * @return Position of the plane
         */
        Point3 position() const;

        /**
         * Getter for normal
         * @return Normal of the plane
         */
        Vec3 normal() const;


        /**
         * Given the ray, check whether the ray hits the plane
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

        /**
         * Creates and stores the AABB for the object
         */
        void makeAABB() override;

        std::string subclass() override;

};

#endif
