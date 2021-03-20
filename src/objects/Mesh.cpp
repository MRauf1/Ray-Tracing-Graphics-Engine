#include "Mesh.h"

Mesh::Mesh() {
    this->color_ = Color3(1.0, 1.0, 1.0);
}

Mesh::Mesh(std::string file_name) {
    this->color_ = Color3(1.0, 1.0, 1.0);
    this->readMesh(file_name);
}

std::vector<std::shared_ptr<Object>> Mesh::objects() const {
    return this->objects_;
}

void Mesh::readMesh(std::string file_name) {
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
                        std::shared_ptr<Object> temp = std::make_shared<Triangle>(this->color_, vertices[face[0]], vertices[face[1]], vertices[face[2]]);
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
    return true;
}

void Mesh::makeAABB() {

}
