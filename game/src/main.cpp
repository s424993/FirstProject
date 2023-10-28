#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

const char *vertexShaderSource = R"(
    #version 460 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos.xyz, 1.0);
    }
)";

const char *fragmentShaderSource = R"(
    #version 460 core
    out vec4 fragColor;
    void main() {
        fragColor = vec4(0.2f, 0.7f, 0.1f, 1.0f);
    }
)";

float vertices[] = {
        // Center
        0.0f, 0.0f, 0.0f,   // Vertex 1
        -0.05f, 0.1f, 0.0f, // Vertex 2
        -0.05f, -0.1f, 0.0f, // Vertex 3

        // Front Tip
        0.0f, 0.0f, 0.0f,        // Vertex 4
        0.1f, 0.025f, 0.0f,     // Vertex 5
        0.1f, -0.025f, 0.0f,    // Vertex 6

        // Lower wing
        -0.05f, -0.1f, 0.0f,  // Vertex 10
        0.1f, -0.025f, 0.0f,   // Vertex 11
        -0.1f, -0.05f, 0.0f,  // Vertex 12

        // Upper wing
        -0.05f, 0.1f, 0.0f,  // Vertex 10
        0.1f, 0.025f, 0.0f,   // Vertex 11
        -0.1f, 0.05f, 0.0f,  // Vertex 12

        // Tail
        0.2f, 0.0f, 0.0f,        // Vertex 13
        0.1f, 0.025f, 0.0f,     // Vertex 1
        0.1f, -0.025f, 0.0f,    // Vertex 15

        // Central Hub
        0.0f, 0.0f, 0.0f,         // Vertex 1
        -0.075f, 0.03f, 0.0f,       // Vertex 2
        -0.075f, -0.03f, 0.0f,        // Vertex 3

};

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    // Define OpenGL version (4.6)
    // -------------------------------------------------
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "GameLabIII", nullptr, nullptr);
    if(window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 110);   // <-- new line

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();

    return 0;

}

