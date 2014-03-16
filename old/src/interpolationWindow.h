#ifndef INTERPOLATIONWINDOW_H
#define INTERPOLATIONWINDOW_H

#include <list>
#include <SFML/Graphics.hpp>
#include "interpolable.h"

class InterpolationWindow: public sf::RenderWindow
{
	public:
		InterpolationWindow(unsigned int ups=25);
		InterpolationWindow(sf::VideoMode mode,
							const sf::String& title,
							sf::Uint32 style=sf::Style::Default,
							const sf::ContextSettings& settings=sf::ContextSettings(),
							unsigned int ups=25);
		InterpolationWindow(sf::WindowHandle handle, const sf::ContextSettings& settings=sf::ContextSettings(), unsigned int ups=25);
		virtual ~InterpolationWindow() {}

		void addInterpolable(Interpolable* interpolable);
		void addInterpolables(std::list<Interpolable*> interpolables);
		void removeInterpolable(Interpolable* interpolable);
		void removeInterpolables(std::list<Interpolable*> interpolables);

		virtual void onEvent(const sf::Event& event) {}
		virtual void onUpdate(void) {}
		virtual void onDraw(void) {}
		void loop(void);

		unsigned int fps(void) const   { return _fps; }

	protected:
		unsigned int _ups, _fps;
		std::list<Interpolable*> _objects;

	private:
		void interpolate(float interpolation);
};

#endif
