#include "../catch.hpp"
#include "../../src/objects/Mesh.h"

TEST_CASE("Test loading teapot mesh") {
    Color3 color(1.0, 1.0, 1.0);
    std::string file_name = "../../src/meshes/teapot.obj";
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(color, file_name);
    REQUIRE(6320 == mesh->objects().size());
}
