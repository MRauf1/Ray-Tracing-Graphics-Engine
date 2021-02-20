#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "../../src/objects/Plane.h"

#include <memory>

TEST_CASE("Test Plane constructor") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(1.0, 2.0, 3.0);
    Vec3 normal(-1.0, -2.0, -3.0);
    std::shared_ptr<Object> plane = std::make_shared<Plane>(color, position, normal);
    REQUIRE(position[0] == (std::dynamic_pointer_cast<Plane>(plane))->position()[0]);
    REQUIRE(position[1] == (std::dynamic_pointer_cast<Plane>(plane))->position()[1]);
    REQUIRE(position[2] == (std::dynamic_pointer_cast<Plane>(plane))->position()[2]);
    REQUIRE(normal[0] == (std::dynamic_pointer_cast<Plane>(plane))->normal()[0]);
    REQUIRE(normal[1] == (std::dynamic_pointer_cast<Plane>(plane))->normal()[1]);
    REQUIRE(normal[2] == (std::dynamic_pointer_cast<Plane>(plane))->normal()[2]);
}

TEST_CASE("Test Plane hit") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(0.0, 0.0, -3.0);
    Vec3 normal(0.0, 0.0, 1.0);
    std::shared_ptr<Object> plane = std::make_shared<Plane>(color, position, normal);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(true == plane->isHit(ray, 0.0, 100.0));
    REQUIRE(position.x() == plane->hitInfo().hitpoint[0]);
    REQUIRE(position.y() == plane->hitInfo().hitpoint[1]);
    REQUIRE(position.z() == plane->hitInfo().hitpoint[2]);
    REQUIRE(3.0 == plane->hitInfo().t);
}

TEST_CASE("Test Plane miss") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(1.0, 0.0, 0.0);
    Vec3 normal(1.0, 0.0, 0.0);
    std::shared_ptr<Object> plane = std::make_shared<Plane>(color, position, normal);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(false == plane->isHit(ray, 0.0, 100.0));
}

TEST_CASE("Test Plane miss because of t") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(0.0, 0.0, 3.0);
    Vec3 normal(0.0, 0.0, 1.0);
    std::shared_ptr<Object> plane = std::make_shared<Plane>(color, position, normal);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(false == plane->isHit(ray, 0.0, 100.0));
}
