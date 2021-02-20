#include "World.h"

World::World() {

}

World::World(Image image, Camera camera) {
    this->image_ = image;
    this->camera_ = camera;
}

Image World::image() const {
    return this->image_;
}

Camera World::camera() const {
    return this->camera_;
}

std::vector<std::shared_ptr<Object>> World::objects() const {
    return this->objects_;
}

void World::addObject(std::shared_ptr<Object> object) {
    this->objects_.push_back(object);
}


// void render();
