#include "World.h"

World::World() {
    this->samples_ = 1;
    this->pixel_samples_ = std::vector<ImagePoint>(1);
}

World::World(Color3 background_color, Image image, Camera camera, int samples, BVH& bvh_objects) {
    this->background_color_ = background_color;
    this->image_ = image;
    this->camera_ = camera;
    this->samples_ = samples;
    this->pixel_samples_ = std::vector<ImagePoint>(this->samples_);
    this->bvh_objects_ = bvh_objects;
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

std::vector<std::shared_ptr<XYRectangleLight>> World::lights() const {
    return this->lights_;
}

void World::addObject(std::shared_ptr<Object> object) {
    this->objects_.push_back(object);
}

void World::addLight(std::shared_ptr<XYRectangleLight> light) {
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
    // return this->bvh_objects_.detectHit(ray);
}

Color3 World::litColor(Ray& ray, std::shared_ptr<Object> hitObject, double minT, double maxT) {
    // TODO: Maybe vary intensity based on distance from

    // If no object was hit, use background color
    if(hitObject == nullptr) {
        return this->background_color_;
    }
    // Due to area light being implemented as a separate light, to be visible
    // as an object, it's defined as an object, which requires special
    // handling
    // TODO: Make lights objects, and define them as lights using Material enum
    if(hitObject->subclass() == "XYRectangle") {
        return hitObject->color();
    }
    // If there are no lights, use object color at full intensity
    if(this->lights_.empty()) {
        return hitObject->color();
    }
    // Initialize normal direction of the object and the color
    Vec3 normalDirection = hitObject->hitInfo().normal.normalize();
    Color3 shade(0.0, 0.0, 0.0);
    Color3 ambient(0.2, 0.2, 0.2);
    // Check if the material is opaque
    // If it is, shade it using the Phong reflection model
    if(hitObject->material() == OPAQUE) {
        shade = shade + ambient.elemProduct(hitObject->color());
        // Go through every light in the world
        for(int i = 0; i < this->lights_.size(); i++) {
            Color3 temp_shade(0.0, 0.0, 0.0);
            // Construct a shadow ray and check if it hits any objects
            Point3 hitPoint = hitObject->hitInfo().hitpoint;
            // Shoot this->samples_ amount of rays at the area light
            for(int j = 0; j < this->samples_; j++) {
                Ray lightRay = this->lights_[i]->lightDirection(hitPoint, true);
                std::shared_ptr<Object> shadowObject = this->hitDetection(lightRay, minT, maxT);
                // If the shadow ray doesn't pass through any objects in between the hitpoint
                // and the light source, modify the color using diffuse and specular shading
                // Otherwise, the color value remains at black for the hard shadow
                if(shadowObject == nullptr || !(shadowObject->hitInfo().t > 0.0 && shadowObject->hitInfo().t < 1.0 ) || shadowObject->subclass() == "XYRectangle") {
                    // Phong Reflection Model
                    // Diffuse component
                    Vec3 lightDirection = lightRay.direction().normalize();
                    double cosFactor = normalDirection.dot(lightDirection);
                    temp_shade = temp_shade + hitObject->color().elemProduct(this->lights_[i]->color()) * cosFactor;
                    // Specular component
                    Vec3 reflectionVector = (lightDirection - normalDirection * 2 * (lightDirection.dot(normalDirection))).normalize();
                    Vec3 viewVector = (this->camera_.position() - hitPoint).normalize();
                    double specularComponent = std::max(reflectionVector.dot(viewVector), 0.0);
                    double specularWeight = std::pow(specularComponent, 100.0);
                    temp_shade = temp_shade + hitObject->color().elemProduct(this->lights_[i]->color()) * specularWeight;
                }
            }
            // Average the shades from the area light
            temp_shade = temp_shade / this->samples_;
            temp_shade.cutToUnit();
            shade = shade + temp_shade;
            // Ray lightRay = this->lights_[i]->lightDirection(hitPoint, true);
            // std::shared_ptr<Object> shadowObject = this->hitDetection(lightRay, minT, maxT);
            // // If the shadow ray doesn't pass through any objects in between the hitpoint
            // // and the light source, modify the color using diffuse and specular shading
            // // Otherwise, the color value remains at black for the hard shadow
            // if(shadowObject == nullptr || !(shadowObject->hitInfo().t > 0.0 && shadowObject->hitInfo().t < 1.0 )) {
            //     Vec3 lightDirection = lightRay.direction().normalize();
            //     double cosFactor = normalDirection.dot(lightDirection);
            //     shade = shade + hitObject->color().elemProduct(this->lights_[i]->color()) * cosFactor;
            //     Vec3 reflectionVector = (lightDirection - normalDirection * 2 * (lightDirection.dot(normalDirection))).normalize();
            //     Vec3 viewVector = (this->camera_.position() - hitPoint).normalize();
            //     double specularComponent = std::max(reflectionVector.dot(viewVector), 0.0);
            //     double specularWeight = std::pow(specularComponent, 100.0);
            //     shade = shade + hitObject->color().elemProduct(this->lights_[i]->color()) * specularWeight;
            //     shade.cutToUnit();
            // }
        }
    } else if(hitObject->material() == TRANSPARENT) {
        // Epsilon to propogate the ray forward slightly to avoid hitting the same
        // object point
        double epsilon = 0.00001;
        // Refract the ray using the index of refraction
        Vec3 direction = this->refract(ray.direction(), normalDirection, 0.5);
        Ray scatteredRay(hitObject->hitInfo().hitpoint + direction * epsilon, direction);
        // Recursively determine which shade the hitpoint is
        std::shared_ptr<Object> hitObject = this->hitDetection(scatteredRay, minT, maxT);
        shade = this->litColor(ray, hitObject, minT, maxT);
    } else if(hitObject->material() == MIRROR) {
        // Calculate the reflection vector for the mirror
        Vec3 rayDirection = ray.direction();
        Vec3 reflectionVector = (rayDirection - normalDirection * 2 * (rayDirection.dot(normalDirection))).normalize();
        Ray reflectedRay(hitObject->hitInfo().hitpoint, reflectionVector);
        // Recursively determine which shade the hitpoint is
        std::shared_ptr<Object> hitObject = this->hitDetection(reflectedRay, minT, maxT);
        shade = this->litColor(ray, hitObject, minT, maxT);
    }
    // Return the color shade
    return shade;
}

Vec3 World::refract(Vec3 direction, Vec3 normal, double refraction_index) {
    // Code for refraction is largely taken and modified from Peter Shirley's
    // "Ray Tracing In One Weekend"
    double cos_theta = std::min((direction * -1.0).dot(normal), 1.0);
    Vec3 ray_perpendicular = (direction + normal * cos_theta) * refraction_index;
    Vec3 ray_parallel = normal * -std::sqrt(std::abs(1.0 - ray_perpendicular.magnitude() * ray_perpendicular.magnitude()));
    return ray_perpendicular + ray_parallel;
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
            // double pixel_size = 1.0 / (width - 1);
            // this->multijitterSampling(pixel_size);
            // // Temporary color used for averaging
            // Color3 tempColor(0.0, 0.0, 0.0);
            // // Go through all samples
            // for(int k = 0; k < this->pixel_samples_.size(); k++) {
            //     // Create a ray through the image point
            //     Ray ray = this->camera_.createRay(double(i) / (width - 1) + this->pixel_samples_[k].x,
            //                                       double(j) / (height - 1) + this->pixel_samples_[k].y);
            //     // Check if it hits an object
            //     std::shared_ptr<Object> hitObject = this->hitDetection(ray, minT, maxT);
            //     // Compute the appropriate color for the pixel using the hit object
            //     tempColor = tempColor + this->litColor(hitObject, minT, maxT);
            // }
            // // Average the colors from the sampling
            // tempColor = tempColor / this->pixel_samples_.size();
            // // Write the color in PPM format
            // tempColor.write_data(std::cout);
            // Code for no sampling
            Ray ray = this->camera_.createRay(double(i) / (width - 1), double(j) / (height - 1));
            std::shared_ptr<Object> hitObject = this->hitDetection(ray, minT, maxT);
            this->litColor(ray, hitObject, minT, maxT).write_data(std::cout);
        }
    }
    // For notifying the user that the program is done
    std::cerr << "\nDone.\n";
}

