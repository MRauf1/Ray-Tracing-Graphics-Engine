#ifndef WORLD_H
#define WORLD_H

#include "Projection.h"
#include "math/Vec3.h"
#include "math/Ray.h"
#include "image/Image.h"
#include "Camera.h"
#include "objects/Object.h"
#include "objects/Plane.h"
#include "objects/Sphere.h"
#include "objects/Triangle.h"
#include "lights/PointLight.h"
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
        std::vector<std::shared_ptr<PointLight>> lights_;

    public:
        World();
        World(Projection projection_, Color3 background_color, Image image, Camera camera);
        Projection projection() const;
        Color3 background_color() const;
        Image image() const;
        Camera camera() const;
        std::vector<std::shared_ptr<Object>> objects() const;
        std::vector<std::shared_ptr<PointLight>> lights() const;

        Ray createRay(int i, int j);
        void addObject(std::shared_ptr<Object> object);
        void addLight(std::shared_ptr<PointLight> light);
        std::shared_ptr<Object> hitDetection(Ray& ray, double minT, double maxT);
        Color3 litColor(std::shared_ptr<Object> hitObject);
        void render(double minT, double maxT);

};

#endif
