#ifndef XYRECTANGLELIGHT_H
#define XYRECTANGLELIGHT_H

#include "../math/Vec3.h"
#include "../math/Ray.h"
#include <random>

class XYRectangleLight {

    private:

        Point3 lower_left_;
        Point3 upper_right_;
        Color3 color_;


    public:

        /**
         * Default XYRectangleLight constructor
         */
        XYRectangleLight();

        /**
         * Parameterized XYRectangleLight constructor
         * @param lower_left  Lower left point of the rectangle light
         * @param upper_right Upper right point of the rectangle light
         * @param color       Color of the rectangle light
         */
        XYRectangleLight(Point3 lower_left, Point3 upper_right, Color3 color);

        /**
         * Getter for lower_left
         * @return Lower left point of the rectangle light
         */
        Point3 lower_left() const;

        /**
         * Getter for upper_right
         * @return Upper right point of the rectangle light
         */
        Point3 upper_right() const;

        /**
         * Getter for color
         * @return Color of the point light
         */
        Color3 color() const;


        /**
         * Given a starting point, creates a ray from that point to the
         * point light
         * @param  point      Starting point of the ray
         * @param  addEpsilon Whether to add epsilon to the point in direction
         *                    of the ray
         * @return            Ray from the point to the point light
         */
        Ray lightDirection(Point3& point, bool addEpsilon);

};

#endif
