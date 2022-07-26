#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	clear();
	delete m_gameObjects;
}

void Scene::render(float deltaTime)
{
	for (GameObject* object : *m_gameObjects)
	{
		object->m_transform->m_rotation->y += deltaTime * 5.0f;
		object->transform();
		object->render();
	}
}

void Scene::add(GameObject* gameObject)
{
	m_gameObjects->push_back(gameObject);
}

void Scene::remove(GameObject* gameObject)
{
	m_gameObjects->remove(gameObject);
}

void Scene::clear()
{
	m_gameObjects->clear();
	m_gameObjects->resize(0);
}