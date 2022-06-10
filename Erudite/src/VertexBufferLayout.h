#pragma once

#include <vector>
#include <glad/glad.h>
#include <assert.h>

struct VertexBufferElement
{
   unsigned int type;
   unsigned int count;
   unsigned char normalized;

   static unsigned int size(unsigned int type)
   {
      switch (type)
      {
         case GL_FLOAT: return sizeof(GLfloat);
         case GL_UNSIGNED_INT: return sizeof(GLuint);
         case GL_UNSIGNED_BYTE: return sizeof(GLbyte);
      }
      assert(false);
      return 0;
   }
};

class VertexBufferLayout
{
public:
   VertexBufferLayout();
   ~VertexBufferLayout();

   inline unsigned int getStride() const { return m_stride; }
   inline const std::vector<VertexBufferElement>  getElements() const { return m_elements; }

   template<typename T> void push(unsigned int count);
   template<> void push<float>(unsigned int count);
   template<> void push<unsigned int>(unsigned int count);
   template<> void push<unsigned char>(unsigned int count);

private:
   std::vector<VertexBufferElement> m_elements;
   unsigned int m_stride;
};