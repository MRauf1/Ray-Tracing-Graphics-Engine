#ifndef MESH_H
#define MESH_H

#include "../math/Vec3.h"
#include "Object.h"
#include "Triangle.h"
#include "../data_structures/BVH.h"
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Mesh : public Object {

    private:

        std::vector<std::shared_ptr<Object>> objects_;
        std::vector<Point3> vertices_;
        std::vector<std::vector<int>> faces_;
        std::vector<Vec3> vertex_normals_;
        BVH bvh_;


    public:

        /**
         * Default Mesh constructor
         */
        Mesh();

        Mesh(Color3 color, std::string file_name);

        std::vector<std::shared_ptr<Object>> objects() const;

        void readMesh(std::string file_name);

        void calculateVertexNormals();

        bool isHit(Ray& ray, double minT, double maxT) override;

        void makeAABB() override;

};

#endif
