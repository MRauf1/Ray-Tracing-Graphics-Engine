#include "../catch.hpp"
#include "../../src/data_structures/AABB.h"

TEST_CASE("Test default AABB constructor") {
    AABB aabb;
    Point3 min_point(-1.0, -1.0, -1.0);
    Point3 max_point(1.0, 1.0, 1.0);
    REQUIRE(true == (min_point == aabb.min_point()));
    REQUIRE(true == (max_point == aabb.max_point()));
}

TEST_CASE("Test non-default AABB constructor") {
    Point3 min_point(-2.0, -3.0, -4.0);
    Point3 max_point(2.0, 1.0, 5.0);
    AABB aabb(min_point, max_point);
    REQUIRE(true == (min_point == aabb.min_point()));
    REQUIRE(true == (max_point == aabb.max_point()));
}

TEST_CASE("Test x-slab hit") {
    Point3 min_point(-1.0, -1.0, -2.0);
    Point3 max_point(1.0, 1.0, -1.0);
    AABB aabb(min_point, max_point);
    Point3 origin(-2.0, 0.0, -1.5);
    Vec3 direction(1.0, 0.0, 0.0);
    Ray ray(origin, direction);
    REQUIRE(true == aabb.isHit(ray));
}

TEST_CASE("Test y-slab hit") {
    Point3 min_point(-1.0, -1.0, -2.0);
    Point3 max_point(1.0, 1.0, -1.0);
    AABB aabb(min_point, max_point);
    Point3 origin(0.0, -2.0, -1.5);
    Vec3 direction(0.0, 1.0, 0.0);
    Ray ray(origin, direction);
    REQUIRE(true == aabb.isHit(ray));
}

TEST_CASE("Test z-slab hit") {
    Point3 min_point(-1.0, -1.0, -2.0);
    Point3 max_point(1.0, 1.0, -1.0);
    AABB aabb(min_point, max_point);
    Point3 origin(0.0, 0.0, -3.0);
    Vec3 direction(0.0, 0.0, 1.0);
    Ray ray(origin, direction);
    REQUIRE(true == aabb.isHit(ray));
}

TEST_CASE("Test x-slab miss when ray is past it") {
    Point3 min_point(-1.0, -1.0, -2.0);
    Point3 max_point(1.0, 1.0, -1.0);
    AABB aabb(min_point, max_point);
    Point3 origin(-2.0, 0.0, -1.5);
    Vec3 direction(-1.0, 0.0, 0.0);
    Ray ray(origin, direction);
    REQUIRE(false == aabb.isHit(ray));
}

TEST_CASE("Test y-slab miss when ray is past it") {
    Point3 min_point(-1.0, -1.0, -2.0);
    Point3 max_point(1.0, 1.0, -1.0);
    AABB aabb(min_point, max_point);
    Point3 origin(0.0, -2.0, -1.5);
    Vec3 direction(0.0, -1.0, 0.0);
    Ray ray(origin, direction);
    REQUIRE(false == aabb.isHit(ray));
}

TEST_CASE("Test z-slab miss when ray is past it") {
    Point3 min_point(-1.0, -1.0, -2.0);
    Point3 max_point(1.0, 1.0, -1.0);
    AABB aabb(min_point, max_point);
    Point3 origin(0.0, 0.0, -3.0);
    Vec3 direction(0.0, 0.0, -1.0);
    Ray ray(origin, direction);
    REQUIRE(false == aabb.isHit(ray));
}

TEST_CASE("Test diagonal hit") {
    Point3 min_point(-1.0, -1.0, -2.0);
    Point3 max_point(1.0, 1.0, -1.0);
    AABB aabb(min_point, max_point);
    Point3 origin(-2.0, -2.0, -1.5);
    Vec3 direction(1.0, 1.0, 0.0);
    Ray ray(origin, direction);
    REQUIRE(true == aabb.isHit(ray));
}

TEST_CASE("Test 0 length hit") {
    Point3 min_point(0.0, -1.0, -2.0);
    Point3 max_point(0.0, 1.0, -1.0);
    AABB aabb(min_point, max_point);
    Point3 origin(1.0, 0.0, -1.5);
    Vec3 direction(-1.0, 0.0, 0.0);
    Ray ray(origin, direction);
    REQUIRE(true == aabb.isHit(ray));
}

TEST_CASE("Test 0 height hit") {
    Point3 min_point(-1.0, 0.0, -2.0);
    Point3 max_point(1.0, 0.0, -1.0);
    AABB aabb(min_point, max_point);
    Point3 origin(0.0, 1.0, -1.5);
    Vec3 direction(0.0, -1.0, 0.0);
    Ray ray(origin, direction);
    REQUIRE(true == aabb.isHit(ray));
}

TEST_CASE("Test 0 depth hit") {
    Point3 min_point(-3.0, -1.0, -1.0);
    Point3 max_point(3.0, 3.0, -1.0);
    AABB aabb(min_point, max_point);
    Point3 origin(0.0, 0.0, 0.0);
    Vec3 direction(0.0, 0.0, -1.0);
    Ray ray(origin, direction);
    REQUIRE(true == aabb.isHit(ray));
}
