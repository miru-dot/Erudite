#pragma once

#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexArrayObject.h"
#include "ElementBufferObject.h"

class OpenGL
{
public:
   static void draw(const VertexArrayObject& vertexArray, const ElementBufferObject& elementBuffer);
   static void clear(unsigned int clear);
   static void polygonMode(unsigned int mode);
   static void switchPolygonMode();
   static void enable(unsigned int cap);
   static void blendFunction(unsigned int sfactor, unsigned int dfactor);
};