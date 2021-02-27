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

        /**
         * Default Camera constructor
         */
        Camera();

        /**
         * Parameterized Camera constructor
         * @param aspect_ratio    Aspect ratio of the viewport
         * @param viewport_height Height of the viewport
         * @param focal_length    Focal length of the camera
         * @param position        Position of the camera
         * @param view_dir        View direction of the camera
         * @param up_dir          Up direction of the camera
         * @param projection      Type of projection to use
         */
        Camera(double aspect_ratio, double viewport_height, double focal_length,
               Point3 position, Vec3 view_dir, Vec3 up_dir, Projection projection);

        /**
         * Getter for aspect ratio
         * @return Aspect ratio of the viewport
         */
        double aspect_ratio() const;

        /**
         * Getter for viewport height
         * @return Height of the viewport
         */
        double viewport_height() const;

        /**
         * Getter for viewport width
         * @return Width of the viewport
         */
        double viewport_width() const;

        /**
         * Getter for focal length
         * @return Focal length of the camera
         */
        double focal_length() const;

        /**
         * Getter for camera position
         * @return Position of the camera
         */
        Point3 position() const;

        /**
         * Getter for x vector in the camera's orthonormal basis
         * @return X direction of the camera
         */
        Vec3 x_dir() const;

        /**
         * Getter for y vector in the camera's orthonormal basis
         * @return Y direction of the camera
         */
        Vec3 y_dir() const;

        /**
         * Getter for z vector in the camera's orthonormal basis
         * @return Z direction of the camera
         */
        Vec3 z_dir() const;

        /**
         * Getter for view direction
         * @return View direction of the camera
         */
        Vec3 view_dir() const;

        /**
         * Getter for up direction
         * @return Up direction of the camera
         */
        Vec3 up_dir() const;

        /**
         * Lower left point of the viewport
         * @return Lower left point of the viewport
         */
        Point3 lower_left() const;

        /**
         * Getter for the projection type
         * @return Projection type
         */
        Projection projection() const;


        /**
         * Generates and returns a ray for the point (using u and v) on the
         * viewport
         * Has the ability to do Perspective and Orthographic projections
         * @param  u Fraction for the horizontal amount along the viewport
         * @param  v Fraction for the vertical amount along the viewport
         * @return   Ray for the point on the viewport
         */
        Ray createRay(double u, double v);

        /**
         * Modifies the internal x_dir_, y_dir_, z_dir_ by transforming them
         * using the view and up directions
         * Normalizes them to ensure the basis is orthonormal
         */
        void createOrthonormalBasis();

};

#endif
