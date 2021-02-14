#include "Point3.h"

Point3::Point3(double data[3]) {
    this->data_[0] = data[0];
    this->data_[1] = data[1];
    this->data_[2] = data[2];
}

double Point3::x() const {
    return this->data_[0];
}

double Point3::y() const {
    return this->data_[1];
}

double Point3::z() const {
    return this->data_[2];
}

Point3 Point3::operator+(const Point3& otherPoint) {
    double tempData [3] = {this->data_[0] + otherPoint.data_[0],
                           this->data_[1] + otherPoint.data_[1],
                           this->data_[2] + otherPoint.data_[2]};
    return Point3(tempData);
}

Point3 Point3::operator-(const Point3& otherPoint) {
    double tempData [3] = {this->data_[0] - otherPoint.data_[0],
                           this->data_[1] - otherPoint.data_[1],
                           this->data_[2] - otherPoint.data_[2]};
    return Point3(tempData);
}

Point3 Point3::operator*(const double& otherNum) {
    double tempData [3] = {this->data_[0] * otherNum,
                           this->data_[1] * otherNum,
                           this->data_[2] * otherNum};
    return Point3(tempData);
}

Point3 Point3::operator/(const double& otherNum) {
    double tempData [3] = {this->data_[0] / otherNum,
                           this->data_[1] / otherNum,
                           this->data_[2] / otherNum};
    return Point3(tempData);
}
