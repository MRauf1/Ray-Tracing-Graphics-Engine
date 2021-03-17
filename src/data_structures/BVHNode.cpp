#include "BVHNode.h"

BVHNode::BVHNode() {

}

BVHNode::BVHNode(std::shared_ptr<BVHNode> left, std::shared_ptr<BVHNode> right, std::shared_ptr<AABB> aabb, std::shared_ptr<Object> object) {
    this->left_ = left;
    this->right_ = right;
    this->aabb_ = aabb;
    this->object_ = object;
}

std::shared_ptr<BVHNode> BVHNode::left() const {
    return this->left_;
}

std::shared_ptr<BVHNode> BVHNode::right() const {
    return this->right_;
}

std::shared_ptr<AABB> BVHNode::aabb() const {
    return this->aabb_;
}

std::shared_ptr<Object> BVHNode::object() const {
    return this->object_;
}
