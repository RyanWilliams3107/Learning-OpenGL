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
    glDeleteShader(m_Shader);
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
