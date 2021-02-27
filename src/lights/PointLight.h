#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "../math/Vec3.h"
#include "../math/Ray.h"

class PointLight {

    private:

        Point3 position_;
        Color3 color_;


    public:

        /**
         * Default PointLight constructor
         */
        PointLight();

        /**
         * Parameterized PointLight constructor
         * @param position Position of the point light
         * @param color    Color of the point light
         */
        PointLight(Point3 position, Color3 color);

        /**
         * Getter for position
         * @return Position of the point light
         */
        Point3 position() const;

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
