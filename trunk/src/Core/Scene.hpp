#ifndef __SCENE__
#define __SCENE__

#include <string>
#include "../GameObjects/GameObject.hpp"

class Scene
{
	public:
		Scene(const std::string& name = "");
		~Scene();
		
		const std::string& name(void) const  { return m_name; }
		GameObject* root(void)               { return m_root; }
		const GameObject* root(void) const   { return m_root; }
		
		void updateLogics(void);
		void render(float coef);
		
		void addGameObject(GameObject* object);
		void setParent(GameObject* object, GameObject* parent);
		void log(const char* tag);
		
	private:
		void updateGameObject(GameObject* object);
		void renderGameObject(GameObject* object, float coef);
		void logGameObject(const char* tag, GameObject* object, int depth = 0);
		
	protected:
		std::string m_name;
		GameObject* m_root;
};

#endif
