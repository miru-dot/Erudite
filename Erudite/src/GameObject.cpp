#include "GameObject.h"

GameObject::GameObject(std::string name, MeshRenderer* mesh, Texture* texture) :
   m_name(name), m_mesh(mesh), m_texture(texture), m_transform(new Transform())
{
   m_shader = new Shader("res/VertexShader.vert", "res/FragmentShader.frag");
   m_shader->bind();
   m_shader->setU1i("u_texture", m_textureSlot);
   
   // sets the buffer layout internally, positions -> colors -> uv ... (do it only once!)
   m_mesh->determineBufferLayout();
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

void GameObject::transform()
{
   m_shader->bind();

   m_shader->setUMat4("u_model",model());
   m_shader->setUMat4("u_view", m_camera->view());
   m_shader->setUMat4("u_projection", m_camera->projection());
}

glm::mat4 GameObject::model()
{
   return m_transform->trs();
}