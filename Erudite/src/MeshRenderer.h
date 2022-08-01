#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexArrayObject.h"
#include "ElementBufferObject.h"
#include <vector>

class MeshRenderer
{
public:
   MeshRenderer();                                                   // constructor
   ~MeshRenderer();                                                  // destructor

   void determineBufferLayout();                                     // sets the VertexBufferLayout, positions (float * 3), colors (float * 4) ...
   void render();                                                    // creates the vertices and renders the geometry               

   MeshRenderer* positions(std::vector<glm::vec3> positions);        // set positions
   MeshRenderer* colors(std::vector<glm::vec4> colors);              // set colors
   MeshRenderer* uv(std::vector<glm::vec2> uv);                      // set uv
   MeshRenderer* normals(std::vector<glm::vec3> normals);            // set normals
   MeshRenderer* indices(std::vector<unsigned int> indices);         // set indices

   void primitive(unsigned int primitive);                           // set the primitive e.g GL_TRIANGLES, GL_LINES, GL_POINTS

private:
   VertexBufferLayout* m_layout = new VertexBufferLayout();          // vertex buffer layout

   std::vector<glm::vec3> m_positions;                               // positions
   std::vector<glm::vec4> m_colors;                                  // colors
   std::vector<glm::vec2> m_uv;                                      // uv
   std::vector<glm::vec3> m_normals;                                 // normals

   std::vector<unsigned int> m_indices;                              // indices
   unsigned int m_primitive = GL_TRIANGLES;                          // primitive
};