#include "Box.hpp"
#include "../Core/Math.hpp"

namespace GO
{
	Box::Box(Phy::World* world, Phy::BodyType type,
	         const Vector2f& center, const Vector2f& size,
	         float angle, const sf::Color& color) :
		GameObject(),
		Phy::Rectangle(world, center, size, type),
		Graphics::RectangleShape()
	{
		/* Physics initialization */
		bodyDef().angle = angle;
		world->RegisterEntity(this, m_isSecure);

		/* Graphics initialization */
		Vector2f realSize = Vector2f(size) + 2*shape()->m_radius;
		setScale(Phy::World::vectorToPhy(realSize).toSFML());
		setPosition(Phy::World::vectorToPhy(center).toSFML());
		setColor(color);
		setRotation(Phy::World::angleFromPhy(angle));
	}

	void Box::update(const Vector2f& position, float angle)
	{
		Phy::Rectangle::update(position, angle);

		setPosition(position.toSFML());
		setRotation(angle);
	}
}
