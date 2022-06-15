#pragma once
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"

class Renderer
{
public:
   static void rectangle(float width, float length);
   static void cube(float width, float length, float hight);
   static void cone(float hight, float radius, unsigned int slices);

   static void draw(const VertexArrayObject& vertexArray, const ElementBufferObject& elementBuffer);

   static void clear();
   static void polygonMode(unsigned int mode);
   static void switchPolygonMode();
};