#include "math/Vec3.h"
#include "image/Image.h"
#include "Camera.h"
#include "objects/Object.h"
#include "objects/Plane.h"
#include "objects/Sphere.h"
#include "lights/PointLight.h"
#include "World.h"
#include <limits>

int main() {

    // Projection type
    Projection PROJECTION = PERSPECTIVE;

    // Background color
    Color3 BACKGROUND(1.0, 1.0, 1.0);

    // Image settings
    double ASPECT_RATIO = 16.0 / 9.0;
    int WIDTH = 256;

    Image IMAGE(ASPECT_RATIO, WIDTH);

    // Camera settings
    double VIEWPORT_HEIGHT = 2.0;
    double FOCAL_LENGTH = 1.0;
    Point3 POSITION(0.0, 0.0, 0.0);

    Camera CAMERA(ASPECT_RATIO, VIEWPORT_HEIGHT, FOCAL_LENGTH, POSITION);

    // Objects in the scene
    Color3 colorPlane1(1.0, 0.0, 0.0);
    Point3 positionPlane1(0.0, -1.0, 0.0);
    Vec3 normalPlane1(0.0, 1.0, 0.0);
    std::shared_ptr<Object> plane1 = std::make_shared<Plane>(colorPlane1, positionPlane1, normalPlane1);
    Color3 colorPlane2(0.0, 1.0, 0.0);
    Point3 positionPlane2(10.0, 0.0, -10.0);
    Vec3 normalPlane2(-0.5, 0.0, 0.5);
    std::shared_ptr<Object> plane2 = std::make_shared<Plane>(colorPlane2, positionPlane2, normalPlane2);
    Color3 colorPlane3(0.0, 0.0, 1.0);
    Point3 positionPlane3(-10.0, 0.0, -10.0);
    Vec3 normalPlane3(0.5, 0.0, 0.5);
    std::shared_ptr<Object> plane3 = std::make_shared<Plane>(colorPlane3, positionPlane3, normalPlane3);
    Color3 colorSphere1(0.0, 1.0, 0.0);
    Point3 positionSphere1(0.0, 0.0, -5.0);
    double radiusSphere1 = 1.0;
    std::shared_ptr<Object> sphere1 = std::make_shared<Sphere>(colorSphere1, positionSphere1, radiusSphere1);
    Color3 colorSphere2(1.0, 0.5, 0.5);
    Point3 positionSphere2(-3.0, 0.0, -3.0);
    double radiusSphere2 = 1.0;
    std::shared_ptr<Object> sphere2 = std::make_shared<Sphere>(colorSphere2, positionSphere2, radiusSphere2);

    // Lights in the scene
    Point3 positionLight1(-1.0, 0.0, 0.0);
    std::shared_ptr<PointLight> pointLight1 = std::make_shared<PointLight>(positionLight1);
    Point3 positionLight2(1.0, 0.0, 0.0);
    std::shared_ptr<PointLight> pointLight2 = std::make_shared<PointLight>(positionLight2);

    // Create the world
    World world(PROJECTION, BACKGROUND, IMAGE, CAMERA);
    // Add objects to the world
    world.addObject(plane1);
    world.addObject(plane2);
    world.addObject(plane3);
    world.addObject(sphere1);
    world.addObject(sphere2);
    // Add lights to the world
    world.addLight(pointLight1);
    world.addLight(pointLight2);

    // Render the scene
    world.render(0.0, std::numeric_limits<double>::max());

}
