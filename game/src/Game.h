
#pragma once

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"

class Game {
public:
    Game(int width, int height, const std::string &title);
    ~Game();
    void run();
private:
    GLFWwindow *window = nullptr;
    glm::mat4 mvpMatrix;
    Shader *shader = nullptr;

    glm::mat4 calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale);
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void update();
    void draw();
    void updateDeltaTime();
};