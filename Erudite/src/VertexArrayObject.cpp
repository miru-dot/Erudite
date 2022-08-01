#include "VertexArrayObject.h"
#include "VertexBufferLayout.h"

/// <summary>
/// Constructor
/// </summary>
VertexArrayObject::VertexArrayObject()
{
   glGenVertexArrays(1, &m_id);
}

/// <summary>
/// Destructor
/// </summary>
VertexArrayObject::~VertexArrayObject()
{
   glDeleteVertexArrays(1, &m_id);
}

/// <summary>
/// Add a vertex buffer to the vao
/// </summary>
/// <param name="vertexBuffer">buffer to add</param>
/// <param name="layout">buffer layout</param>
void VertexArrayObject::addBuffer(const VertexBufferObject& vertexBuffer, VertexBufferLayout& layout)
{
   bind();
   vertexBuffer.bind();
   const auto& elements = layout.getElements();
   unsigned int offset = 0;
   for (unsigned int idx = 0; idx < elements.size(); idx++)
   {
      const auto& element = elements[idx];
      glEnableVertexAttribArray(idx);
      glVertexAttribPointer(idx, element.count, element.type, element.normalized, 
         layout.getStride(), (const void*)offset);
      offset += element.count * VertexBufferElement::size(element.type);
   }
}

/// <summary>
/// Bind the VAO
/// </summary>
void VertexArrayObject::bind() const
{
   glBindVertexArray(m_id);
}

/// <summary>
/// Unbind the VAO
/// </summary>
void VertexArrayObject::unbind() const
{
   glBindVertexArray(0);
}