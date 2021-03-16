#include "AABB.h"

AABB::AABB() {
    this->min_point_ = Point3(-1.0, -1.0, -1.0);
    this->max_point_ = Point3(1.0, 1.0, 1.0);
}

AABB::AABB(Point3 min_point, Point3 max_point) {
    this->min_point_ = min_point;
    this->max_point_ = max_point;
}

Point3 AABB::min_point() const {
    return this->min_point_;
}

Point3 AABB::max_point() const {
    return this->max_point_;
}

bool AABB::isHit(Ray& ray) {
    // Code for the Box-Ray intersection come from the CS 419 lecture slides
    // Initialize data for the x slab intersection
    double a = 1.0 / ray.direction()[0];
    double tx_min, tx_max;
    // Check the x slab
    if(a >= 0.0) {
        tx_min = (this->min_point_[0] - ray.origin()[0]) * a;
        tx_max = (this->max_point_[0] - ray.origin()[0]) * a;
    } else {
        tx_min = (this->max_point_[0] - ray.origin()[0]) * a;
        tx_max = (this->min_point_[0] - ray.origin()[0]) * a;
    }
    // Initialize data for the y slab intersection
    double b = 1.0 / ray.direction()[1];
    double ty_min, ty_max;
    // Check the y slab
    if(b >= 0.0) {
        ty_min = (this->min_point_[1] - ray.origin()[1]) * b;
        ty_max = (this->max_point_[1] - ray.origin()[1]) * b;
    } else {
        ty_min = (this->max_point_[1] - ray.origin()[1]) * b;
        ty_max = (this->min_point_[1] - ray.origin()[1]) * b;
    }
    // Initialize data for the z slab intersection
    double c = 1.0 / ray.direction()[2];
    double tz_min, tz_max;
    // Check the z slab
    if(c >= 0.0) {
        tz_min = (this->min_point_[2] - ray.origin()[2]) * c;
        tz_max = (this->max_point_[2] - ray.origin()[2]) * c;
    } else {
        tz_min = (this->max_point_[2] - ray.origin()[2]) * c;
        tz_max = (this->min_point_[2] - ray.origin()[2]) * c;
    }
    // Initialize data for final intersection check
    double t0, t1;
    // Find the largest entering t
    if(tx_min > ty_min) {
        t0 = tx_min;
    } else {
        t0 = ty_min;
    }
    if(tz_min > t0) {
        t0 = tz_min;
    }
    // Find the smallest exiting t
    if(tx_max < ty_max) {
        t1 = tx_max;
    } else {
        t1 = ty_max;
    }
    if(tz_max < t1) {
        t1 = tz_max;
    }
    // Return the hit result
    double epsilon = 0.00001;
    return (t0 < t1 && t1 > epsilon);
}
