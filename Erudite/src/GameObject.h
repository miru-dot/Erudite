#pragma once

#include "Shader.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "Transform.h"

class GameObject
{
public:
   GameObject(std::string name, MeshRenderer* mesh, Texture* texture);
   ~GameObject();

   void update();
   void render();

   Shader* m_shader;
   Transform* m_transform;

private:
   const unsigned int m_textureSlot = 0;
   std::string m_name;
   Texture* m_texture;
   MeshRenderer* m_mesh;
};