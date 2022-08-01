#pragma once

#include "GameObject.h"

static class Mesh {
public:
   static MeshRenderer* triangle(float size, 
      glm::vec4 color = glm::vec4(1.0f));                            // constructs a triangle
   static MeshRenderer* rectangle(float width, float length, 
      glm::vec4 color = glm::vec4(1.0f));                            // constructs a rectangle
   static MeshRenderer* cube(float width, float length, 
      float hight, glm::vec4 top = glm::vec4(1.0f), 
      glm::vec4 bottom = glm::vec4(1.0f));                           // constructs a cube
   static MeshRenderer* cone(float hight, float radius, 
      unsigned int slices, glm::vec4 color = glm::vec4(1.0f));       // constructs a cone
};