#pragma once
#include <glad/glad.h>

class ElementBufferObject
{
public:
   ElementBufferObject(const unsigned int* data, 
      unsigned int count);                                           // constuctor
   ~ElementBufferObject();                                           // destructor
   
   void bind() const;                                                // bind element buffer
   void unbind() const;                                              // undbind element buffer, bind the default

   inline unsigned int getCount() const { return m_count; };         // get the count

private:
   unsigned int m_id;                                                // element buffer opengl id
   unsigned int m_count;                                             // holds the count of the indices
};