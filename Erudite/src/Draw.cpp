#include "Draw.h"

#include <corecrt_math_defines.h>

void Draw::rectangle(float width, float length)
{
	float x = length / 2.0f;
	float y = width / 2.0f;

	const unsigned int verticesSize = 8;
	float vertices[verticesSize] = {
		-x,  y,	// left top
		 x,  y,	// right top
		-x, -y,	// left bottom
		 x, -y	// right bottom
	};

	const unsigned int indicesSize = 6;
	unsigned int indices[indicesSize] = {
		0, 1, 2,	// triangle 1
		1, 3, 2  // triangle 2
	};

	VertexBufferLayout layout;
	layout.push<float>(2);

	VertexArrayObject vertexArray;
	VertexBufferObject vertexBuffer(vertices, verticesSize * sizeof(float));
	ElementBufferObject elementBuffer(indices, indicesSize);
	vertexArray.addBuffer(vertexBuffer, layout);	
	draw(vertexArray, elementBuffer);
}

void Draw::cube(float width, float length, float hight)
{
	float x = length / 2.0f;
	float y = hight / 2.0f;
	float z = width / 2.0f;

	const unsigned int verticesSize = 24;
	float vertices[verticesSize] = {
		-x,  y, -z,		// front left top
		 x,  y, -z,		// front right top
		-x, -y, -z,		// front left bottom
		 x, -y, -z,		// front right bottom

		-x,  y,  z,		// back left top
		 x,  y,  z,		// back right top
		-x, -y,  z,		// back left bottom
		 x, -y,  z		// back right bottom
	};

	const unsigned int indicesSize = 36;
	unsigned int indices[indicesSize] = {
		0, 1, 2,	 // front face triangle 1
		1, 3, 2,  // front face triangle 2

		5, 4, 7,  // back face triangle 1
		5, 6, 7,  // back face triangle 2

		4, 5, 0,  // top face triangle 1
		5, 1, 0,  // top face triangle 2

		2, 3, 7,  // bottom face triangle 1
		3, 6, 7,  // bottom face triangle 2

		4, 0, 6,  // left face triangle 1
		0, 2, 6,  // left face triangle 2

		1, 5, 3,  // right face triangle 1
		5, 7, 3   // right face triangle 2
	};

	VertexBufferLayout layout;
	layout.push<float>(3);

	VertexArrayObject vertexArray;
	VertexBufferObject vertexBuffer(vertices, verticesSize * sizeof(float));
	ElementBufferObject elementBuffer(indices, indicesSize);
	vertexArray.addBuffer(vertexBuffer, layout);
	draw(vertexArray, elementBuffer);
}

void Draw::cone(float hight, float radius, unsigned int slices)
{
	float radSlice = 360.0f / slices * M_PI / 180.0f;

	std::vector<float> vertices;
	float y = hight / 2.0f;

	// peak
	vertices.push_back(0.0f);
	vertices.push_back(y);
	vertices.push_back(0.0f);

	// slices
	for (int i = 0; i < slices; ++i) {
		float rad = radSlice * i;

		float x = radius * cos(rad);
		float z = radius * sin(rad);

		vertices.push_back(x);
		vertices.push_back(-y);
		vertices.push_back(z);
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
	layout.push<float>(3);

	VertexArrayObject vertexArray;
	VertexBufferObject vertexBuffer(&vertices[0], std::size(vertices) * sizeof(float));
	ElementBufferObject elementBuffer(&indices[0], std::size(indices));
	vertexArray.addBuffer(vertexBuffer, layout);
	draw(vertexArray, elementBuffer);
}

void Draw::draw(const VertexArrayObject& vertexArray, const ElementBufferObject& elementBuffer)
{
	vertexArray.bind();
	elementBuffer.bind();

	glDrawElements(GL_TRIANGLES, elementBuffer.getCount(), GL_UNSIGNED_INT, 0);
}

void Draw::clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}