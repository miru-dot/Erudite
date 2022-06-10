#pragma once
#include <glad/glad.h>

class ElementBufferObject
{
public:
   ElementBufferObject(const unsigned int* data, unsigned int count);
   ~ElementBufferObject();
   
   void bind() const;
   void unbind() const;

   inline unsigned int getCount() const { return m_count; };

private:
   unsigned int m_id;
   unsigned int m_count;
};