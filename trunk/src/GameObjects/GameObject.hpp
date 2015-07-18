#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include <list>
#include <string>
#include <SFML/Graphics/Transformable.hpp>
#include "../Core/Vector2_.hpp"
#include "../Core/Stainable.hpp"
#include "../Graphics/GeometryComponent.hpp"
#include "../Graphics/RenderComponent.hpp"

class Component;

	class GameObject
	{
		public:
			/* Constructor/Desctructor */
			GameObject(const char* name="");
			GameObject(const std::string& name);
			virtual ~GameObject();
			
			/* Getters/Setters */
			int id(void) const                                   { return m_id; }
			const std::string& name(void) const                  { return m_name; }
			void setName(const std::string& name)                { m_name = name; }
			const std::list<Component*>& components() const      { return m_components; }
			Graphics::GeometryComponent* geometry()              { return m_geometry; }
			const Graphics::GeometryComponent* geometry() const  { return m_geometry; }
			Graphics::RenderComponent* renderer()                { return m_renderer; }
			const Graphics::RenderComponent* renderer() const    { return m_renderer; }
			unsigned int childCount(void) const                  { return m_children.size(); }
			std::list<GameObject*> children()                    { return m_children; }
			const std::list<GameObject*> children() const        { return m_children; }
			GameObject* parent(void)                             { return m_parent; }
			const GameObject* parent(void) const                 { return m_parent; }
			
			/* Components manipulators */
			void addComponent(Component* component);
			template <typename T> T* fetchComponent(void);
			template <typename T> std::list<T*>* fetchComponents(void);
			
			/* Update manipulators */
			virtual void onUpdate(float interpolationCoef);
			virtual void onLogicsUpdate(void);
			
			/* Hierarchy manipulators */
			void addChild(GameObject* child);
			void removeChild(GameObject* child);
			void setParent(GameObject* parent);
			
		private:
			void setGeometry(Graphics::GeometryComponent* comp);
			void setRenderer(Graphics::RenderComponent* comp);
			
		public:
			sf::Transformable transform;
			
		protected:
			int m_id;
			std::string m_name;
			std::list<Component*> m_components;
			std::list<GameObject*> m_children;
			GameObject* m_parent;
			Graphics::GeometryComponent* m_geometry;
			Graphics::RenderComponent* m_renderer;
			Stainable<sf::Transformable> m_worldTransform;
			
		private:
			static int s_objectCount;
	};

#endif
