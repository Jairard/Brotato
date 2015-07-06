#include "Component.hpp"
#include "../GameObjects/GameObject.hpp"

Component::Component():
	enabled(true),
	m_gameObject(0)
{
}

Component::~Component()
{
}

