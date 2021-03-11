#include "catch.hpp"
#include "../src/Camera.h"

TEST_CASE("Test default Camera constructor") {
    Camera camera;
    double aspect_ratio = 16.0 / 9.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * aspect_ratio;
    double focal_length = 1.0;
    Point3 position(0.0, 0.0, 0.0);
    Vec3 hor_direction(viewport_width, 0.0, 0.0);
    Vec3 ver_direction(0.0, viewport_height, 0.0);
    Point3 lower_left = position - hor_direction / 2 - ver_direction / 2 - Vec3(0.0, 0.0, focal_length);
    REQUIRE(camera.aspect_ratio() == aspect_ratio);
    REQUIRE(camera.viewport_height() == viewport_height);
    REQUIRE(camera.viewport_width() == viewport_width);
    REQUIRE(camera.focal_length() == focal_length);
    REQUIRE(camera.position().x() == position.x());
    REQUIRE(camera.position().y() == position.y());
    REQUIRE(camera.position().z() == position.z());
}

TEST_CASE("Test non-default Camera constructor") {
    double aspect_ratio = 24.0 / 10.0;
    double viewport_height = 5.0;
    double viewport_width = viewport_height * aspect_ratio;
    double focal_length = 2.5;
    Point3 position(1.0, 2.0, 3.0);
    Vec3 hor_direction(viewport_width, 0.0, 0.0);
    Vec3 ver_direction(0.0, viewport_height, 0.0);
    Point3 lower_left = position - hor_direction / 2 - ver_direction / 2 - Vec3(0.0, 0.0, focal_length);
    Vec3 view_dir(0.0, 0.0, -1.0);
    Vec3 up_dir(0.0, 1.0, 0.0);
    Projection projection = PERSPECTIVE;
    Camera camera(aspect_ratio, viewport_height, focal_length, position, view_dir, up_dir, projection);
    REQUIRE(camera.aspect_ratio() == aspect_ratio);
    REQUIRE(camera.viewport_height() == viewport_height);
    REQUIRE(camera.viewport_width() == viewport_width);
    REQUIRE(camera.focal_length() == focal_length);
    REQUIRE(camera.position().x() == position.x());
    REQUIRE(camera.position().y() == position.y());
    REQUIRE(camera.position().z() == position.z());
}
