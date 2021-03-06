#ifndef WORLD_H
#define WORLD_H

#include "math/Vec3.h"
#include "math/Ray.h"
#include "image/Image.h"
#include "Camera.h"
#include "objects/Object.h"
#include "objects/Plane.h"
#include "objects/Sphere.h"
#include "objects/Triangle.h"
#include "objects/Mesh.h"
#include "objects/XYRectangle.h"
#include "lights/PointLight.h"
#include "lights/XYRectangleLight.h"
#include "ImagePoint.h"
#include "data_structures/BVH.h"
#include <vector>
#include <memory>
#include <iostream>
#include <limits>
#include <utility>
#include <cmath>
#include <random>
#include <typeinfo>

class World {

    private:

        Color3 background_color_;
        Image image_;
        Camera camera_;
        int samples_;
        std::vector<ImagePoint> pixel_samples_;
        std::vector<std::shared_ptr<Object>> objects_;
        std::vector<std::shared_ptr<XYRectangleLight>> lights_;
        BVH bvh_objects_;


    public:

        /**
         * Default World constructor
         */
        World();

        /**
         * Parameterized World constructor
         * @param background_color Background color of the world
         * @param image            Image object for storing the image info
         * @param camera           Camera object
         * @param samples          Number of samples to use in multijittered sampling
         */
        World(Color3 background_color, Image image, Camera camera, int samples, BVH& bvh_objects);

        /**
         * Getter for the background color
         * @return Background color of the world
         */
        Color3 background_color() const;

        /**
         * Getter for the image object
         * @return Image object
         */
        Image image() const;

        /**
         * Getter for the camera object
         * @return Camera object
         */
        Camera camera() const;

        /**
         * Getter for the number of samples to use in multijittered sampling
         * @return Number of samples
         */
        int samples() const;

        /**
         * Getter for the vector of Object pointers
         * Vector stores all of the objects in the world
         */
        std::vector<std::shared_ptr<Object>> objects() const;

        /**
         * Getter for the vector of PointLight pointers
         * Vector stores all of the point lights in the world
         */
        std::vector<std::shared_ptr<XYRectangleLight>> lights() const;


        /**
         * Adds object to the objects vector
         * @param object Object pointer to add
         */
        void addObject(std::shared_ptr<Object> object);

        /**
         * Adds light to the lights vector
         * @param light PointLight pointer to add
         */
        void addLight(std::shared_ptr<XYRectangleLight> light);

        /**
         * Goes through all the objects in the world to check if ray
         * hits any of them
         * If the ray hits, it returns the closest hit object which has valid t
         * values
         * If the ray doesn't hit anything, it returns a null pointer
         * @param  ray  Ray to check the hit for
         * @param  minT Minimum t for the hit
         * @param  maxT Maximum t for the hit
         * @return      Object pointer to the object which was hit
         */
        std::shared_ptr<Object> hitDetection(Ray& ray, double minT, double maxT);

        /**
         * Calculates the appropriate color for the object that was hit
         * If the object is null, then return the background color
         * If there are no lights, return object's color at full intensity
         * Otherwise, go through all lights in the world to calculate the
         * color value using diffuse shading
         * Additionally, cast shadow rays to all other objects to check if a
         * point is in shadow
         * If it is, apply a hard shadow
         * @param  Ray       Ray to check the hit for
         * @param  hitObject Object that was hit
         * @param  minT      Minimum t for the hit
         * @param  maxT      Maximum t for the hit
         * @return           Adjusted color of the object
         */
        Color3 litColor(Ray& ray, std::shared_ptr<Object> hitObject, double minT, double maxT);

        /**
         * Helper function for refracting an incoming ray
         * @param  direction        Direction vector of the incoming ray
         * @param  normal           Normal of the object being hit
         * @param  refraction_index Refraction index of the object being hit
         * @return                  Refracted direction vector of the ray
         */
        Vec3 refract(Vec3 direction, Vec3 normal, double refraction_index);

        /**
         * Renders the world
         * Go through every pixel, and at every pixel, first apply multijittered
         * sampling, and then check hits for all of these samples
         * Then compute the color for the pixel
         * Afterward, average the pixel values using the samples
         * Write the image data in PPM format using std::out
         * @param minT Minimum t for the hit
         * @param maxT Maximum t for the hit
         */
        void render(double minT, double maxT);

        /**
         * Calculate the points on the image through which the rays should pass
         * using multijittered sampling for anti-aliasing
         * Stores the pixel samples inside of pixel_samples_
         * @param  pixel_size Size of the pixel
         */
        void multijitterSampling(double pixel_size);

};

#endif
