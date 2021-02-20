#include "World.h"

World::World() {

}

World::World(Color3 background_color, Image image, Camera camera) {
    this->background_color_ = background_color;
    this->image_ = image;
    this->camera_ = camera;
}

Color3 World::background_color() const {
    return this->background_color_;
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

std::shared_ptr<Object> World::hitDetection(Ray& ray, double minT, double maxT) {
    if(this->objects_.empty()) {
        return nullptr;
    }

    std::shared_ptr<Object> closestObject = nullptr;
    double closestT = std::numeric_limits<double>::max();
    for(int i = 0; i < this->objects_.size(); i++) {
        if(this->objects_[i]->isHit(ray, minT, maxT) && this->objects_[i]->hitInfo().t < closestT) {
            closestObject = this->objects_[i];
            closestT = closestObject->hitInfo().t;
        }
    }
    return closestObject;
}

// void World::render() {
//
//     int width = this->image_.width();
//     int height = this->image_.height();
//     std::cout << "P3\n" << width << " " << height << "\n255\n";
//
//     for(int j = height - 1; j >= 0; j--) {
//         // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
//         for(int i = 0; i < width; i++) {
//
//         }
//     }
//
// }
