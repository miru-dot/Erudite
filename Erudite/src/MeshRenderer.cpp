#include "MeshRenderer.h"
#include "OpenGL.h"

/// <summary>
/// Constructor
/// </summary>
MeshRenderer::MeshRenderer()
{
}

/// <summary>
/// Destructor
/// </summary>
MeshRenderer::~MeshRenderer()
{
	if (m_layout)
		delete m_layout;
}

/// <summary>
/// Sets the VertexBufferLayout, positions (float * 3), colors (float * 4) ...
/// </summary>
void MeshRenderer::determineBufferLayout()
{
	if (m_layout->has(VertexBufferLayout::POSITIONS))
		m_layout->push<float>(3);
	if (m_layout->has(VertexBufferLayout::COLORS))
		m_layout->push<float>(4);
	if (m_layout->has(VertexBufferLayout::UV))
		m_layout->push<float>(2);
	if (m_layout->has(VertexBufferLayout::NORMALS))
		m_layout->push<float>(3);
}

/// <summary>
/// Creates the vertices and renders the geometry  
/// </summary>
void MeshRenderer::render()
{	
	if (m_layout->isEmpty()) 
	{
		assert(false);
		return;
	}

	std::vector<float> vertices;
	unsigned int count = std::size(m_positions);
	for (int i = 0; i < count; i++)
	{
		if (m_layout->has(VertexBufferLayout::POSITIONS))
		{
			vertices.push_back(m_positions[i].x);
			vertices.push_back(m_positions[i].y);
			vertices.push_back(m_positions[i].z);
		}

		if (m_layout->has(VertexBufferLayout::COLORS))
		{
			vertices.push_back(m_colors[i].r);
			vertices.push_back(m_colors[i].g);
			vertices.push_back(m_colors[i].b);
			vertices.push_back(m_colors[i].a);
		}
		
		if (m_layout->has(VertexBufferLayout::UV))
		{
			vertices.push_back(m_uv[i].s);
			vertices.push_back(m_uv[i].t);
		}

		if(m_layout->has(VertexBufferLayout::NORMALS))
		{
			vertices.push_back(m_normals[i].x);
			vertices.push_back(m_normals[i].y);
			vertices.push_back(m_normals[i].z);
		}
	}

	VertexArrayObject vertexArray;
	VertexBufferObject vertexBuffer(&vertices[0], vertices.size() * sizeof(float));
	ElementBufferObject elementBuffer(&m_indices[0], m_indices.size());
	vertexArray.addBuffer(vertexBuffer, *m_layout);
	OpenGL::drawElements(m_primitive, vertexArray, elementBuffer);
}

/// <summary>
/// Set positions
/// </summary>
/// <param name="positions">positions</param>
/// <returns>this</returns>
MeshRenderer* MeshRenderer::positions(std::vector<glm::vec3> positions)
{
	m_layout->data(VertexBufferLayout::POSITIONS);
	m_positions = positions;
	return this;
}

/// <summary>
/// Set colors
/// </summary>
/// <param name="colors">colors</param>
/// <returns>this</returns>
MeshRenderer* MeshRenderer::colors(std::vector<glm::vec4> colors)
{
	m_layout->data(VertexBufferLayout::COLORS);
	m_colors = colors;
	return this;
}

/// <summary>
/// Set uv
/// </summary>
/// <param name="uv">uv</param>
/// <returns>this</returns>
MeshRenderer* MeshRenderer::uv(std::vector<glm::vec2> uv)
{
	m_layout->data(VertexBufferLayout::UV);
	m_uv = uv;
	return this;
}

/// <summary>
/// Set normals
/// </summary>
/// <param name="normals">normals</param>
/// <returns>this</returns>
MeshRenderer* MeshRenderer::normals(std::vector<glm::vec3> normals)
{
	m_layout->data(VertexBufferLayout::NORMALS);
	m_normals = normals;
	return this;
}

/// <summary>
/// Set indices
/// </summary>
/// <param name="indices">indices</param>
/// <returns>this</returns>
MeshRenderer* MeshRenderer::indices(std::vector<unsigned int> indices)
{
	m_indices = indices;
	return this;
}

/// <summary>
/// Set primitive
/// </summary>
/// <param name="primitive">primitive</param>
void MeshRenderer::primitive(unsigned int primitive)
{
	m_primitive = primitive;
}