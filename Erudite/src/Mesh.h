#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "VertexArrayObject.h"
#include "ElementBufferObject.h"
#include <vector>

class MeshRenderer
{
public:
   MeshRenderer();
   ~MeshRenderer();

   void render();

   void positions(std::vector<glm::vec3> positions);
   void colors(std::vector<glm::vec4> colors);
   void uv(std::vector<glm::vec2> uv);
   void indices(std::vector<unsigned int> indices);

private:
   VertexBufferLayout m_layout = VertexBufferLayout();

   std::vector<glm::vec3> m_positions;
   std::vector<glm::vec4> m_colors;
   std::vector<glm::vec2> m_uv;
   std::vector<unsigned int> m_indices;
};