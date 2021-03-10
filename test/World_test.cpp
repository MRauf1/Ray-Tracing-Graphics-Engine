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
Vec3 VIEW_DIR(0.0, 0.0, -1.0); // VIEW_DIR and UP_DIR can't be parallel
Vec3 UP_DIR(0.0, 1.0, 0.0);
Projection PROJECTION = PERSPECTIVE;

Camera CAMERA(ASPECT_RATIO, VIEWPORT_HEIGHT, FOCAL_LENGTH, POSITION, VIEW_DIR, UP_DIR, PROJECTION);

// World settings
int SAMPLES = 16;

TEST_CASE("Test World constructor") {
    World world(BACKGROUND, IMAGE, CAMERA, SAMPLES);
    REQUIRE(BACKGROUND[0] == world.background_color()[0]);
    REQUIRE(BACKGROUND[1] == world.background_color()[0]);
    REQUIRE(BACKGROUND[2] == world.background_color()[0]);
    REQUIRE(true == world.objects().empty());
}

TEST_CASE("Test add object") {
    World world(BACKGROUND, IMAGE, CAMERA, SAMPLES);
    Color3 color(0.5, 0.5, 0.5);
    Point3 position(1.0, 0.0, 0.0);
    Vec3 normal(1.0, 0.0, 0.0);
    std::shared_ptr<Object> plane = std::make_shared<Plane>(color, position, normal);
    world.addObject(plane);
    REQUIRE(1 == world.objects().size());
    REQUIRE(plane == world.objects()[0]);
}

TEST_CASE("Test hitDetection with no objects") {
    World world(BACKGROUND, IMAGE, CAMERA, SAMPLES);
    Point3 rayPoint(0.0, 0.0, 0.0);
    Vec3 rayDirection(1.0, 1.0, 1.0);
    Ray ray(rayPoint, rayDirection);
    REQUIRE(nullptr == world.hitDetection(ray, 0.0, 100.0));
}

TEST_CASE("Test hitDetection with object, but no hit") {
    World world(BACKGROUND, IMAGE, CAMERA, SAMPLES);
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
    World world(BACKGROUND, IMAGE, CAMERA, SAMPLES);
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
    World world(BACKGROUND, IMAGE, CAMERA, SAMPLES);
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

// TEST_CASE("Test litColor") {
//     World world(PERSPECTIVE, BACKGROUND, IMAGE, CAMERA);
//     Color3 color1(1.0, 0.0, 0.0);
//     Point3 position1(0.0, 0.0, -10.0);
//     Vec3 normal1(0.0, 0.0, 1.0);
//     std::shared_ptr<Object> plane1 = std::make_shared<Plane>(color1, position1, normal1);
//     world.addObject(plane1);
//     Point3 positionLight1(-1.0, 0.0, 0.0);
//     std::shared_ptr<PointLight> pointLight1 = std::make_shared<PointLight>(positionLight1);
//     world.addLight(pointLight1);
//     Color3 outputColor = world.litColor(plane1);
//     std::cout << outputColor[0] << std::endl;
//     std::cout << outputColor[1] << std::endl;
//     std::cout << outputColor[2] << std::endl;
// }

// TEST_CASE("Test render") {
//     World world(PERSPECTIVE, BACKGROUND, IMAGE, CAMERA);
//     Color3 color1(1.0, 0.0, 0.0);
//     Point3 position1(0.0, 0.0, -10.0);
//     Vec3 normal1(0.0, 0.0, 1.0);
//     std::shared_ptr<Object> plane1 = std::make_shared<Plane>(color1, position1, normal1);
//     world.addObject(plane1);
//     world.render(0.0, 100.0);
// }
