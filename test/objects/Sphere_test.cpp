#include "../catch.hpp"
#include "../../src/objects/Sphere.h"

#include <memory>

TEST_CASE("Test Sphere constructor") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(1.0, 2.0, 3.0);
    double radius = 1.0;
    std::shared_ptr<Object> sphere = std::make_shared<Sphere>(color, position, radius);
    REQUIRE(position[0] == (std::dynamic_pointer_cast<Sphere>(sphere))->center()[0]);
    REQUIRE(position[1] == (std::dynamic_pointer_cast<Sphere>(sphere))->center()[1]);
    REQUIRE(position[2] == (std::dynamic_pointer_cast<Sphere>(sphere))->center()[2]);
    REQUIRE(radius == (std::dynamic_pointer_cast<Sphere>(sphere))->radius());
}

TEST_CASE("Test Sphere hit") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(0.0, 0.0, -3.0);
    double radius = 1.0;
    std::shared_ptr<Object> sphere = std::make_shared<Sphere>(color, position, radius);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(true == sphere->isHit(ray, 0.0, 100.0));
    REQUIRE(position.x() == sphere->hitInfo().hitpoint[0]);
    REQUIRE(position.y() == sphere->hitInfo().hitpoint[1]);
    REQUIRE(position.z() + radius == sphere->hitInfo().hitpoint[2]);
    REQUIRE(2.0 == sphere->hitInfo().t);
}

TEST_CASE("Test Sphere miss") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(10.0, 0.0, 0.0);
    double radius = 1.0;
    std::shared_ptr<Object> sphere = std::make_shared<Sphere>(color, position, radius);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(false == sphere->isHit(ray, 0.0, 100.0));
}

TEST_CASE("Test Sphere miss because of t") {
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(0.0, 0.0, 3.0);
    double radius = 1.0;
    std::shared_ptr<Object> sphere = std::make_shared<Sphere>(color, position, radius);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(false == sphere->isHit(ray, 0.0, 100.0));
}
