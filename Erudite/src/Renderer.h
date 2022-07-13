#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexArrayObject.h"
#include "ElementBufferObject.h"
#include "GameObject.h"

class Renderer
{
public:
   static GameObject* triangle(float size, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
   static GameObject* rectangle(float width, float length, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
   static GameObject* cube(float width, float length, float hight, glm::vec4 top = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
      glm::vec4 bottom = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
   static GameObject* cone(float hight, float radius, unsigned int slices, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

   static void draw(const VertexArrayObject& vertexArray, const ElementBufferObject& elementBuffer);

   static void clear(unsigned int clear);
   static void polygonMode(unsigned int mode);
   static void switchPolygonMode();
   static void enable(unsigned int cap);
   static void blendFunction(unsigned int sfactor, unsigned int dfactor);
};