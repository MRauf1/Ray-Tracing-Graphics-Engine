#include "math/Vec3.h"
#include "image/Image.h"
#include "Camera.h"
#include "objects/Object.h"
#include "objects/Plane.h"
#include "objects/Sphere.h"
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
    Color3 color1(1.0, 0.0, 0.0);
    Point3 position1(0.0, -1.0, 0.0);
    Vec3 normal1(0.0, 1.0, 0.0);
    std::shared_ptr<Object> plane1 = std::make_shared<Plane>(color1, position1, normal1);
    Color3 color2(0.0, 1.0, 0.0);
    Point3 position2(0.0, 0.0, -5.0);
    double radius2 = 1.0;
    std::shared_ptr<Object> sphere2 = std::make_shared<Sphere>(color2, position2, radius2);

    // Create the world
    World world(PROJECTION, BACKGROUND, IMAGE, CAMERA);
    // Add objects to the world
    world.addObject(plane1);
    world.addObject(sphere2);

    // Render the scene
    world.render(0.0, std::numeric_limits<double>::max());

}
