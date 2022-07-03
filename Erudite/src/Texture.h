#pragma once
#include <string>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

private:
	unsigned int m_id;
	unsigned char* m_buffer;
	int m_width, m_height, m_bpp;
	std::string m_filePath;
};