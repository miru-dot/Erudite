#include "Mesh.h"
#include <corecrt_math_defines.h>

/// <summary>
/// Constructs a triangle
/// </summary>
/// <param name="size">triangle size</param>
/// <param name="color">triangle color</param>
/// <returns>triangle mesh</returns>
MeshRenderer* Mesh::triangle(float size, glm::vec4 color)
{
	float p = size / 2.0f;

	std::vector<glm::vec3> positions = {
		glm::vec3(0.0f,  p, 0.0f),
		glm::vec3(   p, -p, 0.0f),
		glm::vec3(  -p, -p, 0.0f)
	};

	std::vector<glm::vec4> colors(3, glm::vec4(color));

	std::vector<glm::vec2> uv = {
		glm::vec2(0.5f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f)
	};

	std::vector<unsigned int> indices = {
		0, 1, 2
	};

	MeshRenderer* mesh = new MeshRenderer();
	return mesh->positions(positions)->colors(colors)->uv(uv)->indices(indices);
}

/// <summary>
/// Constructs a rectangle
/// </summary>
/// <param name="width">rectangle width</param>
/// <param name="length">rectangle length</param>
/// <param name="color">rectangle color</param>
/// <returns>rectangle mesh</returns>
MeshRenderer* Mesh::rectangle(float width, float length, glm::vec4 color)
{
	float x = length / 2.0f;
	float y = width / 2.0f;

	std::vector<glm::vec3> positions = {
		glm::vec3(-x,  y, 0.0f),	// left top
		glm::vec3( x,  y, 0.0f),	// right top
		glm::vec3(-x, -y, 0.0f),	// left bottom
		glm::vec3( x, -y, 0.0f)		// right bottom
	};

	std::vector<glm::vec4> colors(4, glm::vec4(color));

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
	return mesh->positions(positions)->colors(colors)->uv(uv)->indices(indices);
}

/// <summary>
/// Constructs a cube
/// </summary>
/// <param name="width">cube width</param>
/// <param name="length">cube length</param>
/// <param name="hight">cube hight</param>
/// <param name="color">cube color</param>
/// <returns>cube mesh</returns>
MeshRenderer* Mesh::cube(float width, float length, float hight, glm::vec4 color)
{
	float x = length / 2.0f;
	float y = hight / 2.0f;
	float z = width / 2.0f;

	std::vector<glm::vec3> positions = {
		glm::vec3(-x,  y, z),	// front left top
		glm::vec3( x,  y, z),	// front right top
		glm::vec3(-x, -y, z),	// front left bottom
		glm::vec3( x, -y, z),	// front right bottom

		glm::vec3(-x,  y, -z),	// back left top
		glm::vec3( x,  y, -z),	// back right top
		glm::vec3(-x, -y, -z),	// back left bottom
		glm::vec3( x, -y, -z),	// back right bottom
		
		glm::vec3(-x,  y,  z),	// back left top
		glm::vec3( x,  y,  z),	// back right top
		glm::vec3(-x,  y, -z),	// front left top
		glm::vec3( x,  y, -z),	// front right top

		glm::vec3(-x, -y,  z),	// back left bottom
		glm::vec3( x, -y,  z),	// back right bottom
		glm::vec3(-x, -y, -z),	// front left bottom
		glm::vec3( x, -y, -z),	// front right bottom
	};

	std::vector<glm::vec4> colors(16, color);

	std::vector<glm::vec2> uv = {
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 0.0f),

		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f)
	};

	float v = 0.33333333;

	std::vector<glm::vec3> normals = {
		glm::vec3(-v,  v, v),	// front left top
		glm::vec3( v,  v, v),	// front right top
		glm::vec3(-v, -v, v),	// front left bottom
		glm::vec3( v, -v, v),	// front right bottom
							   
		glm::vec3(-v,  v,  -v),	// back left top
		glm::vec3(v,  v,  -v),	// back right top
		glm::vec3(-v, -v,  -v),	// back left bottom
		glm::vec3(v, -v,  -v),	// back right bottom

		glm::vec3(-v,  v, v),	// back left top
		glm::vec3( v,  v, v),	// back right top
		glm::vec3(-v,  v, -v),	// front left top
		glm::vec3( v,  v, -v),	// front right top

		glm::vec3(-v, -v, v),   // back left bottom
		glm::vec3( v, -v, v),   // back right bottom
		glm::vec3(-v, -v, -v),	// front left bottom
		glm::vec3( v, -v, -v),	// front right bottom
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,	 // front face triangle 1
		1, 3, 2,  // front face triangle 2

		5, 4, 7,  // back face triangle 1
		4, 6, 7,  // back face triangle 2

		10, 11, 8,// top face triangle 1
		11, 9, 8, // top face triangle 2

		12, 13, 15,  // bottom face triangle 1
		12, 15, 14,  // bottom face triangle 2

		4, 0, 6,  // left face triangle 1
		0, 2, 6,  // left face triangle 2

		1, 5, 3,  // right face triangle 1
		5, 7, 3   // right face triangle 2 
	};

	MeshRenderer* mesh = new MeshRenderer();
	return mesh->positions(positions)->colors(colors)->uv(uv)->normals(normals)->indices(indices);
}

/// <summary>
/// Constructs a cone
/// </summary>
/// <param name="hight">cone hight</param>
/// <param name="radius">cone radius</param>
/// <param name="slices">cone slices</param>
/// <param name="color">cone color</param>
/// <returns>cone mesh</returns>
MeshRenderer* Mesh::cone(float hight, float radius, unsigned int slices, glm::vec4 color)
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
	uv.push_back(glm::vec2(0.5f, 1.0f));

	// bottom
	positions.push_back(glm::vec3(0.0f, -y, 0.0f));
	colors.push_back(color);
	uv.push_back(glm::vec2(0.5f, 1.0f));

	// slices
	for (int i = 0; i < slices; ++i) 
	{
		float rad = radSlice * i;
		float x = radius * cos(rad);
		float z = radius * sin(rad);

		positions.push_back(glm::vec3(x, -y, z));
		colors.push_back(color);
		uv.push_back(glm::vec2(0.5f, 0.0f));
	}

	unsigned int bottom = 1;
	unsigned int firstSlice = 2;
	unsigned int peak = 0;
	unsigned int indicesIndex = 2;
	unsigned int traversedSlices = 0;
	for (int i = 0; i < slices; i++)
	{
		traversedSlices++;

		unsigned int tmp = indicesIndex + 1;

		indices.push_back(peak);	// vertex 0 is the peak of the cone
		indices.push_back(indicesIndex);
		indices.push_back(traversedSlices >= slices ? firstSlice : tmp);

		indices.push_back(bottom);	// vertex 1 is the bottom of the cone
		indices.push_back(indicesIndex);
		indices.push_back(traversedSlices >= slices ? firstSlice : tmp);

		indicesIndex++;
	}

	MeshRenderer* mesh = new MeshRenderer();
	return mesh->positions(positions)->colors(colors)->uv(uv)->indices(indices);;
}