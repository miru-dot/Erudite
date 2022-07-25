#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>
#include "Camera.h"

class App 
{
public:
   App();                                                            // consturctor
   ~App();                                                           // destructor
   void run();                                                       // programm loop
   static void checkGLError();                                       // check for open gl errors it will output all errors

private:
   void handleInput(float deltaTime);                                // handle input
   bool init();                                                      // initalizes the programm   
   void terminate();                                                 // terminates the programm 
   bool createContext();                                             // creates GLFW window used as render context 
   
   static void framebufferSizeCallback(GLFWwindow* window,           // called if the window is resized
      int width, int height);
   static void keyPressedCallback(GLFWwindow* window, int key,
      int scancode, int action, int mods);                           // process keyboard input callback

   GLFWwindow* m_window = nullptr;                                   // the render context
   Camera* m_camera = Camera::instance();                            // camera
   const int m_width = 1920;                                         // window width
   const int m_height = 1080;                                        // window height
};