#pragma once

#include "Transform.h"
#include "Camera.h"

struct LightData
{
   float m_ambientIntensity = 0.5f;
   float m_diffuseIntensity = 0.8f;
   float m_specularIntensity = 0.8f;
   float m_hardness = 64.0f;

   glm::vec3 m_color = glm::vec3(1.0f, 1.0f, 1.0f);
   glm::vec3 m_ambientColor = glm::vec3(0.75f, 0.75f, 1.0f);
   bool m_isDirectionalLight = false;
};

class Light 
{
public:
   ~Light();
   Light(Light& other) = delete;                                     // not clonable
   void operator=(const Light&) = delete;                            // not assignable

   static Light* instance();                                         // get the light instance
   static void destroy();                                            // destroy the light instance

   glm::mat4 lightData();                                            // transforms light data

   LightData* m_lightData;                                           // light data
   Transform* m_transform;                                           // light transform
   Camera* m_camera = Camera::instance();                            // camera
private:
   Light();                                                          // constructor
   static inline Light* m_instance;                                  // this instance
};