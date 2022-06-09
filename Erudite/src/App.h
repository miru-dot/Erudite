#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

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
   void processInput();                                              // process keyboard input
   unsigned int compileShader(unsigned int shaderType, 
      const string& shaderSource);                                   // compiles a shader
   unsigned int createShader();                                      // compiles, linkes and builds shaders

   static void framebufferSizeCallback(GLFWwindow* window,           // called if the window is resized
      int width, int height);
   static void checkGLError();                                       // check for open gl errors it will output all errors

   GLFWwindow* m_window = nullptr;                                   // the render context
   const int m_width = 800;                                          // window width
   const int m_length = 800;                                         // window length

   const string VertexShader = 
      "#version 410 core\n"
      "\n"
      "layout (location = 0) in vec4 position;\n"
      "\n"
      "void main()\n"
      "{\n"
      "  gl_Position = position;\n"
      "}\n";

   const string FragmentShader =
      "#version 410 core\n"
      "\n"
      "layout (location = 0) out vec4 color;\n"
      "\n"
      "void main()\n"
      "{\n"
      " color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
      "}\n";
};