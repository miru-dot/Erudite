#include "VertexBufferLayout.h"

/// <summary>
/// Constructor
/// </summary>
VertexBufferLayout::VertexBufferLayout() : m_stride(0) 
{
}

/// <summary>
/// Destructor
/// </summary>
VertexBufferLayout::~VertexBufferLayout() 
{
}

/// <summary>
/// Adds float elements
/// </summary>
/// <param name="count">how many floats</param>
template<> void VertexBufferLayout::push<float>(unsigned int count)
{
   m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
   m_stride += count * VertexBufferElement::size(GL_FLOAT);
}

/// <summary>
/// Adds unsigned int elements
/// </summary>
/// <param name="count">how many unsigned ints</param>
template<> void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
   m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
   m_stride += count * VertexBufferElement::size(GL_UNSIGNED_INT);
}

/// <summary>
/// Adds unsigned char elements
/// </summary>
/// <param name="count">how many unsigned chars</param>
template<> void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
   m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
   m_stride += count * VertexBufferElement::size(GL_UNSIGNED_BYTE);
}

/// <summary>
/// Set vertex data flag
/// </summary>
/// <param name="data">flag</param>
void VertexBufferLayout::data(vertexData data)
{
   m_vertexData |= data;
}

/// <summary>
/// Check if a vertex data flag is set
/// </summary>
/// <param name="data">flag</param>
/// <returns>true if flag is set</returns>
bool VertexBufferLayout::has(vertexData data)
{
   return (data & m_vertexData) == (data);
}

/// <summary>
/// Check if there is no vertex data
/// </summary>
/// <returns></returns>
bool VertexBufferLayout::isEmpty()
{
   return m_vertexData == EMPTY;
}