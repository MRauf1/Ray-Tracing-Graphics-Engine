#ifndef CAMERA_H
#define CAMERA_H

#include "math/Vec3.h"

class Camera {

    private:
        double aspect_ratio_;
        double viewport_height_;
        double viewport_width_;
        double focal_length_;
        Point3 position_;
        Vec3 hor_direction_;
        Vec3 ver_direction_;
        Point3 lower_left_;


    public:
        Camera();
        Camera(double aspect_ratio, double viewport_height, double focal_length, Point3 position);
        double aspect_ratio() const;
        double viewport_height() const;
        double viewport_width() const;
        double focal_length() const;
        Point3 position() const;
        Vec3 hor_direction() const;
        Vec3 ver_direction() const;
        Point3 lower_left() const;

};

#endif
