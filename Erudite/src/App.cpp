#include "App.h"
#include "Shader.h"

#include "VertexBufferObject.h"
#include "ElementBufferObject.h"
#include "VertexArrayObject.h"

#include "Draw.h"

App::App() {}

App::~App() {}

/// <summary>
/// App main loop
/// </summary>
void App::run()
{
	if (!init())
		return;

	unsigned int shaderProgram = createShader();
	glUseProgram(shaderProgram);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(m_window))
	{
		processInput();

		Draw::clear();
	
		//Draw::rectangle(1.0f, 1.0f);
		Draw::cube(1.0f, 1.0f, 1.5f);

		checkGLError();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	terminate();
}

/// <summary>
/// Initalizes the programm
/// </summary>
/// <returns>returns true if initalizing was successful</returns>
bool App::init()
{
	if (!App::createContext()) {
		std::cout << "Failed to create GLFW window" << std::endl;
		terminate();
		return false;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;

	return true;
}

/// <summary>
/// Terminates the app properly
/// </summary>
void App::terminate()
{
	glfwTerminate();
}

/// <summary>
/// Create app context
/// </summary>
/// <returns>returns true if context was created successful</returns>
bool App::createContext()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_length, "SAE OpenGL", NULL, NULL);
	if (m_window == nullptr)
		return false;

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

	return true;
}

/// <summary>
/// Process window keyboard input
/// </summary>
void App::processInput()
{
	if (m_window && glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
}

/// <summary>
/// Compiles the vertex and fragment shader and links the program
/// </summary>
/// <returns>returns the linked program</returns>
unsigned int App::createShader()
{
	unsigned int program = glCreateProgram();
	Shader vs("res/VertexShader.vert", GL_VERTEX_SHADER);
	Shader fs("res/FragmentShader.frag", GL_FRAGMENT_SHADER);

	unsigned int vertexShader = vs.compileShader();
	unsigned int fragmentShader = fs.compileShader();

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
/// Updates the viewport if the windows gets resized
/// </summary>
/// <param name="window">Render context GLFWwindow</param>
/// <param name="width">Width of the window</param>
/// <param name="height">Height of the window</param>
void App::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/// <summary>
/// Check for open gl errors
/// </summary>
void App::checkGLError()
{
	while (GLenum error = glGetError()) 
	{
		switch (error) 
		{
		case GL_INVALID_ENUM:
			std::cout << "GL_INVALID_ENUM - An unacceptable value is specified for an enumerated argument." << std::endl;
			break;

		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_VALUE - A numeric argument is out of range." << std::endl;
			break;

		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION - The specified operation is not allowed in the current state." << std::endl;
			break;

		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION - The framebuffer object is not complete." << std::endl;
			break;

		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY - There is not enough memory left to execute the command." << std::endl;
			break;

		case GL_STACK_UNDERFLOW:
			std::cout << "GL_STACK_UNDERFLOW - An attempt has been made to perform an operation that would cause an internal stack to underflow." << std::endl;
			break;

		case GL_STACK_OVERFLOW:
			std::cout << "GL_STACK_OVERFLOW - An attempt has been made to perform an operation that would cause an internal stack to overflow." << std::endl;
			break;
		}	
	}
}