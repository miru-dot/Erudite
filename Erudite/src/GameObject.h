#pragma once

#include "Shader.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"

class GameObject
{
public:
   GameObject(std::string name, MeshRenderer* mesh, Texture* texture);
   ~GameObject();

   void render();
   void transform();

   glm::mat4 model();

   Shader* m_shader;
   Transform* m_transform;

private:
   const unsigned int m_textureSlot = 0;
   std::string m_name;
   Texture* m_texture;
   MeshRenderer* m_mesh;
   Camera* m_camera = Camera::instance();
};