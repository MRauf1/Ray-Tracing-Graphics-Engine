#ifndef BVHNODE_H
#define BVHNODE_H

#include "../objects/Object.h"
#include "AABB.h"
#include <memory>

class BVHNode {

    private:

        std::shared_ptr<BVHNode> left_;
        std::shared_ptr<BVHNode> right_;
        std::shared_ptr<AABB> aabb_;
        std::shared_ptr<Object> object_;


    public:

        /**
         * Default BVH constructor
         */
        BVHNode();

        BVHNode(std::shared_ptr<BVHNode> left, std::shared_ptr<BVHNode> right, std::shared_ptr<AABB> aabb, std::shared_ptr<Object> object);

        std::shared_ptr<BVHNode> left() const;

        std::shared_ptr<BVHNode> right() const;

        std::shared_ptr<AABB> aabb() const;

        std::shared_ptr<Object> object() const;

};

#endif
