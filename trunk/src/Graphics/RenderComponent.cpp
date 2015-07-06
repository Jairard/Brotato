#include "../Core/Math.hpp"
#include "../GameObjects/GameObject.hpp"
#include "GeometryComponent.hpp"
#include "RenderComponent.hpp"

namespace Graphics
{
	RenderComponent::RenderComponent(sf::RenderTarget& target):
		Component(),
		m_geometry(0),
		m_target(target),
		m_states(sf::RenderStates::Default),
		m_lastTransform(),
		m_delta()
	{
	}
	
	void RenderComponent::init()
	{
		if (hasGameObject())
			m_geometry = gameObject()->geometry();
	}
	
	void RenderComponent::onUpdate(float interpolationCoef)
	{
		if (m_geometry == 0)
			return;
		
		sf::VertexArray array = m_geometry->vertices();
		m_states.transform = Math::lerp(m_lastTransform, m_delta, interpolationCoef).getTransform();
		m_target.draw(&array[0], array.getVertexCount(), array.getPrimitiveType(), m_states);
	}
	
	void RenderComponent::onLogicsUpdate()
	{
		if (!hasGameObject())
			return;
		
		sf::Transformable t = gameObject()->transform;
		
		m_delta.setPosition(t.getPosition() - m_lastTransform.getPosition());
		m_delta.setScale(t.getScale() - m_lastTransform.getScale());
		m_delta.setRotation(t.getRotation() - m_lastTransform.getRotation());
		m_lastTransform = t;
	}
}
