#include "App.h"

App::App() {}

App::~App() {}

/// <summary>
/// App main loop
/// </summary>
void App::run()
{
	if (!init())
		return;

	float vertices[] = {
		 0.0f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f,
	};

	unsigned int indices[] = {
		0, 1, 2,	// Triangle 1
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int shaderProgram = createShader();
	glUseProgram(shaderProgram);

	checkGLError();

	while (!glfwWindowShouldClose(m_window))
	{
		processInput();

		glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		int size;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
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
		cout << "Failed to create GLFW window" << endl;
		terminate();
		return false;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return false;
	}

	cout << "GL version: " << glGetString(GL_VERSION) << endl;

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
/// Compiles a shader
/// </summary>
/// <param name="shaderType">The type of the shader to compile e.g. GL_VERTEX_SHADER</param>
/// <param name="shaderSource">The shader source</param>
/// <returns></returns>
unsigned int App::compileShader(unsigned int shaderType, const string& shaderSource)
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
		cout << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment") << endl;
		cout << message << endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

/// <summary>
/// Compiles the vertex and fragment shader and links the program
/// </summary>
/// <returns>returns the linked program</returns>
unsigned int App::createShader()
{
	unsigned int program = glCreateProgram();
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, VertexShader);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER , FragmentShader);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	//glValidateProgram(program);

	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);
		cout << "Failed Program linking : " << message << endl;
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
			cout << "GL_INVALID_ENUM - An unacceptable value is specified for an enumerated argument." << endl;
			break;

		case GL_INVALID_VALUE:
			cout << "GL_INVALID_VALUE - A numeric argument is out of range." << endl;
			break;

		case GL_INVALID_OPERATION:
			cout << "GL_INVALID_OPERATION - The specified operation is not allowed in the current state." << endl;
			break;

		case GL_INVALID_FRAMEBUFFER_OPERATION:
			cout << "GL_INVALID_FRAMEBUFFER_OPERATION - The framebuffer object is not complete." << endl;
			break;

		case GL_OUT_OF_MEMORY:
			cout << "GL_OUT_OF_MEMORY - There is not enough memory left to execute the command." << endl;
			break;

		case GL_STACK_UNDERFLOW:
			cout << "GL_STACK_UNDERFLOW - An attempt has been made to perform an operation that would cause an internal stack to underflow." << endl;
			break;

		case GL_STACK_OVERFLOW:
			cout << "GL_STACK_OVERFLOW - An attempt has been made to perform an operation that would cause an internal stack to overflow." << endl;
			break;
		}	
	}
}