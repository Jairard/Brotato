#include "_ThickPointShape.hpp"

ThickPointShape::ThickPointShape(const sf::RenderWindow* window, const sf::Vector2f center):
	sf::RectangleShape(),
	_thickness(1.),
	_window(window)
{
	setPosition(center);
	update();
}

void ThickPointShape::setThickness(float thickness)
{
	_thickness = thickness;
	update();
}

void ThickPointShape::setColor(const sf::Color& color)
{
	setFillColor(color);
}

void ThickPointShape::update()
{
	float xRatio = _window->getView().getSize().x / (float)_window->getSize().x;
	float yRatio = _window->getView().getSize().y / (float)_window->getSize().y;

	setSize(sf::Vector2f(_thickness, _thickness));
	setOrigin(sf::Vector2f(_thickness, _thickness) / 2.f);
	setScale(sf::Vector2f(xRatio, yRatio));
}

