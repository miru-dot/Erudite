#include "GameObject.h"

GameObject::GameObject(std::string name, MeshRenderer* mesh, Texture* texture) :
   m_name(name), m_mesh(mesh), m_texture(texture)
{
   m_shader = new Shader("res/VertexShader.vert", "res/FragmentShader.frag");
   m_shader->bind();
   m_shader->setU1i("u_texture", m_textureSlot);
}

GameObject::~GameObject()
{
   if (m_mesh)
      delete m_mesh;
   if (m_texture)
      delete m_texture;
}

void GameObject::render()
{
   m_shader->bind();
   m_texture->bind(m_textureSlot);
   m_mesh->render();
}