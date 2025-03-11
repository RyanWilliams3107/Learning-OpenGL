#include "Shader.h"

#include <filesystem>

Shader::Shader(const std::string& filePath, GLenum shaderType)
    : m_filePath(filePath), m_ShaderType(shaderType)
{
    if (readShaderFromFile() && compileShader()) {
        std::cout << "Compiled Shader Successfully" << m_filePath << std::endl;
    }
    else {
        std::cerr << "Failed to compile Shader: " << m_filePath << std::endl;
    }
}

Shader::~Shader()
{
    if (m_Shader) { glDeleteShader(m_Shader); }
}

bool Shader::readShaderFromFile()
{

    std::cout << "Attempting to open: " << std::filesystem::absolute(m_filePath) << std::endl;
    std::ifstream file(m_filePath);

    if (!file) {
        std::cerr << "Failed to open shader file: " << m_filePath << std::endl;
        m_Source = "";
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    m_Source = buffer.str();
    return true;
}

bool Shader::compileShader()
{
    if (m_Source.empty()) {
        std::cerr << "Cannot compile empty shader" << std::endl;
        return NULL;
    }

    m_Shader = glCreateShader(m_ShaderType);
    const char* source = m_Source.c_str();
    glShaderSource(m_Shader, 1, &source, nullptr);
    glCompileShader(m_Shader);

    GLint success;
    char infoLog[512];

    glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(m_Shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<< infoLog << std::endl;
        return false;
    }
    return true;
}

ShaderProgram::ShaderProgram(GLuint vertexShader, GLuint fragmentShader)
: m_VertexShader(vertexShader), m_FragmentShader(fragmentShader) 
{
    CreateShaderProgram();
}

unsigned int ShaderProgram::getShaderProgram()
{
    return 0;
}

void ShaderProgram::linkShaderProgram()
{
    glLinkProgram(m_ShaderProgram);

    int success;
    char infoLog[512];

    glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: Shader Program Creation Failed\n" << infoLog << std::endl;
    }
}

void ShaderProgram::useShaderProgram()
{
    glUseProgram(m_ShaderProgram);
}

bool ShaderProgram::CreateShaderProgram()
{
    m_ShaderProgram = glCreateProgram();

    glAttachShader(m_ShaderProgram, m_VertexShader);
    glAttachShader(m_ShaderProgram, m_FragmentShader);

    return true;
}
