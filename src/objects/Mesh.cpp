#include "Mesh.h"

Mesh::Mesh() {
    this->color_ = Color3(1.0, 1.0, 1.0);
    this->makeAABB();
}

Mesh::Mesh(Color3 color, std::string file_name) {
    this->color_ = color;
    this->readMesh(file_name);
    this->bvh_ = BVH(this->objects_);
    // std::cout << this->bvh_.objects().size() << std::endl;
    this->makeAABB();
}

std::vector<std::shared_ptr<Object>> Mesh::objects() const {
    return this->objects_;
}

void Mesh::readMesh(std::string file_name) {
    // ----------------- START NOTE -----------------
    // Code for reading files is taken from:
    // https://stackoverflow.com/questions/37957080/can-i-use-2-or-more-delimiters-in-c-function-getline
    // ----------------- END NOTE -----------------
    // Initialize vector which will keep track of the vertices
    std::vector<Point3> vertices;
    // Open the mesh file
    std::ifstream file(file_name);
    if(file.is_open()) {
        // Initialize line which stores each line
        // curr is responsible for keeping track of what type of value the
        // current line is (for example: is it vertex (v) or face (f)...)
        // past_first keeps track of whether we're past the type defining
        // value (for example: v, f, ...)
        // vertex is a temporary array which keeps the vertex data, which will be
        // used to create Point3 object, which is passed to the vertices vector
        // face is a temporary array which keeps the vertex data, which will be
        // used to create Triangle object
        // i is the index for vertex and face to keep track of which index the
        // current iteration is on
        std::string line;
        char curr = 'n';
        bool past_first = false;
        double vertex[3];
        int face[3];
        int i = 0;
        // Go through each line
        while(std::getline(file, line)) {
            // Create istringstream to divide the line by space
            // Reset past_first
            std::istringstream ss(line);
            past_first = false;
            // Go through each divided string
            while(std::getline(ss, line, ' ')) {
                // Update curr if we are on a new line
                if(!past_first) {
                    if(line == "v") {
                        curr = 'v';
                    } else if(line == "f") {
                        curr = 'f';
                    } else {
                        curr = 'n';
                    }
                }
                // Update the temp data
                if(past_first && curr == 'v') {
                    // Update the vertex position
                    vertex[i] = std::stod(line);
                    i = (i + 1) % 3;
                    // If we've gone through the 3 values, vertex is done
                    // so we can create it and add it to the vector
                    if(i == 0) {
                        Point3 temp(vertex);
                        vertices.push_back(temp);
                    }
                } else if(past_first && curr == 'f') {
                    // Update the face index
                    face[i] = std::stoi(line);
                    i = (i + 1) % 3;
                    // If we've gone through the 3 values, face is done
                    // so we can create it and add it to the vector
                    if(i == 0) {
                        std::shared_ptr<Object> temp = std::make_shared<Triangle>(this->color_, vertices[face[0] - 1], vertices[face[1] - 1], vertices[face[2] - 1]);
                        this->objects_.push_back(temp);
                    }
                }
                // Update past_first
                past_first = true;
            }
        }
        // Close the file
        file.close();
    }
}

bool Mesh::isHit(Ray& ray, double minT, double maxT) {
    std::shared_ptr<Object> hitObject = this->bvh_.detectHit(ray);
    if(hitObject == nullptr) {
        return false;
    }
    this->hitInfo_.hitpoint = hitObject->hitInfo().hitpoint;
    this->hitInfo_.normal = hitObject->hitInfo().normal;
    this->hitInfo_.t = hitObject->hitInfo().t;
    return true;
}

void Mesh::makeAABB() {
    // Initialize values for the min and max points
    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double minZ = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();
    double maxZ = std::numeric_limits<double>::lowest();
    // Go through all the points
    for(int i = 0; i < this->objects_.size(); i++) {
        // Update the minimums and maximums
        minX = std::min(minX, this->objects_[i]->aabb()->min_point()[0]);
        minY = std::min(minY, this->objects_[i]->aabb()->min_point()[1]);
        minZ = std::min(minZ, this->objects_[i]->aabb()->min_point()[2]);
        maxX = std::max(maxX, this->objects_[i]->aabb()->max_point()[0]);
        maxY = std::max(maxY, this->objects_[i]->aabb()->max_point()[1]);
        maxZ = std::max(maxZ, this->objects_[i]->aabb()->max_point()[2]);
    }
    // Create the AABB and return it
    Point3 min_point(minX, minY, minZ);
    Point3 max_point(maxX, maxY, maxZ);
    this->aabb_ = std::make_shared<AABB>(min_point, max_point);
}
