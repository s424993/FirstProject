#include "Game.h"

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
    out vec4 fragColor;
    void main() {
        fragColor = vec4(0.2f, 0.7f, 0.1f, 1.0f);
    }
)";

float vertices[54] = {
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
        -0.075f, -0.03f, 0.0f,

};

float zRotation = 0.0f;
float rotationSpeed = 120.0f;
float xTranslate = 0.0f;
float yTranslate = 0.0f;
float translationSpeed = 1.0f;
float deltaTime;
float lastFrameTime;

Game::Game(int width, int height, const std::string &title) {
    glfwInit();
    if(!glfwInit()) {
        throw std::runtime_error("Failed to initialize glfw");
    }
    // Define OpenGL version (4.6)
    // -------------------------------------------------
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if(window == nullptr) {
        throw std::runtime_error("Failed to create window");
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if(glGetError() != GL_NO_ERROR) {
        throw std::runtime_error("gl error");
    }
}

Game::~Game() {
    delete shader;
    glfwTerminate();
}

glm::mat4 Game::calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale) {
    glm::mat4 mvp = glm::mat4(1.0f);
    mvp = glm::translate(mvp, position);
    mvp = glm::rotate(mvp, glm::radians(zRotationInDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
    mvp = glm::scale(mvp, scale);


    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 0.0, 90.0f),
                                 glm::vec3(0.0f, 0.0f, 0.0),
                                 glm::vec3(0.0, 1.0, 0.0));

    glm::mat4 projection = glm::perspective(glm::radians(2.0f), 1000.0f/600.0f, 0.1f, 100.0f);

    glm::mat4 mvpMatrix = projection * view * mvp;

    return mvp;
}

void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::update() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        zRotation += rotationSpeed * deltaTime;
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        zRotation -= rotationSpeed * deltaTime;
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        yTranslate += sin(glm::radians(zRotation)) * translationSpeed * deltaTime;
        xTranslate += cos(glm::radians(zRotation)) * translationSpeed * deltaTime;
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        yTranslate -= sin(glm::radians(zRotation)) * translationSpeed * deltaTime;
        xTranslate -= cos(glm::radians(zRotation)) * translationSpeed * deltaTime;
    }

    mvpMatrix = calculateMvpMatrix(glm::vec3(xTranslate, yTranslate, 0.0f), zRotation, glm::vec3(.5f, .5f, .5f));
}

void Game::draw() {
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 18);

    shader->setMatrix("mvp", mvpMatrix);

    glfwSwapBuffers(window);
}

void Game::updateDeltaTime() {
    // Update delta time
    float frameTime = glfwGetTime();
    deltaTime = frameTime - lastFrameTime;
    lastFrameTime = frameTime;
}

void Game::run() {
    shader = new Shader(vertexShaderSource, fragmentShaderSource);
    shader -> use();

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);

    glfwSetTime(1.0/60);

    while(!glfwWindowShouldClose(window)) {
        update();
        draw();
        updateDeltaTime();
        glfwPollEvents();
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}



