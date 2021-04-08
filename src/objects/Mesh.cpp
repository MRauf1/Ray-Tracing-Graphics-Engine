#include "Mesh.h"

Mesh::Mesh() {
    this->color_ = Color3(1.0, 1.0, 1.0);
    this->calculateVertexNormals();
    this->makeAABB();
}

Mesh::Mesh(Color3 color, Material material, std::string file_name) {
    this->color_ = color;
    this->material_ = material;
    this->readMesh(file_name);
    this->bvh_ = BVH(this->objects_);
    this->calculateVertexNormals();
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
    // std::vector<Point3> vertices;
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
        std::vector<int> face = std::vector<int>(3);
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
                        this->vertices_.push_back(temp);
                    }
                } else if(past_first && curr == 'f') {
                    // Update the face index
                    face[i] = std::stoi(line);
                    i = (i + 1) % 3;
                    // If we've gone through the 3 values, face is done
                    // so we can create it and add it to the vector
                    if(i == 0) {
                        Point3 v1(this->vertices_[face[0] - 1].x(), this->vertices_[face[0] - 1].y(), this->vertices_[face[0] - 1].z(), face[0] - 1);
                        Point3 v2(this->vertices_[face[1] - 1].x(), this->vertices_[face[1] - 1].y(), this->vertices_[face[1] - 1].z(), face[1] - 1);
                        Point3 v3(this->vertices_[face[2] - 1].x(), this->vertices_[face[2] - 1].y(), this->vertices_[face[2] - 1].z(), face[2] - 1);
                        std::shared_ptr<Object> temp = std::make_shared<Triangle>(this->color_, this->material_, v1, v2, v3);
                        // std::shared_ptr<Object> temp = std::make_shared<Triangle>(this->color_, this->vertices_[face[0] - 1], this->vertices_[face[1] - 1], this->vertices_[face[2] - 1]);
                        // std::cout << face[2] - 1 << std::endl;
                        // this->vertices_[face[0] - 1].index(face[0] - 1);
                        // this->vertices_[face[1] - 1].index(face[1] - 1);
                        // this->vertices_[face[2] - 1].index(face[2] - 1);
                        this->objects_.push_back(temp);
                        this->faces_.push_back(face);
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

void Mesh::calculateVertexNormals() {
    // Initialize the vertex normals and set them to 0 vector
    this->vertex_normals_ = std::vector<Vec3>(this->vertices_.size());
    for(int i = 0; i < this->vertex_normals_.size(); i++) {
        Vec3 temp(0.0, 0.0, 0.0);
        this->vertex_normals_[i] = temp;
    }
    // Go through all the faces
    for(int i = 0; i < this->faces_.size(); i++) {
        // Retrieve the necessary data for the calculations
        Point3 vertex1 = this->vertices_[this->faces_[i][0] - 1];
        Point3 vertex2 = this->vertices_[this->faces_[i][1] - 1];
        Point3 vertex3 = this->vertices_[this->faces_[i][2] - 1];
        Vec3 edge1 = vertex2 - vertex1;
        Vec3 edge2 = vertex3 - vertex1;
        Vec3 normal = edge1.cross(edge2);
        // Apply triangle area-weighting
        double factor = 0.5 * normal.magnitude();
        normal = normal * factor;
        // Update the vertex normals
        this->vertex_normals_[this->faces_[i][0] - 1] = this->vertex_normals_[this->faces_[i][0] - 1] + normal;
        this->vertex_normals_[this->faces_[i][1] - 1] = this->vertex_normals_[this->faces_[i][1] - 1] + normal;
        this->vertex_normals_[this->faces_[i][2] - 1] = this->vertex_normals_[this->faces_[i][2] - 1] + normal;
    }
    // Normalize the vertex normals
    for(int i = 0; i < this->vertex_normals_.size(); i++) {
        this->vertex_normals_[i] = this->vertex_normals_[i].normalize();
    }
}

bool Mesh::isHit(Ray& ray, double minT, double maxT) {
    // Check if the mesh was hit
    std::shared_ptr<Object> hitObject = this->bvh_.detectHit(ray);
    // If mesh was not hit, return false
    if(hitObject == nullptr) {
        return false;
    }
    // Update the hitInfo for the hit
    std::shared_ptr<Triangle> temp = std::static_pointer_cast<Triangle>(hitObject);
    this->hitInfo_.hitpoint = temp->hitInfo().hitpoint;
    // this->hitInfo_.normal = temp->hitInfo().normal;
    this->hitInfo_.t = temp->hitInfo().t;
    // Retrieve the necessary data for the barycentric interpolation
    Point3 v1 = temp->point1();
    Point3 v2 = temp->point2();
    Point3 v3 = temp->point3();
    Vec3 e1 = v3 - v2;
    Vec3 e2 = v1 - v3;
    Vec3 e3 = v2 - v1;
    Vec3 d1 = this->hitInfo_.hitpoint - v1;
    Vec3 d2 = this->hitInfo_.hitpoint - v2;
    Vec3 d3 = this->hitInfo_.hitpoint - v3;
    double b1 = (e1.cross(d3).dot(temp->hitInfo().normal)) / (e1.cross(e2).dot(temp->hitInfo().normal));
    double b2 = (e2.cross(d1).dot(temp->hitInfo().normal)) / (e1.cross(e2).dot(temp->hitInfo().normal));
    double b3 = (e3.cross(d2).dot(temp->hitInfo().normal)) / (e1.cross(e2).dot(temp->hitInfo().normal));
    Vec3 v1_normal = this->vertex_normals_[v1.index()];
    Vec3 v2_normal = this->vertex_normals_[v2.index()];
    Vec3 v3_normal = this->vertex_normals_[v3.index()];
    // Apply barycentric interpolation to the normal
    this->hitInfo_.normal = v1_normal * b1 + v2_normal * b2 + v3_normal * b3;
    // Return true since the mesh was hit
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

std::string Mesh::subclass() {
    return "Mesh";
}
