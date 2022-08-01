#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Camera.h"
#include "Scene.h"

class App 
{
public:
   App();                                                            // consturctor
   ~App();                                                           // destructor
   void run();                                                       // programm loop

private:
   void addGameObjects();                                            // add gameobjects
   void handleInput(float deltaTime);                                // handle input
   bool init();                                                      // initalizes the programm   
   void terminate();                                                 // terminates the programm 
   bool createContext();                                             // creates GLFW window used as render context 

   static void framebufferSizeCallback(GLFWwindow* window,
      int width, int height);                                        // called if the window is resized
   static void keyPressedCallback(GLFWwindow* window, int key,
      int scancode, int action, int mods);                           // process keyboard input callback
   static void checkGLError();                                       // check for open gl errors it will output all errors

   GLFWwindow* m_window = nullptr;                                   // the render context
   Camera* m_camera = Camera::instance();                            // camera
   Scene* m_scene = new Scene();                                     // scene
   const int m_width = 1920;                                         // window width
   const int m_height = 1080;                                        // window height
};