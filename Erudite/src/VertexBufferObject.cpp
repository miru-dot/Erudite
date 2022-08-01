#include "VertexBufferObject.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="data">buffer data</param>
/// <param name="size">buffer size</param>
VertexBufferObject::VertexBufferObject(const void* data, unsigned int size)
{
   glGenBuffers(1, &m_id);
   bind();
   glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

/// <summary>
/// Destructor
/// </summary>
VertexBufferObject::~VertexBufferObject()
{
   glDeleteBuffers(1, &m_id);
}

/// <summary>
/// Bind the vertex buffer
/// </summary>
void VertexBufferObject::bind() const
{
   glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

/// <summary>
/// Undbind the vertex buffer
/// </summary>
void VertexBufferObject::unbind() const
{
   glBindBuffer(GL_ARRAY_BUFFER, 0);
}