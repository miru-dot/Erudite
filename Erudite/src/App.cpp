#include "App.h"

#include <string>

#include "Shader.h"
#include "Texture.h"
#include "MeshRenderer.h"

#include "VertexBufferObject.h"
#include "ElementBufferObject.h"
#include "VertexArrayObject.h"

#include "Renderer.h"
#include "GameObject.h"

App::App() {}

App::~App() {}

/// <summary>
/// App main loop
/// </summary>
void App::run()
{
	if (!init())
		return;

	Renderer::polygonMode(GL_FILL);
	Renderer::enable(GL_BLEND);
	Renderer::blendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Renderer::enable(GL_DEPTH_TEST);

	std::vector<GameObject*> gameObjects = {
		Renderer::rectangle(3.0f, 4.5f, glm::vec4(1.0, 1.0, 1.0, 1.0), new Texture("res/textures/snow-forest.jpg")),
		Renderer::cube(1.5f, 1.5f, 1.0f, glm::vec4(1.0, 1.0, 1.0, 1.0), glm::vec4(0.0, 0.0, 0.0, 1.0))
	};

	m_camera->m_transform->m_position->z = -2.0f;
	float deltaTime = 0.0f;
	while (!glfwWindowShouldClose(m_window))
	{
		float start = (float)glfwGetTime();

		handleInput(deltaTime);

		Renderer::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (GameObject* object : gameObjects)
		{
			object->m_transform->m_rotation->y += deltaTime * 5.0f;
			object->transform();
			object->render();
		}

		checkGLError();

		glfwSwapBuffers(m_window);
		glfwPollEvents();

		deltaTime = glfwGetTime() - start;
	}
	
	gameObjects.clear();
	gameObjects.shrink_to_fit();

	terminate();
}

/// <summary>
/// Handle window input
/// </summary>
void App::handleInput(float deltaTime)
{
	float speed = 5.0f * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) 
		m_camera->m_transform->m_position->z += speed;
	else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_camera->m_transform->m_position->x += speed;
	else if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) 
		m_camera->m_transform->m_position->z -= speed;
	else if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) 
		m_camera->m_transform->m_position->x -= speed;
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
	Camera::instance()->destroy();
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

	m_window = glfwCreateWindow(m_width, m_height, "SILIAN OPENGL", NULL, NULL);
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
	Camera::instance()->m_ratio = (float)width / (float)height;
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