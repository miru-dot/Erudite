#pragma once

#include <vector>
#include <glad/glad.h>
#include <assert.h>

struct VertexBufferElement
{
   unsigned int type;                                                // element type GLfloat ...
   unsigned int count;                                               // element count GLfloat * count
   unsigned char normalized;                                         // normalized

   static unsigned int size(unsigned int type)                       // get the size in bytes
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
   VertexBufferLayout();                                             // constructor
   ~VertexBufferLayout();                                            // destructor

   enum vertexData {
      EMPTY = 0,
      POSITIONS = 1,
      COLORS = 2,
      UV = 4,
      NORMALS = 8,
   };                                                                // vertex data flags

   inline unsigned int getStride() const { return m_stride; }
   inline const std::vector<VertexBufferElement>  getElements() const 
   { return m_elements; }                                            // get vertex buffer elements

   template<typename T> void push(unsigned int count);               // push template
   template<> void push<float>(unsigned int count);                  // push float implementation
   template<> void push<unsigned int>(unsigned int count);           // push int implementation
   template<> void push<unsigned char>(unsigned int count);          // push char implementation

   void data(vertexData data);                                       // set vertex data flag
   bool has(vertexData data);                                        // check if a vertex data flag is set
   bool isEmpty();                                                   // check if there is no vertex data

private:
   std::vector<VertexBufferElement> m_elements;                      // holds the vertex elements
   unsigned int m_stride;                                            // holds the vertex stride
   unsigned int m_vertexData = EMPTY;                                // holds the vertex data flags
};