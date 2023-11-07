#pragma once

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    Shader(const char *vertexShaderSource, const char *fragmentShaderSource);
    ~Shader();
    void setMatrix(const std::string &uniformName, glm::mat4 matrix) const;
    void setVector(const std::string &uniformName, glm::vec4 vector) const;
    void use();

private:
    unsigned int shaderProgram = 0;
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;

    GLuint loadAndCompileShader(GLuint shaderType, const char *shaderSource);
};

