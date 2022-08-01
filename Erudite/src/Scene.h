#pragma once

#include "GameObject.h"

class Scene {
public:
   Scene();                                                          // constructor
   ~Scene();                                                         // destructor

   void render();                                                    // renders all objects inside the scene
   void add(GameObject* gameObject);                                 // adds a gameobject to the scene
   void remove(unsigned int index);                                  // removes a gameobject from the scene
   GameObject* at(unsigned int index);                               // gets a gameobject at index
   void clear();                                                     // clears / deletes all gameobjects from the scene

private:
   Camera* m_camera = Camera::instance();                            // camera instance
   std::vector<GameObject*>* m_gameObjects = new std::vector<GameObject*>();  // All gameobjects inside the scene
};