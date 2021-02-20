#ifndef WORLD_H
#define WORLD_H

#include "Projection.h"
#include "math/Vec3.h"
#include "math/Ray.h"
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
        Projection projection_;
        Color3 background_color_;
        Image image_;
        Camera camera_;
        std::vector<std::shared_ptr<Object>> objects_;

    public:
        World();
        World(Projection projection_, Color3 background_color, Image image, Camera camera);
        Projection projection() const;
        Color3 background_color() const;
        Image image() const;
        Camera camera() const;
        std::vector<std::shared_ptr<Object>> objects() const;

        Ray createRay(int i, int j);
        void addObject(std::shared_ptr<Object> object);
        std::shared_ptr<Object> hitDetection(Ray& ray, double minT, double maxT);
        void render(double minT, double maxT);

};

#endif
