#pragma once
#include <vector>


class Mesh {
public:
    explicit Mesh(const std::vector<float> &vertices);
    void draw() const;
    virtual ~Mesh();

    // Delete copy constructor
    Mesh(const Mesh &other) = delete;

    // Explicit move constructor
    Mesh(Mesh &&other) noexcept {
        std::swap(this->VBO, other.VBO);
        std::swap(this->numberOfVertices, other.numberOfVertices);
    }

private:
    unsigned int VBO = 0;
    unsigned int numberOfVertices = 0;
};

