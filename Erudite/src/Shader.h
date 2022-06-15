#pragma once
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <iostream>

class Shader {
public:
   Shader(const std::string& vertexShaderFile, 
      const std::string& fragementShaderFile);                       // creates a new shader objects with the shader source and type
   ~Shader();
   void bind();                                                      // bind shader (program)
   void unbind();                                                    // unbind shader (program)
   void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
   unsigned int getUniformLocation(const std::string& name);

private:
   static void parseSource(std::string sourcefile, std::string* content);
   unsigned int compileShader(unsigned int shaderType,
      std::string& shaderSource);                                    // compiles a shader
   unsigned int createShader();                                      // compiles, linkes and builds shaders

   unsigned int m_id;                                                // shader id
   std::string* m_vertexShaderSource = new std::string();            // the vertex shader source
   std::string* m_fragmentShaderSource = new std::string();          // the fragement shader source
};