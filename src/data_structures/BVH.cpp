#include "BVH.h"

BVH::BVH() {

}

BVH::BVH(std::vector<std::shared_ptr<Object>> objects) {
    this->objects_ = objects;
    std::sort(this->objects_.begin(), this->objects_.end(), compareObject);
    this->root_ = this->createBVH(0, this->objects_.size() - 1);
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
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();
    double maxZ = std::numeric_limits<double>::lowest();
    // Go through all the points
    for(int k = i; k <= j; k++) {
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

std::shared_ptr<BVHNode> BVH::createBVH(int i, int j) {
    // Leaf node
    if(i == j) {
        std::shared_ptr<AABB> aabb = this->createAABB(i, j);
        std::shared_ptr<BVHNode> node = std::make_shared<BVHNode>(nullptr, nullptr, aabb, this->objects_[i]);
        return node;
    }
    // Interior node
    std::shared_ptr<BVHNode> left = this->createBVH(i, i + (int) ((j - i) / 2));
    std::shared_ptr<BVHNode> right = this->createBVH(i + (int) ((j - i) / 2) + 1, j);
    std::shared_ptr<AABB> aabb = this->createAABB(i, j);
    std::shared_ptr<BVHNode> node = std::make_shared<BVHNode>(left, right, aabb, nullptr);
    return node;
}

std::shared_ptr<Object> BVH::detectHit(Ray& ray) {
    return this->detectHitHelper(ray, this->root_);
}

std::shared_ptr<Object> BVH::detectHitHelper(Ray& ray, std::shared_ptr<BVHNode> curr) {
    // If ray misses node's AABB, no hit, so return nullptr
    if(!(curr->aabb()->isHit(ray))) {
        return nullptr;
    }
    // Check if leaf node
    if(curr->left() == nullptr && curr->right() == nullptr) {
        // If ray hits the object, return this object
        if(curr->object()->isHit(ray, 0, 999999)) {
            return curr->object();
        }
        // Else, return nullptr
        return nullptr;
    }
    std::shared_ptr<Object> output = this->detectHitHelper(ray, curr->left());
    if(output != nullptr) {
        return output;
    }
    output = this->detectHitHelper(ray, curr->right());
    return output;
}


bool compareObject(std::shared_ptr<Object> object1, std::shared_ptr<Object> object2) {
    double curr = object1->aabb()->min_point()[0] + (object1->aabb()->max_point()[0] - object1->aabb()->min_point()[0]) / 2;
    double other = object2->aabb()->min_point()[0] + (object2->aabb()->max_point()[0] - object2->aabb()->min_point()[0]) / 2;
    return curr < other;
}
