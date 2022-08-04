#pragma once

#include "Shader.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"

class GameObject
{
public:
   GameObject(std::string name, MeshRenderer* mesh, 
      Texture* texture = new Texture("res/textures/default.png"));   // consturctor
   ~GameObject();                                                    // destructor

   void render();                                                    // renders the gameobject on the screen
   void transform();                                                 // sets the transformation matrix

   glm::mat4 model();                                                // get the this model transformation matrix

   Shader* m_shader;                                                 // shader instance
   Transform* m_transform;                                           // transform of this gameobject
   std::string m_name;                                               // name of this gameobject
   bool m_active;                                                    // active
private:
   const unsigned int m_textureSlot = 0;                             // used texture slot
   Texture* m_texture;                                               // texture of this gameobject
   MeshRenderer* m_mesh;                                             // mesh of this gameobject
   Camera* m_camera = Camera::instance();                            // camera instance
   Light* m_light = Light::instance();
};