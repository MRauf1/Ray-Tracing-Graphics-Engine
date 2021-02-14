#ifndef POINT3_H
#define POINT3_H

#include "Point.h"

class Point3 : public Point<Point3> {

    private:
        double data_[3];

    public:
        Point3(double data[3]);
        double x() const;
        double y() const;
        double z() const;

        Point3 operator+(const Point3& otherPoint) override;
        Point3 operator-(const Point3& otherPoint) override;
        Point3 operator*(const double& otherNum) override;
        Point3 operator/(const double& otherNum) override;

};

#endif
