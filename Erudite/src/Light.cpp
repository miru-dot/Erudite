#include "Light.h"

/// <summary>
/// Constructor
/// </summary>
Light::Light() :
   m_transform(new Transform()), m_lightData(new LightData())
{
   m_transform->m_position->y = 5.0;
}

/// <summary>
/// Destructor
/// </summary>
Light::~Light()
{
   if (m_transform)
      delete m_transform;
}

/// <summary>
/// Get light instance
/// </summary>
/// <returns></returns>
Light* Light::instance()
{
   if (m_instance == nullptr)
      return m_instance = new Light();

   return m_instance;
}

/// <summary>
/// Reset / destroy light instance
/// </summary>
void Light::destroy()
{
   delete m_instance;
   m_instance = 0;
}

glm::mat4 Light::lightData()
{
   LightData data = *m_lightData;

   // columns
   glm::vec4 first   (*m_transform->m_position,             data.m_ambientIntensity);
   glm::vec4 second  (data.m_ambientColor,                  data.m_diffuseIntensity);
   glm::vec4 third   (data.m_color,                         data.m_specularIntensity);
   glm::vec4 fourth  (*m_camera->m_transform->m_position,   data.m_hardness);
   
   return glm::mat4(first, second, third, fourth);
}