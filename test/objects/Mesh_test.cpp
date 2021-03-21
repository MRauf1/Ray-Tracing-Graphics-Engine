#include "../catch.hpp"
#include "../../src/objects/Mesh.h"

TEST_CASE("Test loading teapot mesh") {
    Color3 color(1.0, 1.0, 1.0);
    std::string file_name = "../../src/meshes/teapot.obj";
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(color, file_name);
    REQUIRE(6320 == mesh->objects().size());
}

TEST_CASE("Test teapot mesh hit") {
    Color3 color(1.0, 1.0, 1.0);
    std::string file_name = "../../src/meshes/teapot.obj";
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(color, file_name);
    Point3 origin(0.0, 1.0, 5.0);
    Vec3 direction(0.0, 0.0, -1.0);
    Ray ray(origin, direction);
    REQUIRE(true == mesh->isHit(ray, 0.0, 9999.0));
}