void World::multijitterSampling(double pixel_size) {
    // Initialize square root of the samples, output, and subcell size
    int samples_root = static_cast<int>(std::round(std::sqrt(this->samples_)));
    double subcell_size = pixel_size / (samples_root * samples_root);
    // Initialize random number generator using Uniform distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_double(0.0, subcell_size);
    // Initialize the points to the "canonical" multijittered pattern
    for(int i = 0; i < samples_root; i++) {
        for(int j = 0; j < samples_root; j++) {
            this->pixel_samples_[i * samples_root + j].x = i * samples_root * subcell_size + j * subcell_size + dis_double(gen);
            this->pixel_samples_[i * samples_root + j].y = j * samples_root * subcell_size + i * subcell_size + dis_double(gen);
        }
    }
    // Shuffle x coordinates within each column of cells
    for(int i = 0; i < samples_root; i++) {
        for(int j = 0; j < samples_root; j++) {
            double t;
            int k;
            std::uniform_int_distribution<> dis_int(j, (samples_root - 1));
            k = dis_int(gen);
            t = this->pixel_samples_[i * samples_root + j].x;
            this->pixel_samples_[i * samples_root + j].x = this->pixel_samples_[i * samples_root + k].x;
            this->pixel_samples_[i * samples_root + k].x = t;
        }
    }
    // Shuffle y coordinates within each row of cells
    for(int i = 0; i < samples_root; i++) {
        for(int j = 0; j < samples_root; j++) {
            double t;
            int k;
            std::uniform_int_distribution<> dis_int(j, (samples_root - 1));
            k = dis_int(gen);
            t = this->pixel_samples_[j * samples_root + i].y;
            this->pixel_samples_[j * samples_root + i].y = this->pixel_samples_[k * samples_root + i].y;
            this->pixel_samples_[k * samples_root + i].y = t;
        }
    }
}
