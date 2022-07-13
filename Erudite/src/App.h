#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

class App 
{
public:
   App();                                                            // consturctor
   ~App();                                                           // destructor
   void run();                                                       // programm loop
   static void checkGLError();                                       // check for open gl errors it will output all errors

private:
   enum Geometry                                                     // List of geometry objects
   {
      TRIANGLE = 0,
      RECTANGLE = 1,
      QUBE = 2,
      CONE = 3
   };

   void handleInput();                                               // handle input
   bool init();                                                      // initalizes the programm   
   void terminate();                                                 // terminates the programm 
   bool createContext();                                             // creates GLFW window used as render context 
   
   static void framebufferSizeCallback(GLFWwindow* window,           // called if the window is resized
      int width, int height);
   static void keyPressedCallback(GLFWwindow* window, int key,
      int scancode, int action, int mods);                           // process keyboard input callback

   GLFWwindow* m_window = nullptr;                                   // the render context
   unsigned int m_geometry = TRIANGLE;
   const glm::vec3* m_rotAxis = new glm::vec3();

   const int m_width = 1280;                                         // window width
   const int m_height = 720;                                         // window height
   
   const glm::vec3 m_axisX = glm::vec3(1.0f, 0.0f, 0.0f);            // x axis
   const glm::vec3 m_axisY = glm::vec3(0.0f, 1.0f, 0.0f);            // y axis
   const glm::vec3 m_axisZ = glm::vec3(0.0f, 0.0f, 1.0f);            // y axis
};