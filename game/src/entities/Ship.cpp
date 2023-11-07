
#include "Ship.h"

const char *vertexShaderSource = R"(
        #version 460 core
        layout (location = 0) in vec3 aPos;
        uniform mat4 mvp;
        void main() {
            gl_Position = mvp * vec4(aPos.xyz, 1.0);
        }
    )";

const char *fragmentShaderSource = R"(
        #version 460 core
        uniform vec4 color;
        out vec4 fragColor;
        void main() {
            fragColor = color;
        }
    )";


Ship::Ship(glm::vec3 position, float zRotation, glm::vec3 scale) : Entity(Shader(vertexShaderSource, fragmentShaderSource),
                                                                          Mesh({
                                                                                       // Center
                                                                                       0.0f, 0.0f, 0.0f,
                                                                                       -0.05f, 0.1f, 0.0f,
                                                                                       -0.05f, -0.1f, 0.0f,

                                                                                       // Front Tip
                                                                                       0.0f, 0.0f, 0.0f,
                                                                                       0.1f, 0.025f, 0.0f,
                                                                                       0.1f, -0.025f, 0.0f,

                                                                                       // Lower wing
                                                                                       -0.05f, -0.1f, 0.0f,
                                                                                       0.1f, -0.025f, 0.0f,
                                                                                       -0.1f, -0.05f, 0.0f,

                                                                                       // Upper wing
                                                                                       -0.05f, 0.1f, 0.0f,
                                                                                       0.1f, 0.025f, 0.0f,
                                                                                       -0.1f, 0.05f, 0.0f,

                                                                                       // Tail
                                                                                       0.14f, 0.0f, 0.0f,
                                                                                       0.1f, 0.025f, 0.0f,
                                                                                       0.1f, -0.025f, 0.0f,

                                                                                       // Central Hub
                                                                                       0.0f, 0.0f, 0.0f,
                                                                                       -0.075f, 0.03f, 0.0f,
                                                                                       -0.075f, -0.03f, 0.0f
                                                                               }),
                                                                          position,
                                                                          zRotation,
                                                                          scale,
                                                                          {0.2f, 0.7f, 0.1f, 1.0f}) {

}

void Ship::update(GLFWwindow *window, float deltaTime) {
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        zRotation += rotationSpeed * deltaTime;
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        zRotation -= rotationSpeed * deltaTime;
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position.y += sin(glm::radians(zRotation)) * translationSpeed * deltaTime;
        position.x += cos(glm::radians(zRotation)) * translationSpeed * deltaTime;
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position.y -= sin(glm::radians(zRotation)) * translationSpeed * deltaTime;
        position.x -= cos(glm::radians(zRotation)) * translationSpeed * deltaTime;
    }
}


