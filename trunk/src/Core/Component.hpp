#ifndef __CORE_COMPONENT__
#define __CORE_COMPONENT__

#include "Tools.hpp"

class GameObject;

class Component
{
	public:
		bool enabled;
		
		Component();
		virtual ~Component();
		
		bool hasGameObject(void)                        { return m_gameObject != 0; }
		GameObject* gameObject(void)                { return m_gameObject; }
		void setGameObject(GameObject* gameObject)  { m_gameObject = gameObject; }
		
		virtual void init(void) = 0;
		virtual void onUpdate(float interpolationCoef) = 0;
		virtual void onLogicsUpdate(void) = 0;
		
	protected:
		GameObject* m_gameObject;
};

class DummyComponent : public Component
{
	public:
		virtual void init(void)                         {}
		virtual void onUpdate(float interpolationCoef)  { UNUSED(interpolationCoef); }
		virtual void onLogicsUpdate(void)               {}
};

#endif
