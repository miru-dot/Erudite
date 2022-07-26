#include "Mesh.h"
#include <corecrt_math_defines.h>

GameObject* Mesh::triangle(float size, glm::vec4 color, Texture* texture)
{
	float p = size / 2.0f;

	std::vector<glm::vec3> positions = {
		glm::vec3(0.0f,  p, 0.0f),
		glm::vec3(p, -p, 0.0f),
		glm::vec3(-p, -p, 0.0f)
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

	return new GameObject("triangle", mesh, texture);
}

GameObject* Mesh::rectangle(float width, float length, glm::vec4 color, Texture* texture)
{
	float x = length / 2.0f;
	float y = width / 2.0f;

	std::vector<glm::vec3> positions = {
		glm::vec3(-x,  y, 0.0f),	// left top
		glm::vec3(x,  y, 0.0f),	// right top
		glm::vec3(-x, -y, 0.0f),	// left bottom
		glm::vec3(x, -y, 0.0f)		// right bottom
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

	return new GameObject("rectangle", mesh, texture);
}

GameObject* Mesh::cube(float width, float length, float hight, glm::vec4 top, glm::vec4 bottom, Texture* texture)
{
	float x = length / 2.0f;
	float y = hight / 2.0f;
	float z = width / 2.0f;

	std::vector<glm::vec3> positions = {
		glm::vec3(-x,  y, -z),	// front left top
		glm::vec3(x,  y, -z),	// front right top
		glm::vec3(-x, -y, -z),	// front left bottom
		glm::vec3(x, -y, -z),	// front right bottom

		glm::vec3(-x,  y,  z),	// back left top
		glm::vec3(x,  y,  z),	// back right top
		glm::vec3(-x, -y,  z),	// back left bottom
		glm::vec3(x, -y,  z),	// back right bottom
	};

	std::vector<glm::vec4> colors = {
		glm::vec4(top.r, top.g, top.b, top.a),
		glm::vec4(top.r, top.g, top.b, top.a),
		glm::vec4(bottom.r, bottom.g, bottom.b, bottom.a),
		glm::vec4(bottom.r, bottom.g, bottom.b, bottom.a),

		glm::vec4(top.r, top.g, top.b, top.a),
		glm::vec4(top.r, top.g, top.b, top.a),
		glm::vec4(bottom.r, bottom.g, bottom.b, bottom.a),
		glm::vec4(bottom.r, bottom.g, bottom.b, bottom.a),
	};

	std::vector<glm::vec2> uv = {
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),

		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
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

	return new GameObject("cube", mesh, texture);
}

GameObject* Mesh::cone(float hight, float radius, unsigned int slices, glm::vec4 color)
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec4> colors;
	std::vector<glm::vec2> uv;
	std::vector<unsigned int> indices;
	
	float radSlice = 360.0f / slices * M_PI / 180.0f;

	float y = hight / 2.0f;

	// peak
	positions.push_back(glm::vec3(0.0f, y, 0.0f));
	colors.push_back(color);
	uv.push_back(glm::vec2(0.0f, 0.0f));

	// slices
	for (int i = 0; i < slices; ++i) 
	{
		float rad = radSlice * i;

		float x = radius * cos(rad);
		float z = radius * sin(rad);

		positions.push_back(glm::vec3(x, -y, z));
		colors.push_back(color);
		uv.push_back(glm::vec2(0.0f, 0.0f));
	}

	unsigned int indicesIndex = 1;
	for (int i = 0; i < slices; i++)
	{
		indices.push_back(0);	// vertex 0 is the peak of the cone
		unsigned int tmp = indicesIndex + 1;
		indices.push_back(tmp > slices ? 1 : tmp);
		indices.push_back(indicesIndex);
		indicesIndex++;
	}

	MeshRenderer* mesh = new MeshRenderer();
	mesh->positions(positions)->colors(colors)->uv(uv)->indices(indices);

	return new GameObject("cone", mesh, new Texture("res/textures/default.png"));
}