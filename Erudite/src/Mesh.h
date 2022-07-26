#pragma once

#include "GameObject.h"

class Mesh {
public:
   static GameObject* triangle(float size, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Texture* texture = new Texture("res/textures/default.png"));
   static GameObject* rectangle(float width, float length, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Texture* texture = new Texture("res/textures/default.png"));
   static GameObject* cube(float width, float length, float hight, glm::vec4 top = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
      glm::vec4 bottom = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), Texture* texture = new Texture("res/textures/default.png"));
   static GameObject* cone(float hight, float radius, unsigned int slices, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
};