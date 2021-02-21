#ifndef CAMERA_H
#define CAMERA_H

#include "math/Vec3.h"
#include "Projection.h"
#include "math/Ray.h"

class Camera {

    private:
        double aspect_ratio_;
        double viewport_height_;
        double viewport_width_;
        double focal_length_;
        Point3 position_;
        Vec3 x_dir_;
        Vec3 y_dir_;
        Vec3 z_dir_;
        Vec3 view_dir_;
        Vec3 up_dir_;
        Point3 lower_left_;
        Projection projection_;

    public:
        Camera();
        Camera(double aspect_ratio, double viewport_height, double focal_length, Point3 position, Vec3 view_dir, Vec3 up_dir, Projection projection);
        double aspect_ratio() const;
        double viewport_height() const;
        double viewport_width() const;
        double focal_length() const;
        Point3 position() const;
        Vec3 x_dir() const;
        Vec3 y_dir() const;
        Vec3 z_dir() const;
        Vec3 view_dir() const;
        Vec3 up_dir() const;
        Point3 lower_left() const;
        Projection projection() const;

        Ray createRay(double u, double v);
        void createOrthonormalBasis();

};

#endif
