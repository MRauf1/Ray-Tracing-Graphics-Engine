#include "../catch.hpp"
#include "../../src/math/Vec3.h"
#include <cmath>

TEST_CASE("Test Vec3 constructor") {
    double testData[3] = {1, 2.1, 3.14};
    Vec3 testVec3(testData);
    REQUIRE(testData[0] == testVec3.x());
    REQUIRE(testData[1] == testVec3.y());
    REQUIRE(testData[2] == testVec3.z());
}

TEST_CASE("Test Vec3 operator[]") {
    double testData[3] = {1, 2.1, 3.14};
    Vec3 testVec3(testData);
    REQUIRE(testData[0] == testVec3[0]);
    REQUIRE(testData[1] == testVec3[1]);
    REQUIRE(testData[2] == testVec3[2]);
}

TEST_CASE("Test Vec3 addition") {
    double testData1[3] = {1, 2.1, 3.14};
    Vec3 test1Vec3(testData1);
    double testData2[3] = {3.54, -1.23, 7.5};
    Vec3 test2Vec3(testData2);
    Vec3 outputVec3 = test1Vec3 + test2Vec3;
    REQUIRE((testData1[0] + testData2[0]) == outputVec3.x());
    REQUIRE((testData1[1] + testData2[1]) == outputVec3.y());
    REQUIRE((testData1[2] + testData2[2]) == outputVec3.z());
}

TEST_CASE("Test Vec3 subtraction") {
    double testData1[3] = {-1.32, 4.15, 2.54};
    Vec3 test1Vec3(testData1);
    double testData2[3] = {1.23, -10.32, 9.8};
    Vec3 test2Vec3(testData2);
    Vec3 outputVec3 = test1Vec3 - test2Vec3;
    REQUIRE((testData1[0] - testData2[0]) == outputVec3.x());
    REQUIRE((testData1[1] - testData2[1]) == outputVec3.y());
    REQUIRE((testData1[2] - testData2[2]) == outputVec3.z());
}

TEST_CASE("Test Vec3 multiplication") {
    double testData[3] = {2, -52.1, 73.23};
    Vec3 testVec3(testData);
    double multiplier = 5.1;
    Vec3 outputVec3 = testVec3 * multiplier;
    REQUIRE((testData[0] * multiplier) == outputVec3.x());
    REQUIRE((testData[1] * multiplier) == outputVec3.y());
    REQUIRE((testData[2] * multiplier) == outputVec3.z());
}

TEST_CASE("Test Vec3 division") {
    double testData[3] = {0.9, -2.34, 5.43};
    Vec3 testVec3(testData);
    double divider = 0.9;
    Vec3 outputVec3 = testVec3 / divider;
    REQUIRE((testData[0] / divider) == outputVec3.x());
    REQUIRE((testData[1] / divider) == outputVec3.y());
    REQUIRE((testData[2] / divider) == outputVec3.z());
}

TEST_CASE("Test Vec3 dot") {
    double testData1[3] = {-1.32, 4.15, 2.54};
    Vec3 test1Vec3(testData1);
    double testData2[3] = {1.23, -10.32, 9.8};
    Vec3 test2Vec3(testData2);
    double dot = (testData1[0] * testData2[0]) + (testData1[1] * testData2[1]) + (testData1[2] * testData2[2]);
    REQUIRE(dot == test1Vec3.dot(test2Vec3));
}

TEST_CASE("Test Vec3 cross") {
    double testData1[3] = {2.0, 3.0, 4.0};
    Vec3 test1Vec3(testData1);
    double testData2[3] = {5.0, 6.0, 7.0};
    Vec3 test2Vec3(testData2);
    Vec3 outputVec3 = test1Vec3.cross(test2Vec3);
    REQUIRE(-3 == outputVec3[0]);
    REQUIRE(6 == outputVec3[1]);
    REQUIRE(-3 == outputVec3[2]);
}

TEST_CASE("Test Vec3 magnitude") {
    double testData[3] = {-1.32, 4.15, 2.54};
    Vec3 testVec3(testData);
    double dot = (testData[0] * testData[0]) + (testData[1] * testData[1]) + (testData[2] * testData[2]);
    double magnitude = std::sqrt(dot);
    REQUIRE(magnitude == testVec3.magnitude());
}

TEST_CASE("Test Vec3 normalize") {
    double testData[3] = {-1.32, 4.15, 2.54};
    Vec3 testVec3(testData);
    double dot = (testData[0] * testData[0]) + (testData[1] * testData[1]) + (testData[2] * testData[2]);
    double magnitude = std::sqrt(dot);
    Vec3 outputVec3 = testVec3 / magnitude;
    REQUIRE(outputVec3[0] == testVec3.normalize()[0]);
    REQUIRE(outputVec3[1] == testVec3.normalize()[1]);
    REQUIRE(outputVec3[2] == testVec3.normalize()[2]);
}
