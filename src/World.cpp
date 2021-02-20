#include "World.h"

World::World() {
    this->projection_ = PERSPECTIVE;
}

World::World(Projection projection, Color3 background_color, Image image, Camera camera) {
    this->projection_ = projection;
    this->background_color_ = background_color;
    this->image_ = image;
    this->camera_ = camera;
}

Projection World::projection() const {
    return this->projection_;
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

Ray World::createRay(int i, int j) {
    // TODO: May need to modify this because of moveable camera
    double u = double(i) / (this->image_.width() - 1);
    double v = double(j) / (this->image_.height() - 1);
    Vec3 gridInfo = this->camera_.lower_left() + this->camera_.hor_direction() * u + this->camera_.ver_direction() * v;
    if(this->projection_ == PERSPECTIVE) {
        Ray ray(this->camera_.position(), gridInfo);
        return ray;
    } else if(this->projection_ == ORTHOGRAPHIC) {
        Vec3 direction(0.0, 0.0, -1.0);
        Ray ray(gridInfo, direction);
        return ray;
    }
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

void World::render(double minT, double maxT) {

    int width = this->image_.width();
    int height = this->image_.height();
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    for(int j = height - 1; j >= 0; j--) {
        // std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < width; i++) {
            // double u = double(i) / (width - 1);
            // double v = double(j) / (height - 1);
            // Ray ray(this->camera_.position(), this->camera_.lower_left() + this->camera_.hor_direction() * u + this->camera_.ver_direction() * v);
            Ray ray = this->createRay(i, j);
            std::shared_ptr<Object> hitObject = this->hitDetection(ray, minT, maxT);
            if(hitObject == nullptr) {
                this->background_color_.write_data(std::cout);
            } else {
                hitObject->color().write_data(std::cout);
            }
        }
    }

}
