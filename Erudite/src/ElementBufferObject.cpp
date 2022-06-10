#include "ElementBufferObject.h"

ElementBufferObject::ElementBufferObject(const unsigned int* data, unsigned int count)
   : m_count(count)
{
   glGenBuffers(1, &m_id);
   bind();
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

ElementBufferObject::~ElementBufferObject()
{
   glDeleteBuffers(1, &m_id);
}

void ElementBufferObject::bind() const
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void ElementBufferObject::unbind() const
{
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}