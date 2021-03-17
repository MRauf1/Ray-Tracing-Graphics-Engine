#include "../catch.hpp"
#include "../../src/objects/Object.h"
#include "../../src/objects/Sphere.h"

#include <memory>

TEST_CASE("Test Object comparison") {
    Color3 color1(0.5, 0.5, 0.5);
    Point3 center1(1.0, 2.0, 3.0);
    double radius1 = 1.0;
    std::shared_ptr<Object> object1 = std::make_shared<Sphere>(color1, center1, radius1);
    Color3 color2(0.5, 0.5, 0.5);
    Point3 center2(3.0, 2.0, 3.0);
    double radius2 = 2.0;
    std::shared_ptr<Object> object2 = std::make_shared<Sphere>(color2, center2, radius2);
    REQUIRE(true == (object1 < object2));
}
