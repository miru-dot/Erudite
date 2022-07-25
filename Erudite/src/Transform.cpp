#include "Transform.h"

Transform::Transform()
{
}

Transform::~Transform()
{
   if (m_scale)
      delete m_scale;
   if (m_position)
      delete m_position;
   if(m_rotation)
      delete m_rotation;
}

glm::mat4 Transform::trs()
{
   return translate() * rotate() * scale();
}

glm::mat4 Transform::rts()
{
   return rotate() * translate() * scale();
}

glm::mat4 Transform::rotate()
{
   glm::vec3 rot = *m_rotation;
   glm::mat4 xrot = glm::rotate(glm::mat4(1.0), glm::radians(rot.x), m_axisX);
   glm::mat4 yrot = glm::rotate(glm::mat4(1.0), glm::radians(rot.y), m_axisY);
   glm::mat4 zrot = glm::rotate(glm::mat4(1.0), glm::radians(rot.z), m_axisZ);

   return xrot * yrot * zrot;
}

glm::mat4 Transform::translate()
{
   return glm::translate(glm::mat4(1.0), *m_position);
}

glm::mat4 Transform::scale()
{
   return glm::scale(glm::mat4(1.0), *m_scale);
}