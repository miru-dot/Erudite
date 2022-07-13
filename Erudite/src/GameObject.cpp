#include "GameObject.h"

GameObject::GameObject(std::string name, MeshRenderer* mesh/*, Texture texture*/) :
   m_name(name), m_mesh(mesh)/*, m_texture(texture)*/
{
}

GameObject::~GameObject()
{
   if (m_mesh)
      delete m_mesh;
}

void GameObject::render()
{
   m_mesh->render();
}