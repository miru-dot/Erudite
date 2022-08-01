#pragma once
#include "VertexBufferObject.h"
#include "VertexBufferLayout.h"
#include "ElementBufferObject.h"

class VertexArrayObject 
{
public:
   VertexArrayObject();                                              // constructor
   ~VertexArrayObject();                                             // destructor

   void addBuffer(const VertexBufferObject& vertexBuffer, 
      VertexBufferLayout& layout);                                   // add a vertex buffer to the vao

   void bind() const;                                                // bind the VAO
   void unbind() const;                                              // unbind the VAO

private:
   unsigned int m_id;                                                // VAO opengl id
};