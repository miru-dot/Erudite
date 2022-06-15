#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

class App 
{
public:
   App();                                                            // consturctor
   ~App();                                                           // destructor
   void run();                                                       // programm loop

private:
   bool init();                                                      // initalizes the programm   
   void terminate();                                                 // terminates the programm 
   bool createContext();                                             // creates GLFW window used as render context 
   unsigned int createShader();                                      // compiles, linkes and builds shaders

   static void framebufferSizeCallback(GLFWwindow* window,           // called if the window is resized
      int width, int height);
   static void keyPressedCallback(GLFWwindow* window, int key,
      int scancode, int action, int mods);                           // process keyboard input callback
   static void checkGLError();                                       // check for open gl errors it will output all errors

   GLFWwindow* m_window = nullptr;                                   // the render context
   const int m_width = 800;                                          // window width
   const int m_length = 800;                                         // window length
};