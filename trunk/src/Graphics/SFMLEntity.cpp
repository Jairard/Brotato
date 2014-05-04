#include "SFMLEntity.hpp"

namespace Graphics
{
	SFMLEntity::SFMLEntity()
	{
	}
	
	void SFMLEntity::setOrigin(const Vector2f& origin)
	{
		sf::Transformable::setOrigin(origin.toSFML());
	}
	
	void SFMLEntity::setPosition(const Vector2f& position)
	{
		Entity::setPosition(position);
		sf::Transformable::setPosition(position.toSFML());
	}
	
	void SFMLEntity::setScale(const Vector2f& factors)
	{
		sf::Transformable::setScale(factors.toSFML());
	}
	
	void SFMLEntity::setRotation(float angle)
	{
		Entity::setRotation(angle);
		sf::Transformable::setRotation(angle);
	}
	
	void SFMLEntity::onGameUpdate(const Vector2f& position, float angle)
	{
		Entity::onGameUpdate(position, angle);
		
		setPosition(position);
		setRotation(angle);
	}
}
