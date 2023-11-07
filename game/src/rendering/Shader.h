#pragma once

#include <string>
#include "glad/glad.h"
#include "glm/glm.hpp"

class Shader {
public:
    Shader(const std::string &vertexShaderSource, const std::string &fragmentShaderSource);
    virtual ~Shader();

    // Delete copy constructor
    Shader(const Shader &shader) = delete;

    // Explicit move constructor
    Shader(Shader &&other) noexcept {
        std::swap(this->shaderProgram, other.shaderProgram);
        std::swap(this->vertexShader, other.vertexShader);
        std::swap(this->fragmentShader, other.fragmentShader);
    }

    void setMatrix(const std::string &uniformName, glm::mat4 matrix) const;
    void setVector(const std::string &uniformName, glm::vec4 vector) const;
    void use() const;

private:
    unsigned int loadAndCompileShader(GLuint shaderType, const std::string &shaderSource);

    unsigned int shaderProgram = 0;
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;
};


