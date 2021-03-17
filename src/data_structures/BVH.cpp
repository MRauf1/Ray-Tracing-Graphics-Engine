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

bool compareObject(std::shared_ptr<Object> object1, std::shared_ptr<Object> object2) {
    double curr = (object1->aabb()->max_point()[0] - object1->aabb()->min_point()[0]) / 2;
    double other = (object2->aabb()->max_point()[0] - object2->aabb()->min_point()[0]) / 2;
    return curr < other;
}
