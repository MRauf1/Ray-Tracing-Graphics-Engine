#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/World.h"

#include <memory>

// Background color
Color3 BACKGROUND(1.0, 1.0, 1.0);

// Image settings
double ASPECT_RATIO = 16.0 / 9.0;
int WIDTH = 256;

Image IMAGE(ASPECT_RATIO, WIDTH);

// Camera settings
double VIEWPORT_HEIGHT = 2.0;
double FOCAL_LENGTH = 1.0;
Point3 POSITION(0.0, 0.0, 0.0);

Camera CAMERA(ASPECT_RATIO, VIEWPORT_HEIGHT, FOCAL_LENGTH, POSITION);


TEST_CASE("Test World constructor") {
    World world(BACKGROUND, IMAGE, CAMERA);
    REQUIRE(BACKGROUND[0] == world.background_color()[0]);
    REQUIRE(BACKGROUND[1] == world.background_color()[0]);
    REQUIRE(BACKGROUND[2] == world.background_color()[0]);
    REQUIRE(true == world.objects().empty());
}

TEST_CASE("Test add object") {
    World world(BACKGROUND, IMAGE, CAMERA);
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(1.0, 0.0, 0.0);
    Vec3 normal(1.0, 0.0, 0.0);
    std::shared_ptr<Object> plane = std::make_shared<Plane>(color, position, normal);
    world.addObject(plane);
    REQUIRE(1 == world.objects().size());
    REQUIRE(plane == world.objects()[0]);
}

TEST_CASE("Test hitDetection with no objects") {
    World world(BACKGROUND, IMAGE, CAMERA);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(1.0, 1.0, 1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(nullptr == world.hitDetection(ray, 0.0, 100.0));
}

TEST_CASE("Test hitDetection with object, but no hit") {
    World world(BACKGROUND, IMAGE, CAMERA);
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(0.0, 0.0, 3.0);
    Vec3 normal(0.0, 0.0, 1.0);
    std::shared_ptr<Object> plane = std::make_shared<Plane>(color, position, normal);
    world.addObject(plane);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(nullptr == world.hitDetection(ray, 0.0, 100.0));
}

TEST_CASE("Test hitDetection with object and hit") {
    World world(BACKGROUND, IMAGE, CAMERA);
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(0.0, 0.0, -3.0);
    Vec3 normal(0.0, 0.0, 1.0);
    std::shared_ptr<Object> plane = std::make_shared<Plane>(color, position, normal);
    world.addObject(plane);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(plane == world.hitDetection(ray, 0.0, 100.0));
    REQUIRE(3.0 == world.objects()[0]->hitInfo().t);
}

TEST_CASE("Test hitDetection with multiple objects and closest hit") {
    World world(BACKGROUND, IMAGE, CAMERA);
    Color3 color1(0.5, 0.5, 0.5);
    Point3 position1(0.0, 0.0, -3.0);
    Vec3 normal1(0.0, 0.0, 1.0);
    std::shared_ptr<Object> plane1 = std::make_shared<Plane>(color1, position1, normal1);
    world.addObject(plane1);
    Color3 color2(0.5, 0.5, 0.5);
    Point3 position2(0.0, 0.0, -2.0);
    Vec3 normal2(0.0, 0.0, 1.0);
    std::shared_ptr<Object> plane2 = std::make_shared<Plane>(color2, position2, normal2);
    world.addObject(plane2);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(0.0, 0.0, -1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(plane2 == world.hitDetection(ray, 0.0, 100.0));
    REQUIRE(2.0 == world.objects()[1]->hitInfo().t);
}
