#include "../catch.hpp"
#include "../../src/objects/Mesh.h"

TEST_CASE("Test Teapot Mesh") {
    std::string file_name = "../../src/meshes/teapot.obj";
    Mesh mesh(file_name);
    // Point3 min_point(-1.0, -1.0, -1.0);
    // Point3 max_point(1.0, 1.0, 1.0);
    // REQUIRE(true == (min_point == aabb.min_point()));
    // REQUIRE(true == (max_point == aabb.max_point()));
}
