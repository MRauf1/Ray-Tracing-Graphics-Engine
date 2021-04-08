#include "math/Vec3.h"
#include "image/Image.h"
#include "Camera.h"
#include "objects/Object.h"
#include "data_structures/AABB.h"
#include "objects/Plane.h"
#include "objects/Sphere.h"
#include "lights/PointLight.h"
#include "lights/XYRectangleLight.h"
#include "World.h"
#include <limits>
#include <chrono>

int main() {

    // Background color
    Color3 BACKGROUND(0.0, 0.0, 1.0);

    // Image settings
    double ASPECT_RATIO = 1.0;
    int WIDTH = 400;

    Image IMAGE(ASPECT_RATIO, WIDTH);

    // Camera settings
    double VIEWPORT_HEIGHT = 2.0;
    double FOCAL_LENGTH = 1.0;
    Point3 POSITION(0.0, 0.0, 0.0);
    Vec3 VIEW_DIR(0.0, 0.0, -1.0); // VIEW_DIR and UP_DIR can't be parallel
    Vec3 UP_DIR(0.0, 1.0, 0.0);
    Projection PROJECTION = PERSPECTIVE;

    Camera CAMERA(ASPECT_RATIO, VIEWPORT_HEIGHT, FOCAL_LENGTH, POSITION, VIEW_DIR, UP_DIR, PROJECTION);

    // Number of samples for multijittered sampling
    int SAMPLES = 4;

    Material MATERIAL_OPAQUE = OPAQUE;
    Material MATERIAL_TRANSPARENT = TRANSPARENT;
    Material MATERIAL_MIRROR = MIRROR;

    // Objects in the scene
    Color3 colorPlane1(1.0, 0.0, 0.0);
    Point3 positionPlane1(0.0, -1.0, 0.0);
    Vec3 normalPlane1(0.0, 1.0, 0.0);
    std::shared_ptr<Object> plane1 = std::make_shared<Plane>(colorPlane1, MATERIAL_OPAQUE, positionPlane1, normalPlane1);
    Color3 colorPlane2(0.0, 1.0, 0.0);
    Point3 positionPlane2(10.0, 0.0, -10.0);
    Vec3 normalPlane2(-0.5, 0.0, 0.5);
    std::shared_ptr<Object> plane2 = std::make_shared<Plane>(colorPlane2, MATERIAL_OPAQUE, positionPlane2, normalPlane2);
    Color3 colorPlane3(0.0, 0.0, 1.0);
    Point3 positionPlane3(-10.0, 0.0, -10.0);
    Vec3 normalPlane3(0.5, 0.0, 0.5);
    std::shared_ptr<Object> plane3 = std::make_shared<Plane>(colorPlane3, MATERIAL_OPAQUE, positionPlane3, normalPlane3);

    Color3 colorSphere1(0.0, 1.0, 0.0);
    Point3 positionSphere1(0.0, -0.4, -3.0);
    double radiusSphere1 = 0.6;
    std::shared_ptr<Object> sphere1 = std::make_shared<Sphere>(colorSphere1, MATERIAL_MIRROR, positionSphere1, radiusSphere1);
    Color3 colorSphere2(1.0, 0.5, 0.5);
    Point3 positionSphere2(-2.0, -0.5, -3.0);
    double radiusSphere2 = 0.5;
    std::shared_ptr<Object> sphere2 = std::make_shared<Sphere>(colorSphere2, MATERIAL_OPAQUE, positionSphere2, radiusSphere2);
    Color3 colorSphere3(0.0, 1.0, 1.0);
    Point3 positionSphere3(1.0, -0.3, -2.0);
    double radiusSphere3 = 0.7;
    std::shared_ptr<Object> sphere3 = std::make_shared<Sphere>(colorSphere3, MATERIAL_TRANSPARENT, positionSphere3, radiusSphere3);

    // Color3 colorTriangle1(1.0, 0.5, 0.5);
    // Point3 pointTriangle1_1(0.5, -1.0, -3.0);
    // Point3 pointTriangle1_2(2.0, -1.0, -3.0);
    // Point3 pointTriangle1_3(0.5, 1.0, -3.0);
    // std::shared_ptr<Object> triangle1 = std::make_shared<Triangle>(colorTriangle1, pointTriangle1_1, pointTriangle1_2, pointTriangle1_3);
    // Color3 colorTriangle2(1.0, 0.5, 0.5);
    // Point3 pointTriangle2_1(0.5, 1.0, -3.0);
    // Point3 pointTriangle2_2(2.0, -1.0, -3.0);
    // Point3 pointTriangle2_3(2.0, 1.0, -3.0);
    // std::shared_ptr<Object> triangle2 = std::make_shared<Triangle>(colorTriangle1, pointTriangle2_1, pointTriangle2_2, pointTriangle2_3);

    // Lights in the scene
    // Point3 positionLight1(-5.0, 0.0, 0.0);
    // Color3 colorLight1(0.5, 0.5, 0.5);
    // std::shared_ptr<PointLight> pointLight1 = std::make_shared<PointLight>(positionLight1, colorLight1);
    // Point3 positionLight2(5.0, 0.0, 0.0);
    // Color3 colorLight2(0.5, 0.5, 0.5);
    // std::shared_ptr<PointLight> pointLight2 = std::make_shared<PointLight>(positionLight2, colorLight2);
    // Point3 positionLight3(0.0, 10.0, 0.0);
    // Color3 colorLight3(1.0, 1.0, 1.0);
    // std::shared_ptr<PointLight> pointLight3 = std::make_shared<PointLight>(positionLight3, colorLight3);
    Point3 lowerLeft4(-1.0, 0.0, -5.0);
    Point3 upperRight4(1.0, 2.0, -5.0);
    Color3 colorLight4(1.0, 1.0, 1.0);
    std::shared_ptr<XYRectangleLight> xyRectangleLight1 = std::make_shared<XYRectangleLight>(lowerLeft4, upperRight4, colorLight4);
    std::shared_ptr<Object> XYRectangle1 = std::make_shared<XYRectangle>(colorLight4, MATERIAL_OPAQUE, lowerLeft4, upperRight4);

    std::vector<std::shared_ptr<Object>> objects;
    objects.push_back(sphere1);
    objects.push_back(sphere2);
    // objects.push_back(triangle1);
    // objects.push_back(triangle2);
    BVH bvh_objects(objects);

    // std::vector<std::shared_ptr<Object>> objects;
    // int NUM_SPHERES = 100000;
    // int root = (int) (std::round(std::sqrt(NUM_SPHERES)));
    // Color3 color(1.0, 0.0, 0.0);
    // double radius = VIEWPORT_HEIGHT / root / 3;
    // for(int i = 0; i < root; i++) {
    //     for(int j = 0; j < root; j++) {
    //         Point3 center(radius + (-VIEWPORT_HEIGHT / 2) + i * (radius * 3), radius + (-VIEWPORT_HEIGHT / 2) + j * (radius * 3), -1.0);
    //         std::shared_ptr<Object> sphere = std::make_shared<Sphere>(color, center, radius);
    //         objects.push_back(sphere);
    //     }
    // }

    // Color3 color(1.0, 0.0, 0.0);
    // std::shared_ptr<Object> object = std::make_shared<Mesh>(color, "../meshes/cow.obj");
    // std::cout << object->aabb()->min_point()[0] << "," << object->aabb()->min_point()[1] << "," << object->aabb()->min_point()[2] << std::endl;
    // std::cout << object->aabb()->max_point()[0] << "," << object->aabb()->max_point()[1] << "," << object->aabb()->max_point()[2] << std::endl;
    // objects.push_back(object);
    // BVH bvh_objects(objects);

    // Point3 positionLight4(0.0, 0.5, 3.0);
    // Color3 colorLight4(1.0, 1.0, 1.0);
    // std::shared_ptr<PointLight> pointLight4 = std::make_shared<PointLight>(positionLight4, colorLight4);

    // Create the world
    World world(BACKGROUND, IMAGE, CAMERA, SAMPLES, bvh_objects);
    // world.addObject(object);
    // for(int i = 0; i < objects.size(); i++) {
    //     world.addObject(objects[i]);
    // }

    // Add objects to the world
    world.addObject(plane1);
    world.addObject(plane2);
    world.addObject(plane3);
    world.addObject(sphere1);
    world.addObject(sphere2);
    world.addObject(sphere3);
    // world.addObject(XYRectangle1);
    // world.addObject(triangle1);
    // world.addObject(triangle2);
    // Add lights to the world
    // world.addLight(pointLight1);
    // world.addLight(pointLight2);
    // world.addLight(pointLight3);
    world.addLight(xyRectangleLight1);

    auto t1 = std::chrono::high_resolution_clock::now();
    // Render the scene
    world.render(0.0, std::numeric_limits<double>::max());
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cerr << ms_double.count() << "ms" << "\n";

    // Runtime for building BVH
    t1 = std::chrono::high_resolution_clock::now();
    BVH bvh_objects2(objects);
    t2 = std::chrono::high_resolution_clock::now();
    ms_double = t2 - t1;
    std::cerr << ms_double.count() << "ms" << "\n";

}
