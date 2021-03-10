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
    // If there are no objects, return nullptr
    if(this->objects_.empty()) {
        return nullptr;
    }
    // Initialize closestObject and closestT
    std::shared_ptr<Object> closestObject = nullptr;
    double closestT = std::numeric_limits<double>::max();
    // Go through each object in the world
    for(int i = 0; i < this->objects_.size(); i++) {
        // If the object is hit within the t bounds (minT, maxT) and is closer
        // than previous object, update closestObject and closestT
        if(this->objects_[i]->isHit(ray, minT, maxT) && this->objects_[i]->hitInfo().t < closestT) {
            closestObject = this->objects_[i];
            closestT = closestObject->hitInfo().t;
        }
    }
    // Return the closestObject
    return closestObject;
}

Color3 World::litColor(std::shared_ptr<Object> hitObject, double minT, double maxT) {
    // TODO: Maybe vary intensity based on distance from

    // If no object was hit, use background color
    if(hitObject == nullptr) {
        return this->background_color_;
    }
    // If there are no lights, use object color at full intensity
    if(this->lights_.empty()) {
        return hitObject->color();
    }
    // Initialize normal direction of the object and the color
    Vec3 normalDirection = hitObject->hitInfo().normal.normalize();
    Color3 shade(0.0, 0.0, 0.0);
    // Go through every light in the world
    for(int i = 0; i < this->lights_.size(); i++) {
        // Construct a shadow ray and check if it hits any objects
        Point3 hitPoint = hitObject->hitInfo().hitpoint;
        Ray lightRay = this->lights_[i]->lightDirection(hitPoint, true);
        std::shared_ptr<Object> shadowObject = this->hitDetection(lightRay, minT, maxT);
        // If the shadow ray doesn't pass through any objects in between the hitpoint
        // and the light source, modify the color using diffuse shading
        // Otherwise, the color value remains at black for the hard shadow
        if(shadowObject == nullptr || !(shadowObject->hitInfo().t > 0.0 && shadowObject->hitInfo().t < 1.0 )) {
            Vec3 lightDirection = lightRay.direction().normalize();
            double cosFactor = normalDirection.dot(lightDirection);
            shade = shade + hitObject->color().elemProduct(this->lights_[i]->color()) * cosFactor;
            shade.cutToUnit();
        }
    }
    // Return the color shade
    return shade;
}

void World::render(double minT, double maxT) {
    // Initialize width and height
    int width = this->image_.width();
    int height = this->image_.height();
    // Start writing the data in PPM format
    std::cout << "P3\n" << width << " " << height << "\n255\n";
    // Go through all pixels in the image
    for(int j = height - 1; j >= 0; j--) {
        // For checking how much is left
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for(int i = 0; i < width; i++) {
            // Calculate the pixel size and use it to compute all the image points
            // through which the rays should go using multijittered sampling
            double pixel_size = 1.0 / (width - 1);
            std::vector<ImagePoint> sample_points = this->multijitterSampling(pixel_size);
            // Temporary color used for averaging
            Color3 tempColor(0.0, 0.0, 0.0);
            // Go through all samples
            for(int k = 0; k < sample_points.size(); k++) {
                // Create a ray through the image point
                Ray ray = this->camera_.createRay(double(i) / (width - 1) + sample_points[k].x,
                                                  double(j) / (height - 1) + sample_points[k].y);
                // Check if it hits an object
                std::shared_ptr<Object> hitObject = this->hitDetection(ray, minT, maxT);
                // Compute the appropriate color for the pixel using the hit object
                tempColor = tempColor + this->litColor(hitObject, minT, maxT);
            }
            // Average the colors from the sampling
            tempColor = tempColor / sample_points.size();
            // Write the color in PPM format
            tempColor.write_data(std::cout);
            // Code for no sampling
            // Ray ray = this->camera_.createRay(double(i) / (width - 1), double(j) / (height - 1));
            // std::shared_ptr<Object> hitObject = this->hitDetection(ray, minT, maxT);
            // this->litColor(hitObject, minT, maxT).write_data(std::cout);
        }
    }
    // For notifying the user that the program is done
    std::cerr << "\nDone.\n";
}

std::vector<ImagePoint> World::multijitterSampling(double pixel_size) {
    // Initialize square root of the samples, output, and subcell size
    int samples_root = static_cast<int>(std::round(std::sqrt(this->samples_)));
    std::vector<ImagePoint> output(samples_root * samples_root);
    double subcell_size = pixel_size / (samples_root * samples_root);
    // Initialize random number generator using Uniform distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_double(0.0, subcell_size);
    // Initialize the points to the "canonical" multijittered pattern
    for(int i = 0; i < samples_root; i++) {
        for(int j = 0; j < samples_root; j++) {
            output[i * samples_root + j].x = i * samples_root * subcell_size + j * subcell_size + dis_double(gen);
            output[i * samples_root + j].y = j * samples_root * subcell_size + i * subcell_size + dis_double(gen);
        }
    }
    // Shuffle x coordinates within each column of cells
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
    // Shuffle y coordinates within each row of cells
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
    // Return the output
    return output;
}
