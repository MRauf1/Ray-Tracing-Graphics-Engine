#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/math/Point3.cpp"

TEST_CASE("Test Point3 constructor") {
    double testData[3] = {1, 2.1, 3.14};
    Point3 testPoint3(testData);
    REQUIRE(testData[0] == testPoint3.x());
    REQUIRE(testData[1] == testPoint3.y());
    REQUIRE(testData[2] == testPoint3.z());
}

TEST_CASE("Test Point3 addition") {
    double testData1[3] = {1, 2.1, 3.14};
    Point3 test1Point3(testData1);
    double testData2[3] = {3.54, -1.23, 7.5};
    Point3 test2Point3(testData2);
    Point3 outputPoint3 = test1Point3 + test2Point3;
    REQUIRE((testData1[0] + testData2[0]) == outputPoint3.x());
    REQUIRE((testData1[1] + testData2[1]) == outputPoint3.y());
    REQUIRE((testData1[2] + testData2[2]) == outputPoint3.z());
}

TEST_CASE("Test Point3 subtraction") {
    double testData1[3] = {-1.32, 4.15, 2.54};
    Point3 test1Point3(testData1);
    double testData2[3] = {1.23, -10.32, 9.8};
    Point3 test2Point3(testData2);
    Point3 outputPoint3 = test1Point3 - test2Point3;
    REQUIRE((testData1[0] - testData2[0]) == outputPoint3.x());
    REQUIRE((testData1[1] - testData2[1]) == outputPoint3.y());
    REQUIRE((testData1[2] - testData2[2]) == outputPoint3.z());
}

TEST_CASE("Test Point3 multiplication") {
    double testData[3] = {2, -52.1, 73.23};
    Point3 testPoint3(testData);
    double multiplier = 5.1;
    Point3 outputPoint3 = testPoint3 * multiplier;
    REQUIRE((testData[0] * multiplier) == outputPoint3.x());
    REQUIRE((testData[1] * multiplier) == outputPoint3.y());
    REQUIRE((testData[2] * multiplier) == outputPoint3.z());
}

TEST_CASE("Test Point3 division") {
    double testData[3] = {0.9, -2.34, 5.43};
    Point3 testPoint3(testData);
    double divider = 0.9;
    Point3 outputPoint3 = testPoint3 / divider;
    REQUIRE((testData[0] / divider) == outputPoint3.x());
    REQUIRE((testData[1] / divider) == outputPoint3.y());
    REQUIRE((testData[2] / divider) == outputPoint3.z());
}
