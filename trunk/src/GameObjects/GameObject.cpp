#include "GameObject.hpp"
#include "../PotatoEngine/Debug/Logger.hpp"
#include "../PotatoEngine/Core/Tools.hpp"
#include "../Core/Component.hpp"

using Pot::Debug::Logger;

	int GameObject::s_objectCount = 0;
	
	GameObject::GameObject(const std::string& name):
		transform(),
		m_id(s_objectCount++),
		m_name(name),
		m_components(),
		m_children(),
		m_parent(0),
		m_geometry(0),
		m_renderer(0)
	{}
	
	GameObject::GameObject(const char* name):
		transform(),
		m_id(s_objectCount++),
		m_name(name),
		m_components(),
		m_children(),
		m_parent(0),
		m_geometry(0),
		m_renderer(0)
	{
	}
	
	GameObject::~GameObject()
	{
		std::list<Component*>::iterator it;
		
		for (it=m_components.begin(); it!=m_components.end(); it++)
			delete *it;
	}
	
	void GameObject::addComponent(Component* component)
	{
		if (component == 0)
			return;
		
		component->setGameObject(this);
		m_components.push_back(component);
		
		setGeometry(Pot::Tools::as<Graphics::GeometryComponent>(component));
		setRenderer(Pot::Tools::as<Graphics::RenderComponent>(component));
	}
	
	template <typename T>
	T* GameObject::fetchComponent()
	{
		std::list<Component*>::iterator it;
		
		for (it=m_components.begin(); it!=m_components.end(); it++)
			if (Pot::Tools::is<T>(*it))
				return (T*)*it;
		
		return 0;
	}
	
	template <typename T>
	std::list<T*>* GameObject::fetchComponents()
	{
		std::list<Component*>::iterator it;
		std::list<T*>* components = new std::list<T*>();
		
		for (it=m_components.begin(); it!=m_components.end(); it++)
			if (Pot::Tools::is<T>(*it))
				components->push_back((T*)*it);
		
		return components;
	}
	
	void GameObject::onUpdate(float interpolationCoef)
	{
		std::list<Component*>::iterator it;
		
		for (it=m_components.begin(); it!=m_components.end(); it++)
			if ((*it)->enabled)
				(*it)->onUpdate(interpolationCoef);
	}
	
	void GameObject::onLogicsUpdate()
	{
		std::list<Component*>::iterator it;
		
		for (it=m_components.begin(); it!=m_components.end(); it++)
			if ((*it)->enabled)
				(*it)->onLogicsUpdate();
	}
	
	void GameObject::addChild(GameObject* child)
	{
		if (child != 0)
			m_children.push_back(child);
	}
	
	void GameObject::removeChild(GameObject* child)
	{
		if (child == 0)
			return;
		
		std::list<GameObject*>::iterator it;
		
		for (it=m_children.begin(); it!=m_children.end(); ++it)
		{
			if ((*it) == child)
			{
				m_children.erase(it);
				return;
			}
		}
		
		Logger::log("Warning", "Trying to remove '%s' from children but it was not found", child->name().c_str());
	}
	
	void GameObject::setParent(GameObject* parent)
	{
		if (parent != 0)
			m_parent = parent;
	}
	
	void GameObject::setGeometry(Graphics::GeometryComponent* comp)
	{
		if (comp == 0)
			return;
		
		if (m_geometry != 0)
		{
			Logger::log("Warning", "Gameobject '%s' has several geometries", name().c_str());
			return;
		}
		
		m_geometry = comp;
	}
	
	void GameObject::setRenderer(Graphics::RenderComponent* comp)
	{
		if (comp == 0)
			return;
		
		if (m_renderer != 0)
		{
			Logger::log("Warning", "Gameobject '%s' has several renderers", name().c_str());
			return;
		}
		
		m_renderer = comp;
	}
