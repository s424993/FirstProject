#pragma once


class Shader {
private:
    unsigned int shaderProgram = 0;
    unsigned int vertexShader = 0;
    unsigned int fragmentShader = 0;


    Shader();
    ~Shader();
    void setMatrix();
    void setVector();
};

