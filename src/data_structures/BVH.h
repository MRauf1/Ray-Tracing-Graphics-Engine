#ifndef BVH_H
#define BVH_H

#include "BVHNode.h"
#include "../objects/Object.h"
#include <memory>
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

class BVH {

    private:

        std::shared_ptr<BVHNode> root_;
        std::vector<std::shared_ptr<Object>> objects_;


    public:

        /**
         * Default BVH constructor
         */
        BVH();

        /**
         * Parameterized BVH constructor
         * @param objects Vector of objects to put inside the BVH
         */
        BVH(std::vector<std::shared_ptr<Object>> objects);

        /**
         * Getter for root
         * @return Root of BVH
         */
        std::shared_ptr<BVHNode> root() const;

        /**
         * Getter for objects
         * @return Objects inside BVH
         */
        std::vector<std::shared_ptr<Object>> objects() const;

        /**
         * Helper function to create AABB for a BVHNode inside the BVH
         * For determining which objects are inside the current node, the list
         * of objects of BVH and the starting and ending indices are used,
         * since the list of objects is sorted (median partitioning is used)
         * @param  i Starting index for the list of objects
         * @param  j Ending index for the list of objects
         * @return   Pointer to the AABB for the current BVHNode
         */
        std::shared_ptr<AABB> createAABB(int i, int j);

        /**
         * Recursive function responsible for creating the BVH by recursing
         * on the BVHNodes and initializing them appropriately
         * @param  i Starting index for the list of objects
         * @param  j Ending index for the list of objects
         * @return   Pointer to the created BVHNode
         */
        std::shared_ptr<BVHNode> createBVH(int i, int j);

        /**
         * Main function for detecting a hit using BVH
         * @param  ray Ray to check collision against
         * @return     Pointer to the object that has been hit (if none, then nullptr)
         */
        std::shared_ptr<Object> detectHit(Ray& ray);

        /**
         * Helper function for detecting a hit using BVH
         * Uses the inputted BVHNode to recurse through the BVH
         * @param  ray  Ray to check collision against
         * @param  curr Pointer to the current BVHNode to check
         * @return      Pointer to the object that has been hit (if none, then nullptr)
         */
        std::shared_ptr<Object> detectHitHelper(Ray& ray, std::shared_ptr<BVHNode> curr);

};

/**
 * Helper function used to help sort objects based on their AABB
 * @param  object1 First object to compare
 * @param  object2 Second object to compare
 * @return         Boolean for which one is greater (True if first is less)
 */
bool compareObject(std::shared_ptr<Object> object1, std::shared_ptr<Object> object2);

#endif
