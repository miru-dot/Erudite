#include "App.h"

#include <string>
#include <math.h>

#include "OpenGL.h"
#include "Mesh.h"
#include "GameObject.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

/// <summary>
/// Constructor
/// </summary>
App::App() :
	m_backgroundColor(glm::vec4(0.25f, 0.25f, 0.45f, 1.0f))
{}

/// <summary>
/// Destructor
/// </summary>
App::~App() 
{
	Camera::instance()->destroy();
	Light::instance()->destroy();
	delete m_scene;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
}

/// <summary>
/// App main loop
/// </summary>
void App::run()
{
	if (!init())
		return;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

	ImGui::StyleColorsDark();

	OpenGL::enable(GL_DEPTH_TEST);
	OpenGL::enable(GL_CULL_FACE);
	OpenGL::frontFace(GL_CW);
	OpenGL::enable(GL_BLEND);
	OpenGL::blendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	OpenGL::polygonMode(GL_FILL);

	addGameObjects();

	glm::vec3* pos = new glm::vec3(1.0f, 1.0f, 1.0f);

	float deltaTime = 0.0f;
	while (!glfwWindowShouldClose(m_window))
	{
		float start = (float)glfwGetTime();

		handleInput(deltaTime);

		glClearColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
		OpenGL::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		m_scene->render();

		checkGLError();

		ui();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
	/* triangle
	GameObject* triangle = new GameObject("Nature Triangle", Mesh::triangle(2.0f, glm::vec4(0.2f, 0.2f, 0.8f, 1.0f)));
	triangle->m_transform->m_position->x = 5;
	triangle->m_transform->m_rotation->x = -90;
	m_scene->add(triangle);
	*/

	//rectangle
	GameObject* rectangle = new GameObject("Snowy Rectangle", Mesh::rectangle(1.5f, 2.0f), new Texture("res/textures/snow-forest.jpg"));
	rectangle->m_transform->m_position->x = -5;
	rectangle->m_transform->m_rotation->x = -90;
	m_scene->add(rectangle);

	// cube
	GameObject* cube = new GameObject("Fancy Cube", Mesh::cube(1.0f, 1.0f, 1.0f), new Texture("res/textures/wood.png"));
	m_scene->add(cube);

	//cone
	MeshRenderer* coneMesh = Mesh::cone(2.5f, 1.0f, 100, glm::vec4(0.7, 0.8, 0.9, 1.0));
	coneMesh->primitive(GL_LINES);
	GameObject* cone = new GameObject("Line Cone", coneMesh, new Texture("res/textures/000010806.jpg"));
	cone->m_transform->m_position->x = 5;
	m_scene->add(cone);
}

/// <summary>
/// Build imGUI ui
/// </summary>
void App::ui()
{
	ImGui::Begin("Settings");

	ImGui::BeginGroup();
	ImGui::Text("Window");
	ImGui::ColorEdit3("Background Color", (float*)&m_backgroundColor);
	ImGui::EndGroup();

	ImGui::NewLine();

	ImGui::BeginGroup();
   ImGui::Text("Light");
	if(m_light->m_lightData->m_isDirectionalLight)
		ImGui::DragFloat3("Direction", (float*)m_light->m_transform->m_position, 0.1f, -1.0f, 1.0f);
	else
		ImGui::DragFloat3("Position", (float*)m_light->m_transform->m_position, 0.1f);
	ImGui::ColorEdit3("Light Color", (float*)&m_light->m_lightData->m_color);
	ImGui::ColorEdit3("Ambient Color", (float*)&m_light->m_lightData->m_ambientColor);
	ImGui::SliderFloat("Ambient Intensity", &m_light->m_lightData->m_ambientIntensity, 0.0f, 1.0f);
	ImGui::SliderFloat("Diffuse Intensity", &m_light->m_lightData->m_diffuseIntensity, 0.0f, 1.0f);
	ImGui::SliderFloat("Specular Intensity", &m_light->m_lightData->m_specularIntensity, 0.0f, 1.0f);
	ImGui::DragFloat("Hardness", &m_light->m_lightData->m_hardness, 5.0f);
	ImGui::Checkbox("Is Directional", &m_light->m_lightData->m_isDirectionalLight);
	ImGui::EndGroup();
	
	ImGui::NewLine();
	
	ImGui::BeginGroup();
	ImGui::Text("Camera");
	ImGui::DragFloat3("Camera Translation", (float*)m_camera->m_transform->m_position, 0.1f);
	ImGui::SliderFloat3("Camera Rotation", (float*)m_camera->m_transform->m_rotation, 0.0f, 360.0f);
	ImGui::DragFloat3("Camera Scale", (float*)m_camera->m_transform->m_scale, 0.1f, 0.0);
	ImGui::EndGroup();

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Begin("Scene");
	for (auto object : *m_scene->all())
	{
		if (!object)
			continue;

		std::string name = object->m_name;

		ImGui::BeginGroup();
		ImGui::Text(name.c_str());
		ImGui::DragFloat3((name + " Translation").c_str(), (float*)object->m_transform->m_position, 0.1f);
		ImGui::SliderFloat3((name + " Rotation").c_str(), (float*)object->m_transform->m_rotation, 0.0f, 360.0f);
		ImGui::DragFloat3((name + " Scale").c_str(), (float*)object->m_transform->m_scale, 0.1f, 0.0);
		ImGui::Checkbox(("Enable " + name).c_str(), &object->m_active);
		ImGui::EndGroup();

		ImGui::NewLine();
	}
	ImGui::End();
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
/// Create app context
/// </summary>
/// <returns>returns true if context was created successful</returns>
bool App::createContext()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(m_width, m_height, "OPENGL", NULL, NULL);
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

	if (key == GLFW_KEY_U && action == GLFW_PRESS)
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