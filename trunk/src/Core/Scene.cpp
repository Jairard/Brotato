#include <sstream>
#include <list>
#include "Scene.hpp"

Scene::Scene(const std::string& name):
	m_name(name),
	m_root(new GameObject("SceneRoot"))
{
}

Scene::~Scene()
{
	delete m_root;
}

void Scene::updateLogics()
{
	updateGameObject(m_root);
}

void Scene::updateGameObject(GameObject* object)
{
	if (object == 0)
		return;
	
	object->onLogicsUpdate();
	
	std::list<GameObject*> children = object->children();
	std::list<GameObject*>::iterator it;
	
	for (it=children.begin(); it!=children.end(); ++it)
		updateGameObject(*it);
}

void Scene::render(float coef)
{
	renderGameObject(m_root, coef);
}

void Scene::renderGameObject(GameObject* object, float coef)
{
	if (object == 0)
		return;
	
	object->onUpdate(coef);
	
	std::list<GameObject*> children = object->children();
	std::list<GameObject*>::iterator it;
	
	for (it=children.begin(); it!=children.end(); ++it)
		renderGameObject(*it, coef);
}

void Scene::addGameObject(GameObject* object)
{
	if (object == 0)
		return;
	
	setParent(object, m_root);
}

void Scene::setParent(GameObject* object, GameObject* parent)
{
	if (object != 0 && parent != 0)
	{
		GameObject* currentParent = object->parent();
		if (currentParent != 0)
			object->parent()->removeChild(object);
		
		object->setParent(parent);
		parent->addChild(object);
	}
}

void Scene::log(const char* tag)
{
	Logger::log(tag, "Scene: %s", name().c_str());
	logGameObject(tag, m_root);
}

void Scene::logGameObject(const char* tag, GameObject* object, int depth)
{
	std::stringstream str;
	
	for (int i=0; i<depth; i++)
		str << '\t';
	
	if (object == 0)
	{
		str << "<Null GameObject>";
		return;
	}
	
	str << object->name() << " (" << object->childCount() << " children)";
	Logger::log(tag, str.str().c_str());
	
	std::list<GameObject*> children = object->children();
	std::list<GameObject*>::iterator it;
	for (it=children.begin(); it!=children.end(); ++it)
		logGameObject(tag, *it, depth+1);
}

