#pragma once
#include "VertexBufferObject.h"
#include "VertexBufferLayout.h"
#include "ElementBufferObject.h"

class VertexArrayObject 
{
public:
   VertexArrayObject();
   ~VertexArrayObject();

   void addBuffer(const VertexBufferObject& vertexBuffer, VertexBufferLayout& layout);
   void draw(const VertexArrayObject& vertexArray, const ElementBufferObject& elementBuffer);

   void bind() const;
   void unbind() const;

private:
   unsigned int m_id;
};