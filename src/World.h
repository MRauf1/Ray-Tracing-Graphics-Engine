#ifndef WORLD_H
#define WORLD_H

#include "math/Vec3.h"
#include "image/Image.h"
#include "Camera.h"
#include "objects/Object.h"
#include "objects/Plane.h"
#include <vector>
#include <memory>
#include <iostream>
#include <limits>

class World {

    private:
        Color3 background_color_;
        Image image_;
        Camera camera_;
        std::vector<std::shared_ptr<Object>> objects_;

    public:
        World();
        World(Color3 background_color, Image image, Camera camera);
        Color3 background_color() const;
        Image image() const;
        Camera camera() const;
        std::vector<std::shared_ptr<Object>> objects() const;

        void addObject(std::shared_ptr<Object> object);
        std::shared_ptr<Object> hitDetection(Ray& ray, double minT, double maxT);
        // void render();

};

#endif
