#include "../catch.hpp"
#include "../../src/data_structures/BVHNode.h"
#include "../../src/objects/Sphere.h"

TEST_CASE("Test BVH constructor for interior node (null object)") {
    std::shared_ptr<BVHNode> left = std::make_shared<BVHNode>();
    std::shared_ptr<BVHNode> right = std::make_shared<BVHNode>();
    Point3 min_point(-1.0, -1.0, -2.0);
    Point3 max_point(1.0, 1.0, -1.0);
    std::shared_ptr<AABB> aabb = std::make_shared<AABB>(min_point, max_point);
    std::shared_ptr<Object> object = nullptr;
    std::shared_ptr<BVHNode> bvh = std::make_shared<BVHNode>(left, right, aabb, object);
    REQUIRE(true == (min_point == bvh->aabb()->min_point()));
    REQUIRE(true == (max_point == bvh->aabb()->max_point()));
}

TEST_CASE("Test BVH constructor for leaf node (non-null object)") {
    std::shared_ptr<BVHNode> left = nullptr;
    std::shared_ptr<BVHNode> right = nullptr;
    Point3 min_point(-1.0, -1.0, -2.0);
    Point3 max_point(1.0, 1.0, -1.0);
    std::shared_ptr<AABB> aabb = std::make_shared<AABB>(min_point, max_point);
    Color3 color(1.0, 1.0, 1.0);
    Point3 center(0.0, 0.0, 0.0);
    double radius = 1.0;
    std::shared_ptr<Object> object = std::make_shared<Sphere>(color, center, radius);
    std::shared_ptr<BVHNode> bvh = std::make_shared<BVHNode>(left, right, aabb, object);
    REQUIRE(true == (min_point == bvh->aabb()->min_point()));
    REQUIRE(true == (max_point == bvh->aabb()->max_point()));
    REQUIRE(true == (color == bvh->object()->color()));
}
