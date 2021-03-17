#include "../catch.hpp"
#include "../../src/data_structures/BVH.h"
#include "../../src/objects/Sphere.h"
#include <iostream>

TEST_CASE("Test BVH objects are sorted by midpoint") {
    std::shared_ptr<BVHNode> root = std::make_shared<BVHNode>();
    Color3 color(1.0, 1.0, 1.0);
    Point3 center(0.0, 0.0, 0.0);
    double radius1 = 3.0;
    double radius2 = 2.0;
    double radius3 = 4.0;
    std::shared_ptr<Object> object1 = std::make_shared<Sphere>(color, center, radius1);
    std::shared_ptr<Object> object2 = std::make_shared<Sphere>(color, center, radius2);
    std::shared_ptr<Object> object3 = std::make_shared<Sphere>(color, center, radius3);
    std::vector<std::shared_ptr<Object>> objects;
    objects.push_back(object1);
    objects.push_back(object2);
    objects.push_back(object3);
    BVH bvh(root, objects);
    std::vector<std::shared_ptr<Object>> output = bvh.objects();
    REQUIRE(true == (output[0] == objects[1]));
    REQUIRE(true == (output[1] == objects[0]));
    REQUIRE(true == (output[2] == objects[2]));
}

TEST_CASE("Test BVH AABB for the root node") {
    std::shared_ptr<BVHNode> root = std::make_shared<BVHNode>();
    Color3 color(1.0, 1.0, 1.0);
    Point3 center1(0.0, 0.0, 0.0);
    Point3 center2(5.0, 2.0, 0.0);
    Point3 center3(7.0, 0.0, 1.0);
    double radius1 = 3.0;
    double radius2 = 2.0;
    double radius3 = 4.0;
    std::shared_ptr<Object> object1 = std::make_shared<Sphere>(color, center1, radius1);
    std::shared_ptr<Object> object2 = std::make_shared<Sphere>(color, center2, radius2);
    std::shared_ptr<Object> object3 = std::make_shared<Sphere>(color, center3, radius3);
    std::vector<std::shared_ptr<Object>> objects;
    objects.push_back(object1);
    objects.push_back(object2);
    objects.push_back(object3);
    BVH bvh(root, objects);
    std::shared_ptr<AABB> aabb = bvh.createAABB(0, objects.size());
    Point3 min_point(-3.0, -4.0, -3.0);
    Point3 max_point(11.0, 4.0, 5.0);
    REQUIRE(true == (aabb->min_point() == min_point));
    REQUIRE(true == (aabb->max_point() == max_point));
}
