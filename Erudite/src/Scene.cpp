#include "Scene.h"

/// <summary>
/// Constructor
/// </summary>
Scene::Scene()
{
}

/// <summary>
/// Destructor
/// </summary>
Scene::~Scene()
{
	clear();
	delete m_gameObjects;
}

/// <summary>
/// Renders all objects inside the scene
/// </summary>
void Scene::render()
{
	for (GameObject* object : *m_gameObjects)
	{
		if (object->m_active) 
		{
			object->transform();
			object->render();
		}
	}
}

/// <summary>
/// Adds a gameobject to the scene
/// </summary>
/// <param name="gameObject">gameobject to add</param>
void Scene::add(GameObject* gameObject)
{
	m_gameObjects->push_back(gameObject);
}

/// <summary>
/// Removes a gameobject from the scene
/// </summary>
/// <param name="index">gameobject at index to remove</param>
void Scene::remove(unsigned int index)
{
	m_gameObjects->erase(std::next(m_gameObjects->begin(), index));
}

/// <summary>
/// Gets a gameobject at index
/// </summary>
/// <param name="index">index of the gameobject to get</param>
/// <returns></returns>
GameObject* Scene::at(unsigned int index)
{
	return m_gameObjects->at(index);
}

/// <summary>
/// Get a gameobject by name
/// </summary>
/// <param name="name">name of the gameobject</param>
/// <returns>the game object with name or nullptr</returns>
GameObject* Scene::get(std::string name)
{
	for(GameObject* g : *m_gameObjects)
	{
		if (g->m_name == name)
			return g;
	}
	return nullptr;
}

/// <summary>
/// Returns all Gamobjects
/// </summary>
/// <returns></returns>
std::vector<GameObject*>* Scene::all()
{
	return m_gameObjects;
}

/// <summary>
/// Clears / deletes all gameobjects from the scene
/// </summary>
void Scene::clear()
{
	m_gameObjects->clear();
	m_gameObjects->shrink_to_fit();
}