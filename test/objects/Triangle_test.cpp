#include "../catch.hpp"
#include "../../src/objects/Triangle.h"

#include <memory>

TEST_CASE("Test Triangle constructor") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 point1(-0.5, -1.0, -3.0);
    Point3 point2(-0.5, 1.0, -3.0);
    Point3 point3(1.0, -1.0, -3.0);
    std::shared_ptr<Object> triangle = std::make_shared<Triangle>(color, point1, point2, point3);
    REQUIRE(point1[0] == (std::dynamic_pointer_cast<Triangle>(triangle))->point1()[0]);
    REQUIRE(point1[1] == (std::dynamic_pointer_cast<Triangle>(triangle))->point1()[1]);
    REQUIRE(point1[2] == (std::dynamic_pointer_cast<Triangle>(triangle))->point1()[2]);
    REQUIRE(point2[0] == (std::dynamic_pointer_cast<Triangle>(triangle))->point2()[0]);
    REQUIRE(point2[1] == (std::dynamic_pointer_cast<Triangle>(triangle))->point2()[1]);
    REQUIRE(point2[2] == (std::dynamic_pointer_cast<Triangle>(triangle))->point2()[2]);
    REQUIRE(point3[0] == (std::dynamic_pointer_cast<Triangle>(triangle))->point3()[0]);
    REQUIRE(point3[1] == (std::dynamic_pointer_cast<Triangle>(triangle))->point3()[1]);
    REQUIRE(point3[2] == (std::dynamic_pointer_cast<Triangle>(triangle))->point3()[2]);
}

TEST_CASE("Test Triangle hit") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 point1(-0.5, -1.0, -3.0);
    Point3 point2(-0.5, 3.0, -3.0);
    Point3 point3(1.0, -1.0, -3.0);
    std::shared_ptr<Object> triangle = std::make_shared<Triangle>(color, point1, point2, point3);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(true == triangle->isHit(ray, 0.0, 100.0));
    REQUIRE(rayPoint[0] == triangle->hitInfo().hitpoint[0]);
    REQUIRE(rayPoint[1] == triangle->hitInfo().hitpoint[1]);
    REQUIRE(-3.0 == triangle->hitInfo().hitpoint[2]);
    REQUIRE(3.0 == triangle->hitInfo().t);
}

TEST_CASE("Test Triangle miss") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 point1(-5.5, -1.0, -3.0);
    Point3 point2(-5.5, 3.0, -3.0);
    Point3 point3(-3.0, -1.0, -3.0);
    std::shared_ptr<Object> triangle = std::make_shared<Triangle>(color, point1, point2, point3);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(false == triangle->isHit(ray, 0.0, 100.0));
}

TEST_CASE("Test Triangle miss because of t") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 point1(-0.5, -1.0, 3.0);
    Point3 point2(-0.5, 3.0, 3.0);
    Point3 point3(1.0, -1.0, 3.0);
    std::shared_ptr<Object> triangle = std::make_shared<Triangle>(color, point1, point2, point3);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(false == triangle->isHit(ray, 0.0, 100.0));
}
