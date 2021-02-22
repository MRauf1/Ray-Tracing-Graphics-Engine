#include "World.h"

World::World() {
    this->samples_ = 1;
}

World::World(Color3 background_color, Image image, Camera camera, int samples) {
    this->background_color_ = background_color;
    this->image_ = image;
    this->camera_ = camera;
    this->samples_ = samples;
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

int World::samples() const {
    return this->samples_;
}

std::vector<std::shared_ptr<Object>> World::objects() const {
    return this->objects_;
}

std::vector<std::shared_ptr<PointLight>> World::lights() const {
    return this->lights_;
}

void World::addObject(std::shared_ptr<Object> object) {
    this->objects_.push_back(object);
}

void World::addLight(std::shared_ptr<PointLight> light) {
    this->lights_.push_back(light);
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

Color3 World::litColor(std::shared_ptr<Object> hitObject) {
    // TODO: Maybe vary intensity based on distance from
    // TODO: For proportions, wouldn't it be more realistic to add them instead of max?
    if(hitObject == nullptr) {
        return this->background_color_;
    }

    if(this->lights_.empty()) {
        return hitObject->color();
    }

    Vec3 normalDirection = hitObject->hitInfo().normal.normalize();
    Color3 shade(0.0, 0.0, 0.0);
    for(int i = 0; i < this->lights_.size(); i++) {
        Point3 hitPoint = hitObject->hitInfo().hitpoint;
        Ray lightRay = this->lights_[i]->lightDirection(hitPoint);
        Vec3 lightDirection = lightRay.direction().normalize();
        double cosFactor = normalDirection.dot(lightDirection);
        shade = shade + hitObject->color().elemProduct(this->lights_[i]->color()) * cosFactor;
        shade.cutToUnit();
    }
    return shade;
}

void World::render(double minT, double maxT) {

    int width = this->image_.width();
    int height = this->image_.height();
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    for(int j = height - 1; j >= 0; j--) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < width; i++) {
            double pixel_size = 1.0 / (width - 1);
            std::vector<ImagePoint> sample_points = this->multijitterSampling(pixel_size);
            Color3 tempColor(0.0, 0.0, 0.0);
            for(int k = 0; k < sample_points.size(); k++) {
                Ray ray = this->camera_.createRay(double(i) / (width - 1) + sample_points[k].x, double(j) / (height - 1) + sample_points[k].y);
                std::shared_ptr<Object> hitObject = this->hitDetection(ray, minT, maxT);
                tempColor = tempColor + this->litColor(hitObject);
            }
            tempColor = tempColor / sample_points.size();
            tempColor.write_data(std::cout);
            // Code for no sampling
            // Ray ray = this->camera_.createRay(double(i) / (width - 1), double(j) / (height - 1));
            // std::shared_ptr<Object> hitObject = this->hitDetection(ray, minT, maxT);
            // this->litColor(hitObject).write_data(std::cout);
        }
    }

    std::cerr << "\nDone.\n";

}

std::vector<ImagePoint> World::multijitterSampling(double pixel_size) {
    int samples_root = static_cast<int>(std::round(std::sqrt(this->samples_)));
    std::vector<ImagePoint> output(samples_root * samples_root);
    double subcell_size = pixel_size / (samples_root * samples_root);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_double(0.0, subcell_size);

    for(int i = 0; i < samples_root; i++) {
        for(int j = 0; j < samples_root; j++) {
            output[i * samples_root + j].x = i * samples_root * subcell_size + j * subcell_size + dis_double(gen);
            output[i * samples_root + j].y = j * samples_root * subcell_size + i * subcell_size + dis_double(gen);
        }
    }

    for(int i = 0; i < samples_root; i++) {
        for(int j = 0; j < samples_root; j++) {
            double t;
            int k;
            std::uniform_int_distribution<> dis_int(j, (samples_root - 1));
            k = dis_int(gen);
            t = output[i * samples_root + j].x;
            output[i * samples_root + j].x = output[i * samples_root + k].x;
            output[i * samples_root + k].x = t;
        }
    }

    for(int i = 0; i < samples_root; i++) {
        for(int j = 0; j < samples_root; j++) {
            double t;
            int k;
            std::uniform_int_distribution<> dis_int(j, (samples_root - 1));
            k = dis_int(gen);
            t = output[j * samples_root + i].y;
            output[j * samples_root + i].y = output[k * samples_root + i].y;
            output[k * samples_root + i].y = t;
        }
    }

    return output;

}
