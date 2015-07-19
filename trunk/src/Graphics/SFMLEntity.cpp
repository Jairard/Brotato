#include "SFMLEntity.hpp"
#include "../PotatoEngine/Core/LibsHelpers.hpp"

namespace Graphics
{
	SFMLEntity::SFMLEntity()
	{
	}
	
	void SFMLEntity::setOrigin(const Pot::Vector2f& origin)
	{
		sf::Transformable::setOrigin(pv_2_sfv(origin));
	}
	
	void SFMLEntity::setPosition(const Pot::Vector2f& position)
	{
		Entity::setPosition(position);
		sf::Transformable::setPosition(pv_2_sfv(position));
	}
	
	void SFMLEntity::setScale(const Pot::Vector2f& factors)
	{
		sf::Transformable::setScale(pv_2_sfv(factors));
	}
	
	void SFMLEntity::setRotation(float angle)
	{
		Entity::setRotation(angle);
		sf::Transformable::setRotation(angle);
	}
	
	void SFMLEntity::onGameUpdate(const Pot::Vector2f& position, float angle)
	{
		Entity::onGameUpdate(position, angle);
		
		setPosition(position);
		setRotation(angle);
	}
}
