#pragma once
#include <string>

class Texture
{
public:
	Texture(const std::string& path);											// constructor																								
	~Texture();																			// destructor

	void bind(unsigned int slot = 0) const;									// bind the texture
	void unbind() const;																// unbind the texture

private:
	unsigned int m_id;																// this textures opengl id
	unsigned char* m_buffer;														// texture byte buffer
	int m_width, m_height, m_bpp;													// texture size
	std::string m_filePath;															// texture path
};