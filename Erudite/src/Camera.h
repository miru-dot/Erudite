#pragma once

#include "Transform.h"

class Camera {
public:
   ~Camera();
   Camera(Camera& other) = delete;                                   // not clonable
   void operator=(const Camera&) = delete;                           // not assignable

   static Camera* instance();                                        // get the camera instance
   static void destroy();                                            // destroy the camera instance

   glm::mat4 projection();                                           // get projection matrix
   glm::mat4 view();                                                 // get view matrix

   Transform* m_transform;                                           // camera transform
   float m_fieldOfView;                                              // fov - field of view
   float m_nearPlane;                                                // near camera plane
   float m_farPlane;                                                 // far camera plane
   float m_ratio;                                                    // screen width / height ratio
private:
   Camera();                                                         // constructor
   static inline Camera* m_instance;                                 // this instance
};