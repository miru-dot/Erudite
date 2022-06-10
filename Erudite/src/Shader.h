#pragma once
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <iostream>

class Shader {
public:
   Shader(std::string shaderSource, unsigned int shaderType);        // creates a new shader objects with the shader source and type
   ~Shader();
   unsigned int compileShader();                                     // compiles a shader

private:
   std::string* m_shaderSource;                                      // the shader source as string
   unsigned int m_shaderType;                                        // the shader type
};