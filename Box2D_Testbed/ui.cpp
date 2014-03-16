#include <iostream>
#include <cstdarg>

#include "test.hpp"
#include "ui.hpp"

const char* UI::FONT_FILE = "arial.ttf";

UI::UI(const Settings& settings):
	sf::Drawable(),
	sf::View(),
	_font(),
	_background(),
	_checkboxes()
{
	updateBackground();
	_background.setFillColor(sf::Color(200, 200, 200));
	_isFontLoaded = _font.loadFromFile(FONT_FILE);
	if (!_isFontLoaded)
		std::cerr << "Couldn't load font '" << FONT_FILE << "'" << std::endl;

	build(settings);
}

UI::~UI()
{
	std::vector<CheckBox*>::iterator it;
	for (it=_checkboxes.begin(); it!=_checkboxes.end(); it++)
		delete *it;
}

void UI::build(const Settings& settings)
{
	_checkboxes.push_back(new CheckBox(settings.drawShapes, "Draw shapes"));
	/*
	_checkboxes.push_back(new CheckBox());
	_checkboxes.push_back(new CheckBox());
	_checkboxes.push_back(new CheckBox());
	_checkboxes.push_back(new CheckBox());
	_checkboxes.push_back(new CheckBox());
	//*/

	/*
	sf::Vector2f windowSize(window->getSize());

	float xRatio = 0.5 * getSize().x / (float)windowSize.x;
	float yRatio = 0.5 * getSize().y / (float)windowSize.y;

	text.setScale(sf::Vector2f(xRatio, yRatio));

	std::vector<CheckBox*>::iterator it;
	for (it=_checkboxes.begin(); it!=_checkboxes.end(); it++)
		(*it)->setScale(sf::Vector2f(xRatio, yRatio));
	*/

	const unsigned int start = 5, step = 15;

	for (unsigned int i=0; i<_checkboxes.size(); i++)
	{
		CheckBox* cb = _checkboxes[i];
		cb->setPosition(5, start + i*step);
		cb->setPosition(0, 0);
		cb->setScale(100, 100);
	}
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.setView(*this);
	target.draw(_background);

	if (_isFontLoaded)
	{
		std::vector<CheckBox*>::const_iterator it;
		for (it=_checkboxes.begin(); it!=_checkboxes.end(); it++)
		{
			target.draw(**it);
		}
	}
}

void UI::updateBackground()
{
	_background.setSize(getSize());
}

CheckBox::CheckBox(bool checked, const char* txt, ...):
	sf::Drawable(),
	_checked(checked),
	_text()
{
	char buffer[512];
	va_list arg;

	va_start(arg, txt);
	vsprintf(buffer, txt, arg);
	va_end(arg);

	_text.setString(buffer);
	_text.setColor(sf::Color(255, 255, 255));
}

void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::cout << _text.getString().toAnsiString() << std::endl;
	std::cout << getPosition().x << " " << getPosition().y << std::endl;
	std::cout << getScale().x << " " << getScale().y << std::endl;
	states.transform *= getTransform();
	target.draw(_text);
}
