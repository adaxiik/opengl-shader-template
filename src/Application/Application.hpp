#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Application
{
private:
    GLFWwindow* window;
    int width;
    int height;
    bool resizeable;
    std::string title;

    unsigned VAO,VBO,shaderProgram; 
    int fps;

    static Application* instance;
    Application();
    ~Application();

    static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
    void ProcessInput();

    void LoadGLFW();
    void LoadGLEW();
    void LoadImGui();
    void SetupRenderingScreen();
    void RenderUI();
    void Cleanup();
public:
    static Application* GetInstance();
    static void DestroyInstance();
    void Run();
    void Init(int width, int height, std::string title,bool resizeable);
    void RenderScreen(); // render the scene including the UI
    
};
