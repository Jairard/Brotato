#include "Entity.hpp"
#include "../Core.hpp"
#include "../PotatoEngine/Core/Math.hpp"
namespace Graphics
{
	Entity::Entity():
		m_velocity(),
		m_lastPosition(),
		m_currentPosition(),
		m_angularVelocity(0.),
		m_lastRotation(0.),
		m_currentRotation(0.)
	{}
	
	void Entity::setPosition(const Pot::Vector2f& position)
	{
		m_currentPosition = position;
	}
	
	void Entity::setRotation(float angle)
	{
		m_currentRotation = angle;
	}
	
	void Entity::onGameUpdate(const Pot::Vector2f& position, float angle)
	{
		m_velocity = position - m_lastPosition;
		
		m_lastPosition = position;
		m_angularVelocity = angle - m_lastRotation;
		m_lastRotation = angle;
	}
	
	void Entity::extrapolate(float coef)
	{
		setPosition(Pot::Math::lerp(m_lastPosition, m_lastPosition + m_velocity, coef));
		setRotation(Pot::Math::lerp(m_lastRotation, m_lastRotation + m_angularVelocity, coef));
	}
	
	void Entity::render(sf::RenderTarget& target, float coef, sf::RenderStates states)
	{
		UNUSED(target);
		UNUSED(states);
		
		extrapolate(coef);
	}
}
