#include "OpenGL.h"

void OpenGL::draw(const VertexArrayObject& vertexArray, const ElementBufferObject& elementBuffer)
{
	vertexArray.bind();
	elementBuffer.bind();

	glDrawElements(GL_TRIANGLES, elementBuffer.getCount(), GL_UNSIGNED_INT, 0);
}

void OpenGL::clear(unsigned int clear)
{
	glClear(clear);
}

/// <summary>
/// Controls the interpretation of polygons for rasterization
/// </summary>
/// <param name="mode">GL_POINT, GL_LINE or GL_FILL</param>
void OpenGL::polygonMode(unsigned int mode)
{
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void OpenGL::switchPolygonMode()
{
	int mode;
	glGetIntegerv(GL_POLYGON_MODE, &mode);
	polygonMode(mode == GL_FILL ? GL_LINE : GL_FILL);
}

void OpenGL::enable(unsigned int cap)
{
	glEnable(cap);
}

void OpenGL::blendFunction(unsigned int sfactor, unsigned int dfactor)
{
	glBlendFunc(sfactor, dfactor);
}