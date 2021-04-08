#ifndef XYRECTANGLE_H
#define XYRECTANGLE_H

#include "../math/Vec3.h"
#include "../math/Ray.h"
#include "Object.h"

class XYRectangle : public Object {

    private:

        Point3 lower_left_;
        Point3 upper_right_;


    public:

        /**
         * Default XYRectangle constructor
         */
        XYRectangle();

        /**
         * Parameterized XYRectangle constructor
         * @param color       Color of the rectangle
         * @param material    Material of the rectangle
         * @param lower_left  Lower left point of the rectangle
         * @param upper_right Upper right point of the rectangle
         */
        XYRectangle(Color3 color, Material material, Point3 lower_left, Point3 upper_right);

        /**
         * Getter for lower_left
         * @return Lower left point of the rectangle
         */
        Point3 lower_left() const;

        /**
         * Getter for upper_right
         * @return Upper right point of the rectangle
         */
        Point3 upper_right() const;

        /**
         * Given the ray, check whether the ray hits the rectangle
         * If it does, check whether it hits within the appropriate
         * t value (using minT and maxT)
         * If it does, return true and store the hit information inside
         * plane's hitInfo variable
         * Otherwise, return false
         * @param  ray  Ray to test the hit for
         * @param  minT Minimum t value to be considered a hit
         * @param  maxT Maximum t value to be considered a hit
         * @return      Bool for whether the rectangle was hit or not
         */
        bool isHit(Ray& ray, double minT, double maxT) override;

        /**
         * Creates and stores the AABB for the object
         */
        void makeAABB() override;

        /**
         * Getter for which subclass the object is
         * @return String representing the subclass name
         */
        std::string subclass() override;

};

#endif
