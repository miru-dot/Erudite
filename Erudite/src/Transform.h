#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Transform
{
public:
   Transform();                                                      // constructor
   ~Transform();                                                     // destructor

   glm::mat4 trs();                                                  // get translation * rotation * scale matrix
   glm::mat4 rts();                                                  // get rotation * translation * scale matrix

   glm::mat4 rotate();                                               // get rotation matrix
   glm::mat4 translate();                                            // get translation matrix
   glm::mat4 scale();                                                // get scale matrix

   glm::vec3* m_scale = new glm::vec3(1.0f);                         // scale
   glm::vec3* m_position = new glm::vec3(0.0f);                      // position
   glm::vec3* m_rotation = new glm::vec3(0.0f);                      // rotation

private:
   const glm::vec3 m_axisX = glm::vec3(1.0f, 0.0f, 0.0f);            // x axis
   const glm::vec3 m_axisY = glm::vec3(0.0f, 1.0f, 0.0f);            // y axis
   const glm::vec3 m_axisZ = glm::vec3(0.0f, 0.0f, 1.0f);            // z axis
};