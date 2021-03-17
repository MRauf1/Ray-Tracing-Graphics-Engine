#ifndef BVH_H
#define BVH_H

#include "BVHNode.h"
#include "../objects/Object.h"
#include <memory>
#include <vector>
#include <algorithm>
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

        BVH(std::shared_ptr<BVHNode> root, std::vector<std::shared_ptr<Object>> objects);

        std::shared_ptr<BVHNode> root() const;

        std::vector<std::shared_ptr<Object>> objects() const;

};

bool compareObject(std::shared_ptr<Object> object1, std::shared_ptr<Object> object2);

#endif
