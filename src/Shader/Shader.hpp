#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>

class Shader
{
private:
    Shader();
    static std::string LoadShader(std::string path);
public:
    ~Shader();
    static unsigned CompileShaders(std::string vertexShaderPath, std::string fragmentShaderPath);
    static void Setf(unsigned shaderProgram, std::string name, float a);
    static void Setf(unsigned shaderProgram, std::string name, float a, float b);
    static void Setf(unsigned shaderProgram, std::string name, float a, float b, float c);
    static void Setf(unsigned shaderProgram, std::string name, float a, float b, float c, float d);

    static void Seti(unsigned shaderProgram, std::string name, int a);
    static void Seti(unsigned shaderProgram, std::string name, int a, int b);
    static void Seti(unsigned shaderProgram, std::string name, int a, int b, int c);
    static void Seti(unsigned shaderProgram, std::string name, int a, int b, int c, int d);
};
