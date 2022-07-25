#include "Camera.h"

Camera::Camera() :
   m_transform(new Transform()), m_fieldOfView(90.0f), m_farPlane(100.0f), m_nearPlane(0.1f), m_ratio(1.777f)
{
}

Camera::~Camera()
{
   if (m_transform)
      delete m_transform;
}

Camera* Camera::instance()
{
   if (m_instance == nullptr)
      return m_instance = new Camera();

   return m_instance;
}

void Camera::destroy()
{
   delete m_instance;
   m_instance = 0;
}

glm::mat4 Camera::projection()
{
    return glm::perspective(m_fieldOfView, m_ratio, m_nearPlane, m_farPlane);
}

glm::mat4 Camera::view()
{
   return m_transform->rts();
}