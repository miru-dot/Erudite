#include "Draw.h"
#include <vector>

void Draw::rectangle(float width, float length)
{
	float x = length / 2.0f;
	float y = width / 2.0f;

	float vertices[] = {
		-x,  y,	// left top
		 x,  y,  // right top
		-x, -y,	// left bottom
		 x, -y,	// right bottom
	};

	unsigned int indices[] = {
		0, 1, 2,	// triangle 1
		1, 3, 2
	};


}