#include "Camera.h"

/// <summary>
/// Constructor
/// </summary>
Camera::Camera() :
   m_transform(new Transform()), m_fieldOfView(115.0f), m_farPlane(100.0f), m_nearPlane(0.1f), m_ratio(1.777f)
{
   //m_transform->m_rotation->x = 30;
   m_transform->m_position->y = -1.0;
   m_transform->m_position->z = -2.0f;
}

/// <summary>
/// Destructor
/// </summary>
Camera::~Camera()
{
   if (m_transform)
      delete m_transform;
}

/// <summary>
/// Get the camera instance
/// </summary>
/// <returns>camera instance</returns>
Camera* Camera::instance()
{
   if (m_instance == nullptr)
      return m_instance = new Camera();

   return m_instance;
}

/// <summary>
/// Reset / destroy the camera instance
/// </summary>
void Camera::destroy()
{
   delete m_instance;
   m_instance = 0;
}

/// <summary>
/// Get projection matrix
/// </summary>
/// <returns>view matrix</returns>
glm::mat4 Camera::projection()
{
    return glm::perspective(m_fieldOfView, m_ratio, m_nearPlane, m_farPlane);
}

/// <summary>
/// Get view matrix
/// </summary>
/// <returns>view matrix</returns>
glm::mat4 Camera::view()
{
   return m_transform->rts();
}