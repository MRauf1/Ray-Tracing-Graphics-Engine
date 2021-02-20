#ifndef WORLD_H
#define WORLD_H

#include "image/Image.h"
#include "Camera.h"
#include "objects/Object.h"
#include "objects/Plane.h"
#include <vector>
#include <memory>

class World {

    private:
        Image image_;
        Camera camera_;
        std::vector<std::shared_ptr<Object>> objects_;

    public:
        World();
        World(Image image, Camera camera);
        Image image() const;
        Camera camera() const;
        std::vector<std::shared_ptr<Object>> objects() const;

        void addObject(Object& object);
        void render();

};

#endif
