#include "MeshRenderer.h"
#include "OpenGL.h"

MeshRenderer::MeshRenderer()
{
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::render()
{	
	// For debuging =)
	//assert(std::size(m_positions) == std::size(m_colors) && std::size(m_positions) == std::size(m_uv));
	
	std::vector<float> vertices;
	unsigned int count = std::size(m_positions);
	for (int i = 0; i < count; i++) 
	{
		vertices.push_back(m_positions[i].x);
		vertices.push_back(m_positions[i].y);
		vertices.push_back(m_positions[i].z);

		vertices.push_back(m_colors[i].r);
		vertices.push_back(m_colors[i].g);
		vertices.push_back(m_colors[i].b);
		vertices.push_back(m_colors[i].a);

		vertices.push_back(m_uv[i].s);
		vertices.push_back(m_uv[i].t);
	}

	VertexBufferLayout layout;
	layout.push<float>(3);	// position
	layout.push<float>(4);	// color
	layout.push<float>(2);	// texture coordinates

	VertexArrayObject vertexArray;
	VertexBufferObject vertexBuffer(&vertices[0], std::size(vertices) * sizeof(float));
	ElementBufferObject elementBuffer(&m_indices[0], std::size(m_indices));
	vertexArray.addBuffer(vertexBuffer, layout);
	OpenGL::draw(vertexArray, elementBuffer);
}

MeshRenderer* MeshRenderer::positions(std::vector<glm::vec3> positions)
{
	m_positions = positions;
	return this;
}

MeshRenderer* MeshRenderer::colors(std::vector<glm::vec4> colors)
{
	m_colors = colors;
	return this;
}

MeshRenderer* MeshRenderer::uv(std::vector<glm::vec2> uv)
{
	m_uv = uv;
	return this;
}

MeshRenderer* MeshRenderer::indices(std::vector<unsigned int> indices)
{
	m_indices = indices;
	return this;
}