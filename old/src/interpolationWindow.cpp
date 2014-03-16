#include <iostream>
#include "interpolationwindow.h"

InterpolationWindow::InterpolationWindow(unsigned int ups):
	sf::RenderWindow(),
	_ups(ups),
	_fps(0),
	_objects()
{}

InterpolationWindow::InterpolationWindow(sf::VideoMode mode,
										 const sf::String& title,
										 sf::Uint32 style,
										 const sf::ContextSettings& settings,
										 unsigned int ups):
	sf::RenderWindow(mode, title, style, settings),
	_ups(ups),
	_fps(0),
	_objects()
{}

InterpolationWindow::InterpolationWindow(sf::WindowHandle handle, const sf::ContextSettings& settings, unsigned int ups):
	sf::RenderWindow(handle, settings),
	_ups(ups),
	_fps(0),
	_objects()
{}

void InterpolationWindow::addInterpolable(Interpolable* interpolable)
{
	addInterpolables(std::list<Interpolable*>(1, interpolable));
}

void InterpolationWindow::addInterpolables(std::list<Interpolable*> interpolables)
{
	for (std::list<Interpolable*>::iterator it=interpolables.begin(); it!=interpolables.end(); it++)
		_objects.push_back(*it);
}

void InterpolationWindow::removeInterpolable(Interpolable* interpolable)
{
	removeInterpolables(std::list<Interpolable*>(1, interpolable));
}

void InterpolationWindow::removeInterpolables(std::list<Interpolable*> interpolables)
{
	for (std::list<Interpolable*>::iterator it=interpolables.begin(); it!=interpolables.end(); it++)
		_objects.remove(*it);
}

void InterpolationWindow::interpolate(float interpolation)
{
	for (std::list<Interpolable*>::iterator it=_objects.begin(); it!=_objects.end(); it++)
		(*it)->interpolate(interpolation);
}

void InterpolationWindow::loop()
{
	sf::Clock updateClock;
	int f = 0;

	while (isOpen())
	{
		float elapsed = updateClock.getElapsedTime().asSeconds();

		if (elapsed >= 1./_ups)
		{
			_fps = f * _ups;
			f = 0;
			updateClock.restart();

			sf::Event event;
			while (pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					close();
				onEvent(event);
			}
			onUpdate();

			elapsed = updateClock.getElapsedTime().asSeconds();
		}

		//*
		interpolate(elapsed * _ups);
		/*/
		interpolate(.75);
		//*/

		clear();
		onDraw();
		display();

		f++;
	}
}
