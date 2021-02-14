#include "Vec3.h"

Vec3::Vec3(double data[3]) {
    this->data[0] = data[0];
    this->data[1] = data[1];
    this->data[2] = data[2];
}

Vec3 Vec3::operator+(const Vec3& otherVec) {
    double tempData [3] = {this->data[0] + otherVec.data[0],
                           this->data[1] + otherVec.data[1],
                           this->data[2] + otherVec.data[2]};
    return Vec3(tempData);
}

Vec3 Vec3::operator-(const Vec3& otherVec) {
    double tempData [3] = {this->data[0] - otherVec.data[0],
                           this->data[1] - otherVec.data[1],
                           this->data[2] - otherVec.data[2]};
    return Vec3(tempData);
}

Vec3 Vec3::operator*(const double& otherNum) {
    double tempData [3] = {this->data[0] * otherNum,
                           this->data[1] * otherNum,
                           this->data[2] * otherNum};
    return Vec3(tempData);
}

Vec3 Vec3::operator/(const double& otherNum) {
    double tempData [3] = {this->data[0] / otherNum,
                           this->data[1] / otherNum,
                           this->data[2] / otherNum};
    return Vec3(tempData);
}
