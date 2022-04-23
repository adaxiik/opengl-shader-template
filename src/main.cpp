#include <iostream>
#include "Application/Application.hpp"
int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    Application::GetInstance()->Init(800, 600, "Game of Life", false);
    glfwSwapInterval(0);
    Application::GetInstance()->Run();
    Application::DestroyInstance();

    return 0;
}
