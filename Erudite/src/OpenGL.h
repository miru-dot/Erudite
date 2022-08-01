#pragma once

#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexArrayObject.h"
#include "ElementBufferObject.h"

class OpenGL
{
public:
   static void drawElements(unsigned int mode, 
      const VertexArrayObject& vertexArray, 
      const ElementBufferObject& elementBuffer);                     // Render primitives from array data
   static void clear(unsigned int mask);                             // Clear buffers to preset values
   static void polygonMode(unsigned int mode);                       // Controls the interpretation of polygons for rasterization
   static void switchPolygonMode();                                  // Switches polygon mode back and forth for GL_FILL and GL_LINE
   static void enable(unsigned int cap);                             // Enable or disable server-side GL capabilities
   static void blendFunction(unsigned int sfactor, 
      unsigned int dfactor);                                         // Specify pixel arithmetic
};