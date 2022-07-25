#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Transform
{
public:
   Transform();
   ~Transform();

   glm::mat4 trs();
   glm::mat4 rts();

   glm::mat4 rotate();
   glm::mat4 translate();
   glm::mat4 scale();

   glm::vec3* m_scale = new glm::vec3(1.0f, 1.0f, 1.0f);
   glm::vec3* m_position = new glm::vec3(0.0f, 0.0f, 0.0f);
   glm::vec3* m_rotation = new glm::vec3(0.0f, 0.0f, 0.0f);

private:
   const glm::vec3 m_axisX = glm::vec3(1.0f, 0.0f, 0.0f);            // x axis
   const glm::vec3 m_axisY = glm::vec3(0.0f, 1.0f, 0.0f);            // y axis
   const glm::vec3 m_axisZ = glm::vec3(0.0f, 0.0f, 1.0f);            // z axis
};