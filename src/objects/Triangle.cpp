#include "Triangle.h"

Triangle::Triangle() {

}

Triangle::Triangle(Color3 color, Point3 point1, Point3 point2, Point3 point3) {
    this->color_ = color;
    this->point1_ = point1;
    this->point2_ = point2;
    this->point3_ = point3;
}

Point3 Triangle::point1() const {
    return this->point1_;
}

Point3 Triangle::point2() const {
    return this->point2_;
}

Point3 Triangle::point3() const {
    return this->point3_;
}

bool Triangle::isHit(Ray& ray, double minT, double maxT) {
    Point3 e1 = this->point2_ - this->point1_;
    Point3 e2 = this->point3_ - this->point1_;
    Vec3 q = ray.direction().cross(e2);
    double a = e1.dot(q);
    double epsilon = 0.0000001;
    if(a > -epsilon && a < epsilon) {
        return false;
    }
    double f = 1 / a;
    Vec3 s = ray.origin() - this->point1_;
    double u = f * (s.dot(q));
    if(u < 0.0) {
        return false;
    }
    Vec3 r = s.cross(e1);
    double v = f * (ray.direction().dot(r));
    if(v < 0.0 || (u + v) > 1.0) {
        return false;
    }
    bool isHit = true;
    double t = f * (e2.dot(r));

    if(isHit && t >= minT && t <= maxT) {
        this->hitInfo_.hitpoint = ray.at(t);
        // Note: slides say e1.cross(e2) for normal, but that gives normal
        // in the reverse direction, but e2.cross(e1)
        // Bug or not? Need to figure out
        this->hitInfo_.normal = e2.cross(e1);
        this->hitInfo_.t = t;
        return true;
    }
    return false;
}
