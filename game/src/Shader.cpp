#include "Shader.h"

struct glStatusData {
    int success;
    const char *shaderName;
    char infoLog[GL_INFO_LOG_LENGTH];
};

Shader::Shader(const char *vertexShaderSource, const char *fragmentShaderSource) {
    vertexShader = loadAndCompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    fragmentShader = loadAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

}

GLuint Shader::loadAndCompileShader(GLuint shaderType, const char *shaderSource) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    glStatusData compilationStatus{};
    compilationStatus.shaderName = shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment";
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compilationStatus.success);
    if(compilationStatus.success == GL_FALSE) {
        glGetShaderInfoLog(shader, GL_INFO_LOG_LENGTH, nullptr, compilationStatus.infoLog);
        throw std::runtime_error("ERROR: " + std::string(compilationStatus.shaderName) + " shader compilation failed.\n" +
                                 std::string(compilationStatus.infoLog));
    }

    return shader;
}

Shader::~Shader() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::setMatrix(const std::string& uniformName, glm::mat4 matrix) const {
    GLint location = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniformMatrix4fv(location, 1,GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVector(const std::string& uniformName, glm::vec4 vector) const {
    GLint location = glGetUniformLocation(shaderProgram, uniformName.c_str());
    glUniform4fv(location, 1, glm::value_ptr(vector));
}

void Shader::use() {
    glUseProgram(shaderProgram);
}
