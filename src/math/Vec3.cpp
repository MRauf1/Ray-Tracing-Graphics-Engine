#include "Vec3.h"

Vec3::Vec3(double data[3]) {
    this->data_[0] = data[0];
    this->data_[1] = data[1];
    this->data_[2] = data[2];
}

double Vec3::x() const {
    return this->data_[0];
}

double Vec3::y() const {
    return this->data_[1];
}

double Vec3::z() const {
    return this->data_[2];
}

Vec3 Vec3::operator+(const Vec3& otherVec) {
    double tempData [3] = {this->data_[0] + otherVec.data_[0],
                           this->data_[1] + otherVec.data_[1],
                           this->data_[2] + otherVec.data_[2]};
    return Vec3(tempData);
}

Vec3 Vec3::operator-(const Vec3& otherVec) {
    double tempData [3] = {this->data_[0] - otherVec.data_[0],
                           this->data_[1] - otherVec.data_[1],
                           this->data_[2] - otherVec.data_[2]};
    return Vec3(tempData);
}

Vec3 Vec3::operator*(const double& otherNum) {
    double tempData [3] = {this->data_[0] * otherNum,
                           this->data_[1] * otherNum,
                           this->data_[2] * otherNum};
    return Vec3(tempData);
}

Vec3 Vec3::operator/(const double& otherNum) {
    double tempData [3] = {this->data_[0] / otherNum,
                           this->data_[1] / otherNum,
                           this->data_[2] / otherNum};
    return Vec3(tempData);
}
