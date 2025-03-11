#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	Shader(const std::string& filePath, GLenum shaderType);
	~Shader();

	GLuint getShader() const { return m_Shader; }
	GLenum getShaderType() const { return m_ShaderType; }

private:
	bool readShaderFromFile();
	bool compileShader();

private:
	std::string m_filePath;
	std::string m_Source;
	GLenum m_ShaderType;
	GLuint m_Shader;
};

