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

        /**
         * Parameterized Mesh constructor
         * @param color     Color of the mesh
         * @param file_name File name of the mesh in .obj format
         */
        Mesh(Color3 color, std::string file_name);

        /**
         * Getter for objects
         * @return Vector of pointers to the objects of the mesh
         */
        std::vector<std::shared_ptr<Object>> objects() const;

        /**
         * Utility function for reading in the mesh in .obj format from
         * the specified path
         * @param file_name File name of the mesh in .obj format
         */
        void readMesh(std::string file_name);

        /**
         * Calculates and stores the per-vertex normals using triangle
         * area-weighting
         */
        void calculateVertexNormals();

        /**
         * Given the ray, check whether the ray hits the mesh
         * If it does, check whether it hits within the appropriate
         * t value (using minT and maxT)
         * If it does, return true and store the hit information inside
         * plane's hitInfo variable
         * Otherwise, return false
         * @param  ray  Ray to test the hit for
         * @param  minT Minimum t value to be considered a hit
         * @param  maxT Maximum t value to be considered a hit
         * @return      Bool for whether the mesh was hit or not
         */
        bool isHit(Ray& ray, double minT, double maxT) override;

        /**
         * Creates and stores the AABB for the object
         */
        void makeAABB() override;

        std::string subclass() override;

};

#endif
