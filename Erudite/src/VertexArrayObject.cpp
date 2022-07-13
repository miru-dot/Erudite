#include "VertexArrayObject.h"
#include "VertexBufferLayout.h"

VertexArrayObject::VertexArrayObject()
{
   glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject()
{
   glDeleteVertexArrays(1, &m_id);
}

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

void VertexArrayObject::draw(const VertexArrayObject& vertexArray, const ElementBufferObject& elementBuffer)
{
   vertexArray.bind();
   elementBuffer.bind();

   glDrawElements(GL_TRIANGLES, elementBuffer.getCount(), GL_UNSIGNED_INT, 0);
}

void VertexArrayObject::bind() const
{
   glBindVertexArray(m_id);
}

void VertexArrayObject::unbind() const
{
   glBindVertexArray(0);
}