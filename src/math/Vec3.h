#ifndef VEC3_H
#define VEC3_H

#include "Vec.h"
#include <cmath>

class Vec3 : public Vec<Vec3> {

    private:

        double data_[3];


    public:

        /**
         * Default Vec3 constructor
         */
        Vec3();

        /**
         * Parameterized Vec3 constructor using an array
         * @param data  Double array containing the Vec3 values
         */
        Vec3(double data[3]);

        /**
         * Parameterized Vec3 constructor using double values
         * @param x Value x for Vec3
         * @param y Value y for Vec3
         * @param z Value z for Vec3
         */
        Vec3(double x, double y, double z);

        /**
         * Getter for x
         * @return Value x of Vec3
         */
        double x() const;

        /**
         * Getter for y
         * @return Value y of Vec3
         */
        double y() const;

        /**
         * Getter for z
         * @return Value z of Vec3
         */
        double z() const;


        /**
         * [] operator for Vec3
         * @param  i Index at which to evaluate
         * @return   Value copy at index i
         */
        double operator[](int i) const override;

        /**
         * + operator for Vec3
         * @param  otherVec Other vector which will be added
         * @return          Vec3 copy of the sum result
         */
        Vec3 operator+(const Vec3& otherVec) override;

        /**
         * - operator for Vec3
         * @param  otherVec Other vector which will be subtracted
         * @return          Vec3 copy of the subtraction result
         */
        Vec3 operator-(const Vec3& otherVec) override;

        /**
         * * operator for Vec3
         * @param  otherNum Other double which Vec3 will be multiplied by
         * @return          Vec3 copy of the multiplication result
         */
        Vec3 operator*(const double& otherNum) override;

        /**
         * / operator for Vec3
         * @param  otherNum Other double which Vec3 will be divided by
         * @return          Vec3 copy of the division result
         */
        Vec3 operator/(const double& otherNum) override;


        /**
         * Element wise product of 2 Vec3s
         * @param  otherVec Other vector which will be multiplied
         * @return          Vec3 copy of the elementwise product result
         */
        Vec3 elemProduct(const Vec3& otherVec) override;

        /**
         * Dot product of 2 Vec3s
         * @param  otherVec Other vector which will be dot producted
         * @return          Vec3 copy of the dot product result
         */
        double dot(const Vec3& otherVec) override;

        /**
         * Cross product of 2 Vec3s
         * @param  otherVec Other vector which will be cross producted
         * @return          Vec3 copy of the cross product result
         */
        Vec3 cross(const Vec3& otherVec) override;

        /**
         * Magnitude of Vec3
         * @return Magnitude of Vec3
         */
        double magnitude() override;

        /**
         * Normalized Vec3
         * @return Normalized Vec3
         */
        Vec3 normalize() override;

        /**
         * Cuts Vec3 entries to 1.0 if they're above 1.0
         */
        void cutToUnit() override;

        /**
         * Writes Vec3 data to std::out
         * @param out std::out to which the data is written to
         */
        void write_data(std::ostream& out) override;

};

// Aliases for Point3, Color3
using Point3 = Vec3;
using Color3 = Vec3;

#endif
