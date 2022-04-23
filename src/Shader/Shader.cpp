#include "Shader.hpp"

Shader::Shader()
{
}

Shader::~Shader()
{
}

unsigned Shader::CompileShaders(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    
    std::string fragmentShaderSource = Shader::LoadShader(fragmentShaderPath);
    std::string vertexShaderSource = Shader::LoadShader(vertexShaderPath);

    const char *vertexShaderSourcePtr = vertexShaderSource.c_str();
    const char *fragmentShaderSourcePtr = fragmentShaderSource.c_str();

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourcePtr, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);

        std::cerr << "ERROR: Vertex shader compilation failed\n"
                  << infoLog << std::endl;
        return 0;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourcePtr, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR: Fragment shader compilation failed\n"
                  << infoLog << std::endl;
        return 0;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR: Shader linking Failed\n"
                  << infoLog << std::endl;

        return 0;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::string Shader::LoadShader(std::string path)
{
    std::string result = std::string();
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << path << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line;
    while (std::getline(file, line))
        result += line + "\n";
    
    file.close();
    return result;
}

void Shader::Setf(unsigned shaderProgram, std::string name, float a)
{
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), a);
}

void Shader::Setf(unsigned shaderProgram, std::string name, float a, float b)
{
    glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), a, b);
}

void Shader::Setf(unsigned shaderProgram, std::string name, float a, float b, float c)
{
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), a, b, c);
}

void Shader::Setf(unsigned shaderProgram, std::string name, float a, float b, float c, float d)
{
    glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), a, b, c, d);
}

void Shader::Seti(unsigned shaderProgram, std::string name, int a)
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), a);
}

void Shader::Seti(unsigned shaderProgram, std::string name, int a, int b)
{
    glUniform2i(glGetUniformLocation(shaderProgram, name.c_str()), a, b);
}

void Shader::Seti(unsigned shaderProgram, std::string name, int a, int b, int c)
{
    glUniform3i(glGetUniformLocation(shaderProgram, name.c_str()), a, b, c);
}

void Shader::Seti(unsigned shaderProgram, std::string name, int a, int b, int c, int d)
{
    glUniform4i(glGetUniformLocation(shaderProgram, name.c_str()), a, b, c, d);
}
