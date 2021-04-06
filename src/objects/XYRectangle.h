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
         * Parameterized PointLight constructor
         * @param position Position of the point light
         * @param color    Color of the point light
         */
        XYRectangle(Point3 lower_left, Point3 upper_right, Color3 color);

        /**
         * Getter for position
         * @return Position of the point light
         */
        Point3 lower_left() const;

        Point3 upper_right() const;

        bool isHit(Ray& ray, double minT, double maxT) override;

        /**
         * Creates and stores the AABB for the object
         */
        void makeAABB() override;

        std::string subclass() override;

};

#endif
