#include "Vec3.h"

Vec3::Vec3() {
    this->data_[0] = 0;
    this->data_[1] = 0;
    this->data_[2] = 0;
}

Vec3::Vec3(double data[3]) {
    this->data_[0] = data[0];
    this->data_[1] = data[1];
    this->data_[2] = data[2];
}

Vec3::Vec3(double x, double y, double z) {
    this->data_[0] = x;
    this->data_[1] = y;
    this->data_[2] = z;
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

double Vec3::operator[](int i) const {
    return this->data_[i];
}

Vec3 Vec3::operator+(const Vec3& otherVec) {
    double tempData[3] = {
        this->data_[0] + otherVec.data_[0],
        this->data_[1] + otherVec.data_[1],
        this->data_[2] + otherVec.data_[2]
    };
    return Vec3(tempData);
}

Vec3 Vec3::operator-(const Vec3& otherVec) {
    double tempData[3] = {
        this->data_[0] - otherVec.data_[0],
        this->data_[1] - otherVec.data_[1],
        this->data_[2] - otherVec.data_[2]
    };
    return Vec3(tempData);
}

Vec3 Vec3::operator*(const double& otherNum) {
    double tempData[3] = {
        this->data_[0] * otherNum,
        this->data_[1] * otherNum,
        this->data_[2] * otherNum
    };
    return Vec3(tempData);
}

Vec3 Vec3::operator/(const double& otherNum) {
    double tempData[3] = {
        this->data_[0] / otherNum,
        this->data_[1] / otherNum,
        this->data_[2] / otherNum
    };
    return Vec3(tempData);
}

Vec3 Vec3::elemProduct(const Vec3& otherVec) {
    return Vec3(this->data_[0] * otherVec[0], this->data_[1] * otherVec[1],this->data_[2] * otherVec[2]);
}

double Vec3::dot(const Vec3& otherVec) {
    return ((this->data_[0] * otherVec[0]) + (this->data_[1] * otherVec[1]) + (this->data_[2] * otherVec[2]));
}

Vec3 Vec3::cross(const Vec3& otherVec) {
    double v1 = this->data_[1] * otherVec[2] - this->data_[2] * otherVec[1];
    double v2 = this->data_[2] * otherVec[0] - this->data_[0] * otherVec[2];
    double v3 = this->data_[0] * otherVec[1] - this->data_[1] * otherVec[0];
    return Vec3(v1, v2, v3);
}

double Vec3::magnitude() {
    return (std::sqrt((*this).dot((*this))));
}

Vec3 Vec3::normalize() {
    return ((*this) / ((*this).magnitude()));
}

void Vec3::cutToUnit() {
    for(int i = 0; i < 3; i++) {
        this->data_[i] = this->data_[i] > 1.0 ? 1.0 : this->data_[i];
    }
}

void Vec3::write_data(std::ostream& out) {
    // Following code taken from Peter Shirley's "Ray Tracing in One Weekend"
    out << static_cast<int>(255.999 * this->data_[0]) << " "
        << static_cast<int>(255.999 * this->data_[1]) << " "
        << static_cast<int>(255.999 * this->data_[2]) << "\n";
}
