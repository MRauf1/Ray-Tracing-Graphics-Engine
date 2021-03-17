#include "BVH.h"

BVH::BVH() {

}

BVH::BVH(std::shared_ptr<BVHNode> root, std::vector<std::shared_ptr<Object>> objects) {
    this->root_ = root;
    this->objects_ = objects;
    std::sort(this->objects_.begin(), this->objects_.end(), compareObject);
}

std::shared_ptr<BVHNode> BVH::root() const {
    return this->root_;
}

std::vector<std::shared_ptr<Object>> BVH::objects() const {
    return this->objects_;
}

std::shared_ptr<AABB> BVH::createAABB(int i, int j) {
    // For leaf nodes, return the object's AABB
    if(i == j) {
        return this->objects_[i]->aabb();
    }
    // Initialize values for the min and max points
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::min();
    double maxY = std::numeric_limits<double>::min();
    double maxZ = std::numeric_limits<double>::min();
    // Go through all the points
    for(int k = i; k < j; k++) {
        // Update the minimums and maximums
        minX = std::min(minX, this->objects_[k]->aabb()->min_point()[0]);
        minY = std::min(minY, this->objects_[k]->aabb()->min_point()[1]);
        minZ = std::min(minZ, this->objects_[k]->aabb()->min_point()[2]);
        maxX = std::max(maxX, this->objects_[k]->aabb()->max_point()[0]);
        maxY = std::max(maxY, this->objects_[k]->aabb()->max_point()[1]);
        maxZ = std::max(maxZ, this->objects_[k]->aabb()->max_point()[2]);
    }
    // Create the AABB and return it
    Point3 min_point(minX, minY, minZ);
    Point3 max_point(maxX, maxY, maxZ);
    std::shared_ptr<AABB> aabb = std::make_shared<AABB>(min_point, max_point);
    return aabb;
}

bool compareObject(std::shared_ptr<Object> object1, std::shared_ptr<Object> object2) {
    double curr = (object1->aabb()->max_point()[0] - object1->aabb()->min_point()[0]) / 2;
    double other = (object2->aabb()->max_point()[0] - object2->aabb()->min_point()[0]) / 2;
    return curr < other;
}
