#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include <algorithm>

class Triangle : public Object {

    private:

        Point3 point1_;
        Point3 point2_;
        Point3 point3_;


    public:

        /**
         * Default Triangle constructor
         */
        Triangle();

        /**
         * Parameterized Triangle constructor
         * @param color  Color of the Triangle
         * @param point1 1st vertex of the Triangle
         * @param point2 2nd vertex of the Triangle
         * @param point3 3rd vertex of the Triangle
         */
        Triangle(Color3 color, Point3 point1, Point3 point2, Point3 point3);

        /**
         * Getter for point1
         * @return 1st vertex of the Triangle
         */
        Point3 point1() const;

        /**
         * Getter for point2
         * @return 2nd vertex of the Triangle
         */
        Point3 point2() const;

        /**
         * Getter for point3
         * @return 3rd vertex of the Triangle
         */
        Point3 point3() const;


        /**
         * Given the ray, check whether the ray hits the triangle
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
