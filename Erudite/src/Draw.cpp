#include "Draw.h"

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