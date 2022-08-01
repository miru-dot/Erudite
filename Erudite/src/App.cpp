#include "App.h"

#include <string>
#include <math.h>

#include "OpenGL.h"
#include "Mesh.h"
#include "GameObject.h"

App::App() {}

App::~App() 
{
	terminate();
}

/// <summary>
/// App main loop
/// </summary>
void App::run()
{
	if (!init())
		return;

	OpenGL::polygonMode(GL_FILL);
	OpenGL::enable(GL_BLEND);
	OpenGL::blendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	OpenGL::enable(GL_DEPTH_TEST);

	addGameObjects();

	m_camera->m_transform->m_position->z = -5.0f;

	float deltaTime = 0.0f;
	while (!glfwWindowShouldClose(m_window))
	{
		float start = (float)glfwGetTime();

		handleInput(deltaTime);

		OpenGL::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_scene->render();

		checkGLError();

		glfwSwapBuffers(m_window);
		glfwPollEvents();

		deltaTime = glfwGetTime() - start;
	}
}

/// <summary>
/// Add gameobjects to scene
/// </summary>
void App::addGameObjects()
{
	GameObject* triangle = new GameObject("Fancy Triangle", Mesh::triangle(2.0f), new Texture("res/textures/nikon-df-sample-images-262.jpg"));
	triangle->m_transform->m_position->x = -10;
	m_scene->add(triangle);

	GameObject* cube = new GameObject("Fancy Cube", Mesh::cube(1.5f, 1.5f, 1.0f), new Texture("res/textures/2114387497_1ccd0bd73e.jpg"));
	cube->m_transform->m_position->x = -5;
	m_scene->add(cube);

	GameObject* rectangle = new GameObject("Rectangle", Mesh::rectangle(3.0f, 4.5f), new Texture("res/textures/snow-forest.jpg"));
	m_scene->add(rectangle);

	GameObject* cone = new GameObject("Cone", Mesh::cone(2.5f, 1.0f, 100, glm::vec4(0.7, 0.8, 0.9, 1.0)), new Texture("res/textures/default.png"));
	cone->m_transform->m_position->x = 5;
	m_scene->add(cone);
}

/// <summary>
/// Handle window input
/// </summary>
void App::handleInput(float deltaTime)
{
	float moveSpeed = 5.0f * deltaTime;
	float rotSpeed = 50.0f * deltaTime;

	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) 
		m_camera->m_transform->m_position->z += moveSpeed;
	else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		m_camera->m_transform->m_position->x += moveSpeed;
	else if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) 
		m_camera->m_transform->m_position->z -= moveSpeed;
	else if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) 
		m_camera->m_transform->m_position->x -= moveSpeed;
	else if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
		m_camera->m_transform->m_rotation->y -= rotSpeed;
	else if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
		m_camera->m_transform->m_rotation->y += rotSpeed;
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
	delete m_scene;
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
	// return if minimized
	if (width == 0 || height == 0)
		return;

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
		OpenGL::switchPolygonMode();
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