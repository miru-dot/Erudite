#include "Shader.h"

Shader::Shader(std::string shaderSource, unsigned int shaderType)
{
	m_shaderType = shaderType;

	std::ifstream stream(shaderSource);
	std::string line;
	m_shaderSource = new std::string();
	while (getline(stream, line))
		*m_shaderSource += line + '\n';
}

Shader::~Shader()
{
   if (m_shaderSource)
      delete m_shaderSource;
}

/// <summary>
/// Compiles a shader
/// </summary>
/// <param name="shaderType">The type of the shader to compile e.g. GL_VERTEX_SHADER</param>
/// <param name="shaderSource">The shader source</param>
/// <returns></returns>
unsigned int Shader::compileShader()
{
	unsigned int shader = glCreateShader(m_shaderType);
	const char* src = m_shaderSource->c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		std::cout << "Failed to compile " << (m_shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}