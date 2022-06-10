#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(const void* data, unsigned int size)
{
   glGenBuffers(1, &m_id);
   bind();
   glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
   glDeleteBuffers(1, &m_id);
}

void VertexBufferObject::bind() const
{
   glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBufferObject::unbind() const
{
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}