#include "Texture.h"
#include "stb_image/stb_image.h"
#include <glad/glad.h>

/// <summary>
/// Constructor - sets up a texture
/// </summary>
/// <param name="path"></param>
Texture::Texture(const std::string& path)
   : m_id(0), m_filePath(path), m_buffer(nullptr),
   m_width(0), m_height(0), m_bpp(0)
{
   stbi_set_flip_vertically_on_load(true);
   m_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

   glGenTextures(1, &m_id);
   glBindTexture(GL_TEXTURE_2D, m_id);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //GL_CLAMP_TO_EDGE, GL_REPEAT
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_buffer);
   glBindTexture(GL_TEXTURE_2D, 0);

   if (m_buffer)
      stbi_image_free(m_buffer);
}

/// <summary>
/// Destructor
/// </summary>
Texture::~Texture()
{
   glDeleteTextures(1, &m_id);
}

/// <summary>
/// Bind the texture
/// </summary>
/// <param name="slot"></param>
void Texture::bind(unsigned int slot /*= 0*/) const
{
   glActiveTexture(GL_TEXTURE0 + slot);
   glBindTexture(GL_TEXTURE_2D, m_id);
}

/// <summary>
/// Unbind the texture
/// </summary>
void Texture::unbind() const
{
   glBindTexture(GL_TEXTURE_2D, 0);
}