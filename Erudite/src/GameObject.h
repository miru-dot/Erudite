#pragma once

#include "Shader.h"
#include "Texture.h"
#include "MeshRenderer.h"

class GameObject
{
public:
   GameObject(std::string name, MeshRenderer* mesh, Texture* texture);
   ~GameObject();

   void render();

   Shader* m_shader;

private:
   const unsigned int m_textureSlot = 0;
   std::string m_name;
   Texture* m_texture;
   MeshRenderer* m_mesh;
};