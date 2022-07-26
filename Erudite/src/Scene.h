#pragma once

#include "GameObject.h"

class Scene {
public:
   Scene();
   ~Scene();

   void render(float deltaTime);
   void add(GameObject* gameObject);
   void remove(GameObject* gameObject);
   void clear();

private:
   Camera* m_camera = Camera::instance();
   std::list<GameObject*>* m_gameObjects = new std::list<GameObject*>();
};