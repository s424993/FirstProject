#pragma once
#include "Entity.h"

class Ship: public Entity {
public:
    explicit Ship(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                  float zRotation = 0.0f,
                  glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
    void update(GLFWwindow *window, float deltaTime) override;

private:
    float translationSpeed = 1.0f;
    float rotationSpeed = 120.0f;
};

