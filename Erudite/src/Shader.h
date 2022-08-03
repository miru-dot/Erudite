#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Shader {
public:
   Shader(const std::string& vertexShaderFile, 
      const std::string& fragementShaderFile);                       // creates a new shader objects with the shader source and type
   ~Shader();
   void bind();                                                      // bind shader (program)
   void unbind();                                                    // unbind shader (program)
   void setU1i(const std::string& name, int value);                  // set 1 int uniform                   
   void setU1f(const std::string& name, float value);                // set 1 float uniform
   void setU4f(const std::string& name, float v0, float v1, 
      float v2, float v3);                                           // set 4 float uniform
   void setUMat4(const std::string& name, glm::mat4 matrix);         // set matrix 4 uniform
   void setUVec3(const std::string& name, glm::vec3 vector);         // set vector 3 uniform
   unsigned int getUniformLocation(const std::string& name);         // the location of a uniform in the shader

private:
   static void parseSource(std::string sourcefile, std::string* content);
   unsigned int compileShader(unsigned int shaderType,
      std::string& shaderSource);                                    // compiles a shader
   unsigned int createShader();                                      // compiles, linkes and builds shaders

   unsigned int m_id;                                                // shader id
   std::string* m_vertexShaderSource = new std::string();            // the vertex shader source
   std::string* m_fragmentShaderSource = new std::string();          // the fragement shader source
   std::unordered_map<std::string, int> m_unformLocations;           // holds the uniform locations
};