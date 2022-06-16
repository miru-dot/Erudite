#include "Shader.h"

/// <summary>
/// Create a new vertex and fragement shader
/// </summary>
/// <param name="vertexShaderFile"></param>
/// <param name="fragementShaderFile"></param>
Shader::Shader(const std::string& vertexShaderFile, const std::string& fragementShaderFile)
{
	parseSource(vertexShaderFile, m_vertexShaderSource);
	parseSource(fragementShaderFile, m_fragmentShaderSource);

	m_id = createShader();
}

/// <summary>
/// Delete this shader program
/// </summary>
Shader::~Shader()
{
	if (m_vertexShaderSource)
		delete m_vertexShaderSource;
	if (m_fragmentShaderSource)
		delete m_fragmentShaderSource;

	glDeleteProgram(m_id);
}

/// <summary>
/// Parse the source file and write its content into content
/// </summary>
/// <param name="sourcefile"></param>
/// <param name="content"></param>
void Shader::parseSource(std::string sourcefile, std::string* content)
{
	std::ifstream stream(sourcefile);
	std::string line;
	while (getline(stream, line))
		*content += line + '\n';
}


/// <summary>
/// Compiles the vertex and fragment shader and links the program
/// </summary>
/// <returns>returns the linked program</returns>
unsigned int Shader::createShader()
{
	unsigned int program = glCreateProgram();
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, *m_vertexShaderSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, *m_fragmentShaderSource);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);
		std::cout << "Failed Program linking : " << message << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}


/// <summary>
/// Compiles a shader
/// </summary>
/// <param name="shaderType">The type of the shader to compile e.g. GL_VERTEX_SHADER</param>
/// <param name="shaderSource">The shader source</param>
/// <returns></returns>
unsigned int Shader::compileShader(unsigned int shaderType, std::string& shaderSource)
{
	unsigned int shader = glCreateShader(shaderType);
	const char* src = shaderSource.c_str();
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
		std::cout << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

/// <summary>
/// bind shader program
/// </summary>
void Shader::bind()
{
	glUseProgram(m_id);
}

/// <summary>
/// unbind shader program, set to default program 0
/// </summary>
void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::setU4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

void Shader::setUMat4(const std::string& name, glm::mat4 matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

unsigned int Shader::getUniformLocation(const std::string& name)
{
	if (m_unformLocations.find(name) != m_unformLocations.end())
		return m_unformLocations[name];

	int location = glGetUniformLocation(m_id, name.c_str());
	if (location == -1)
		std::cout << "error: unform " << name << "does not exist!" << std::endl;

	return m_unformLocations[name] = location;
}