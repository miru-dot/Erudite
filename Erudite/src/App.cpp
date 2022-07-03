#include "App.h"

#include "Shader.h"
#include "Texture.h"

#include "VertexBufferObject.h"
#include "ElementBufferObject.h"
#include "VertexArrayObject.h"

#include "Renderer.h"
#include <string>

App::App() 
{
	m_rotAxis = &m_axisY;
	m_geometry = RECTANGLE;
}

App::~App() 
{
}

/// <summary>
/// App main loop
/// </summary>
void App::run()
{
	if (!init())
		return;

	int texSlot = 0;
	Shader shader("res/VertexShader.vert", "res/FragmentShader.frag");
	shader.bind();
	shader.setU1i("u_texture", texSlot);

	Texture def("res/textures/default.png");
	Texture snow("res/textures/snow-forest.jpg");

	def.bind(texSlot);

	float ratio = (float)m_width / (float)m_height;
	glm::mat4 proj = glm::perspective(90.0f, ratio, 0.1f, 100.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
	glm::mat4 model = glm::mat4(1.0f);	

	Renderer::polygonMode(GL_FILL);
	Renderer::enable(GL_BLEND);
	Renderer::blendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float deltaTime = 0.0f;
	while (!glfwWindowShouldClose(m_window))
	{
		double start = glfwGetTime();

		handleInput();

		Renderer::clear();
	
		def.bind(texSlot);

		model = glm::rotate(model, glm::radians(deltaTime * 35.0f), *m_rotAxis);
		glm::mat4 mvp = proj * view * model;
		shader.setUMat4("u_mvp", mvp);

		switch (m_geometry) 
		{
			case TRIANGLE: Renderer::triangle(1.5f); break;
			case RECTANGLE: {
				snow.bind(texSlot);
				Renderer::rectangle(1.0f, 1.5f);
				break;
			}
			case QUBE: Renderer::cube(1.2f, 0.7f, 1.4f, glm::vec4(0.4, 1.0, 0.5, 1.0)); break;
			case CONE: Renderer::cone(1.5f, 0.75f, 32.0f, glm::vec4(0.4, 0.5, 1.0, 1.0)); break;
		}

		checkGLError();

		glfwSwapBuffers(m_window);
		glfwPollEvents();

		deltaTime = glfwGetTime() - start;
	}

	terminate();
}

/// <summary>
/// Handle window input
/// </summary>
void App::handleInput()
{
	if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
		m_geometry = TRIANGLE;
	else if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		m_geometry = RECTANGLE;
	else if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
		m_geometry = QUBE;
	else if (glfwGetKey(m_window, GLFW_KEY_R) == GLFW_PRESS)
		m_geometry = CONE;
	else if (glfwGetKey(m_window, GLFW_KEY_Z) == GLFW_PRESS)
		m_rotAxis = &m_axisY;
	else if (glfwGetKey(m_window, GLFW_KEY_X) == GLFW_PRESS)
		m_rotAxis = &m_axisX;
	else if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS)
		m_rotAxis = &m_axisZ;
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

	m_window = glfwCreateWindow(m_width, m_height, "I BIMS DE SILIAN", NULL, NULL);
	if (m_window == nullptr)
		return false;

	glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
	glfwSetKeyCallback(m_window, keyPressedCallback);

	return true;
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
/// Kayboard input callback
/// </summary>
/// <param name="window">The window</param>
/// <param name="key">The keycode</param>
/// <param name="scancode"></param>
/// <param name="action">The action is one of GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE</param>
/// <param name="mods"></param>
void App::keyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (window == nullptr)
		return;

	if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
		Renderer::switchPolygonMode();
	else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
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