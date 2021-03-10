#include "../catch.hpp"
#include "../../src/math/Ray.h"

TEST_CASE("Test Ray constructor") {
    double testPointData[3] = {1, 2.1, 3.14};
    Point3 testPoint(testPointData);
    double testDirectionData[3] = {0.1, 1.4, 5.4};
    Vec3 testDirection(testDirectionData);
    Ray testRay(testPoint, testDirection);
    REQUIRE(testPointData[0] == testRay.origin()[0]);
    REQUIRE(testPointData[1] == testRay.origin()[1]);
    REQUIRE(testPointData[2] == testRay.origin()[2]);
    REQUIRE(testDirectionData[0] == testRay.direction()[0]);
    REQUIRE(testDirectionData[1] == testRay.direction()[1]);
    REQUIRE(testDirectionData[2] == testRay.direction()[2]);
}

TEST_CASE("Test Ray at with negative t") {
    double testPointData[3] = {1, 2.1, 3.14};
    Point3 testPoint(testPointData);
    double testDirectionData[3] = {0.1, 1.4, 5.4};
    Vec3 testDirection(testDirectionData);
    Ray testRay(testPoint, testDirection);
    double t = -2.0;
    Point3 output = testRay.at(t);
    REQUIRE((testPointData[0] + t * testDirectionData[0]) == output[0]);
    REQUIRE((testPointData[0] + t * testDirectionData[0]) == output[0]);
    REQUIRE((testPointData[0] + t * testDirectionData[0]) == output[0]);
}

TEST_CASE("Test Ray at with t = 0") {
    double testPointData[3] = {1, 2.1, 3.14};
    Point3 testPoint(testPointData);
    double testDirectionData[3] = {0.1, 1.4, 5.4};
    Vec3 testDirection(testDirectionData);
    Ray testRay(testPoint, testDirection);
    double t = 0.0;
    Point3 output = testRay.at(t);
    REQUIRE((testPointData[0] + t * testDirectionData[0]) == output[0]);
    REQUIRE((testPointData[0] + t * testDirectionData[0]) == output[0]);
    REQUIRE((testPointData[0] + t * testDirectionData[0]) == output[0]);
}

TEST_CASE("Test Ray at with positive t") {
    double testPointData[3] = {1, 2.1, 3.14};
    Point3 testPoint(testPointData);
    double testDirectionData[3] = {0.1, 1.4, 5.4};
    Vec3 testDirection(testDirectionData);
    Ray testRay(testPoint, testDirection);
    double t = 3.1;
    Point3 output = testRay.at(t);
    REQUIRE((testPointData[0] + t * testDirectionData[0]) == output[0]);
    REQUIRE((testPointData[0] + t * testDirectionData[0]) == output[0]);
    REQUIRE((testPointData[0] + t * testDirectionData[0]) == output[0]);
}
