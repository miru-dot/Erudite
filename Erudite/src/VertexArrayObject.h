#pragma once
#include "VertexBufferObject.h"
#include "VertexBufferLayout.h"

class VertexArrayObject 
{
public:
   VertexArrayObject();
   ~VertexArrayObject();

   void addBuffer(const VertexBufferObject& vertexBuffer, VertexBufferLayout& layout);

   void bind() const;
   void unbind() const;

private:
   unsigned int m_id;
};