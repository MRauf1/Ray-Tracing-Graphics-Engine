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

        /**
         * Parameterized BVHNode constructor
         * @param left   Left subtree
         * @param right  Right subtree
         * @param aabb   AABB for the current BVHNode
         * @param object Object inside the current BVHNode
         */
        BVHNode(std::shared_ptr<BVHNode> left, std::shared_ptr<BVHNode> right, std::shared_ptr<AABB> aabb, std::shared_ptr<Object> object);

        /**
         * Getter for left
         * @return Pointer to the left subtree
         */
        std::shared_ptr<BVHNode> left() const;

        /**
         * Getter for right
         * @return Pointer to the right subtree
         */
        std::shared_ptr<BVHNode> right() const;

        /**
         * Getter for AABB
         * @return Pointer to the AABB of the current BVHNode
         */
        std::shared_ptr<AABB> aabb() const;

        /**
         * Getter for object
         * @return Pointer to the object within the current BVHNode
         */
        std::shared_ptr<Object> object() const;

};

#endif
