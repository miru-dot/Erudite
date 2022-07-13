#include "Renderer.h"

#include <corecrt_math_defines.h>
#include "App.h"

GameObject* Renderer::triangle(float size, glm::vec4 color)
{
	float p = size / 2.0f;

	std::vector<glm::vec3> positions = {
		glm::vec3(0.0f,  p, 0.0f),
		glm::vec3(	 p, -p, 0.0f),
		glm::vec3(	-p, -p, 0.0f)
	};

	std::vector<glm::vec4> colors = {
		glm::vec4(color.r, color.g, color.b, color.a),
		glm::vec4(color.r, color.g, color.b, color.a),
		glm::vec4(color.r, color.g, color.b, color.a)
	};

	std::vector<glm::vec2> uv = {
		glm::vec2(0.5f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f)
	};

	std::vector<unsigned int> indices = {
		0, 1, 2
	};

	MeshRenderer* mesh = new MeshRenderer();
	mesh->positions(positions)->colors(colors)->uv(uv)->indices(indices);

	return new GameObject("triangle", mesh);
}

GameObject* Renderer::rectangle(float width, float length, glm::vec4 color)
{
	float x = length / 2.0f;
	float y = width / 2.0f;

	std::vector<glm::vec3> positions = {
		glm::vec3(-x,  y, 0.0f),	// left top
		glm::vec3( x,  y, 0.0f),	// right top
		glm::vec3(-x, -y, 0.0f),	// left bottom
		glm::vec3( x, -y, 0.0f)		// right bottom
	};

	std::vector<glm::vec4> colors = {
		glm::vec4(color.r, color.g, color.b, color.a),
		glm::vec4(color.r, color.g, color.b, color.a),
		glm::vec4(color.r, color.g, color.b, color.a),
		glm::vec4(color.r, color.g, color.b, color.a)
	};

	std::vector<glm::vec2> uv = {
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f)
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		1, 3, 2
	};	

	MeshRenderer* mesh = new MeshRenderer();
	mesh->positions(positions)->colors(colors)->uv(uv)->indices(indices);

	return new GameObject("rectangle", mesh);
}

GameObject* Renderer::cube(float width, float length, float hight, glm::vec4 top, glm::vec4 bottom)
{
	float x = length / 2.0f;
	float y = hight / 2.0f;
	float z = width / 2.0f;

	std::vector<glm::vec3> positions = {
		glm::vec3(-x,  y, -z),	// front left top
		glm::vec3( x,  y, -z),	// front right top
		glm::vec3(-x, -y, -z),	// front left bottom
		glm::vec3( x, -y, -z),	// front right bottom

		glm::vec3(-x,  y,  z),	// back left top
		glm::vec3( x,  y,  z),	// back right top
		glm::vec3(-x, -y,  z),	// back left bottom
		glm::vec3( x, -y,  z)	// back right bottom
	};

	std::vector<glm::vec4> colors = {
		glm::vec4(top.r, top.g, top.b, top.a),
		glm::vec4(top.r, top.g, top.b, top.a),
		glm::vec4(bottom.r, bottom.g, bottom.b, bottom.a),
		glm::vec4(bottom.r, bottom.g, bottom.b, bottom.a),

		glm::vec4(top.r, top.g, top.b, top.a),
		glm::vec4(top.r, top.g, top.b, top.a),
		glm::vec4(bottom.r, bottom.g, bottom.b, bottom.a),
		glm::vec4(bottom.r, bottom.g, bottom.b, bottom.a)
	};

	std::vector<glm::vec2> uv = {
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),

		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f)
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,	 // front face triangle 1
		1, 3, 2,  // front face triangle 2

		5, 4, 7,  // back face triangle 1
		4, 6, 7,  // back face triangle 2

		4, 5, 0,  // top face triangle 1
		5, 1, 0,  // top face triangle 2

		2, 3, 6,  // bottom face triangle 1
		3, 7, 6,  // bottom face triangle 2

		4, 0, 6,  // left face triangle 1
		0, 2, 6,  // left face triangle 2

		1, 5, 3,  // right face triangle 1
		5, 7, 3   // right face triangle 2 
	};

	MeshRenderer* mesh = new MeshRenderer();
	mesh->positions(positions)->colors(colors)->uv(uv)->indices(indices);

	return new GameObject("cube", mesh);
}

GameObject* Renderer::cone(float hight, float radius, unsigned int slices, glm::vec4 color)
{
	float radSlice = 360.0f / slices * M_PI / 180.0f;

	std::vector<float> vertices;
	float y = hight / 2.0f;

	// peak
	vertices.push_back(0.0f);
	vertices.push_back(y);
	vertices.push_back(0.0f);

	vertices.push_back(color.r);
	vertices.push_back(color.g);
	vertices.push_back(color.b);
	vertices.push_back(color.a);

	// slices
	for (int i = 0; i < slices; ++i) {
		float rad = radSlice * i;

		float x = radius * cos(rad);
		float z = radius * sin(rad);

		vertices.push_back(x);
		vertices.push_back(-y);
		vertices.push_back(z);

		vertices.push_back(color.r);
		vertices.push_back(color.g);
		vertices.push_back(color.b);
		vertices.push_back(color.a);
	}

	std::vector<unsigned int> indices;
	unsigned int indicesIndex = 1;
	for (int i = 0; i < slices; i++)
	{
		indices.push_back(0);	// vertex 0 is the peak of the cone
		unsigned int tmp = indicesIndex + 1;
		indices.push_back(tmp > slices ? 1 : tmp);
		indices.push_back(indicesIndex);
		indicesIndex++;
	}

	VertexBufferLayout layout;
	layout.push<float>(3);  // position
	layout.push<float>(4);	// color

	VertexArrayObject vertexArray;
	VertexBufferObject vertexBuffer(&vertices[0], std::size(vertices) * sizeof(float));
	ElementBufferObject elementBuffer(&indices[0], std::size(indices));
	vertexArray.addBuffer(vertexBuffer, layout);
	draw(vertexArray, elementBuffer);

	return nullptr;
}

void Renderer::draw(const VertexArrayObject& vertexArray, const ElementBufferObject& elementBuffer)
{
	vertexArray.bind();
	elementBuffer.bind();

	glDrawElements(GL_TRIANGLES, elementBuffer.getCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::clear(unsigned int clear)
{
	glClear(clear);
}

/// <summary>
/// Controls the interpretation of polygons for rasterization
/// </summary>
/// <param name="mode">GL_POINT, GL_LINE or GL_FILL</param>
void Renderer::polygonMode(unsigned int mode)
{
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void Renderer::switchPolygonMode()
{
	int mode;
	glGetIntegerv(GL_POLYGON_MODE, &mode);
	polygonMode(mode == GL_FILL ? GL_LINE : GL_FILL);
}

void Renderer::enable(unsigned int cap)
{
	glEnable(cap);
}

void Renderer::blendFunction(unsigned int sfactor, unsigned int dfactor)
{
	glBlendFunc(sfactor, dfactor);
}