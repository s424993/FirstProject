#pragma once
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "entities/Ship.h"


class Game {
public:
    Game(int width, int height, const std::string &title);
    virtual ~Game();
    void run();
    glm::mat4 calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale);

private:
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
    void update();
    void draw();
    void updateDeltaTime();

    GLFWwindow *window = nullptr;
    std::unique_ptr<Ship> spaceShip;
    float lastFrameTime = 1.0f/60;
    float deltaTime = 1.0f/60;
};
