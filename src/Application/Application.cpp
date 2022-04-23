#include "Application.hpp"
#include "../Shader/Shader.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

Application *Application::instance = nullptr;
Application *Application::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Application();
    }
    return instance;
}
Application::Application()
{
}
Application::~Application()
{
}

void Application::DestroyInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

void Application::Init(int width, int height, std::string title,bool resizeable)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->resizeable = resizeable;
    LoadGLFW();
    LoadGLEW();
    LoadImGui();
    SetupRenderingScreen();
    if((this->shaderProgram = Shader::CompileShaders("shaders/vert.vs", "shaders/frag.fs")) == 0)
    {
        std::cerr << "ERROR: Shader compilation failed" << std::endl;
        Cleanup();
        exit(EXIT_FAILURE);
    }
    
}

void Application::LoadGLFW()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, this->resizeable);

    // glfw window creation
    // --------------------
    this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
    if (!this->window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;

        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(this->window);
    glfwSetFramebufferSizeCallback(this->window, this->FrameBufferSizeCallback);
}
void Application::LoadImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}



void Application::LoadGLEW()
{

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Application::SetupRenderingScreen(){
     // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        -1.0f, -1.0f, 0.0f, // left  
         3.0f, -1.0f, 0.0f, // right 
        -1.0f,  3.0f, 0.0f  // top   
    }; 


    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Application::Cleanup()
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteProgram(this->shaderProgram);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();



    glfwDestroyWindow(this->window);    
    glfwTerminate();
}

void Application::Run()
{

    double lastTime = glfwGetTime();
    int frames = 0;

    while (!glfwWindowShouldClose(this->window))
    {

        double currentTime = glfwGetTime();
        ++frames;
        if(currentTime - lastTime >= 1.0){
            //printf("%f ms/frame\n",1000.0/double(frames));
            this->fps = frames;
            frames = 0;
            lastTime += 1.0;
        }
        glfwGetWindowSize(this->window, &this->width, &this->height);
        ProcessInput();
        RenderScreen();
    }
    Cleanup();
}

void Application::FrameBufferSizeCallback(GLFWwindow *window, int width, int height)
{

    (void)window;
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Application::RenderScreen()
{
    // render
    // ------
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // draw our first triangle

    glUseProgram(this->shaderProgram);
    Shader::Setf(this->shaderProgram, "res", (float)this->width,(float)this->height);
    Shader::Setf(this->shaderProgram, "time", glfwGetTime());

    //printf("%d %d\n",app.window.width,app.window.height);
    glBindVertexArray(this->VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time 

    RenderUI();

    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void Application::RenderUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Stats");
    ImGui::Text("FPS: %d", this->fps);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::ProcessInput()
{
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);
}
