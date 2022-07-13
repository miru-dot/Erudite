#pragma once

#include "Texture.h"
#include "Mesh.h"

class GameObject
{
public:
   GameObject(std::string name = std::string("object"),
      MeshRenderer* mesh = new MeshRenderer()/*,
      Texture texture = Texture("res/textures/default.png")*/);
   ~GameObject();


   void render();

private:
   std::string m_name;
  // Texture m_texture;
   MeshRenderer* m_mesh;
};