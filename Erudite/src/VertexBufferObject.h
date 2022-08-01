#pragma once
#include <glad/glad.h>

class VertexBufferObject
{
public:
   VertexBufferObject(const void* data, unsigned int size);          // constructor
   ~VertexBufferObject();                                            // destructor

   void bind() const;                                                // bind the vertex buffer
   void unbind() const;                                              // undbind the vertex buffer

private:
   unsigned int m_id;                                                // vertex buffer opengl id
};