#ifndef __POT_INPUTLISTENER__
#define __POT_INPUTLISTENER__

#include <SFML/Window/Event.hpp>
#include "Core/Tools.hpp"

namespace sf
{
	class RenderWindow;
}

namespace Pot
{

class InputListener
{
	public:
		InputListener(sf::RenderWindow& window);
		virtual ~InputListener() {}

		virtual void onEvent(const sf::Event& event);

		/* Window-related events */
		virtual void onFocusLost(void) {}
		virtual void onFocusGained(void) {}
		virtual void onWindowClosed(void) {}
		virtual void onWindowResized(const sf::Event::SizeEvent size) { POT_UNUSED(size); }

		/* Keyboard-related events */
		virtual void onTextEntered(const sf::Event::TextEvent& text) { POT_UNUSED(text); }
		virtual void onKeyPressed(const sf::Event::KeyEvent& key) { POT_UNUSED(key); }
		virtual void onKeyReleased(const sf::Event::KeyEvent& key) { POT_UNUSED(key); }

		/* Mouse-related events */
		virtual void onMouseEntered(void) {}
		virtual void onMouseLeft(void) {}
		virtual void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove) { POT_UNUSED(mouseMove); }
		virtual void onMouseWheelMoved(const sf::Event::MouseWheelEvent& mouseWheel) { POT_UNUSED(mouseWheel); }
		virtual void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton) { POT_UNUSED(mouseButton); }
		virtual void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton) { POT_UNUSED(mouseButton); }

		/* Joystick-related events */
		virtual void onJoystickConnected(const sf::Event::JoystickConnectEvent& joystickConnect) { POT_UNUSED(joystickConnect); }
		virtual void onJoystickDisconnected(const sf::Event::JoystickConnectEvent& joystickConnect) { POT_UNUSED(joystickConnect); }
		virtual void onJoystickButtonPressed(const sf::Event::JoystickButtonEvent& joystickButton) { POT_UNUSED(joystickButton); }
		virtual void onJoystickButtonReleased(const sf::Event::JoystickButtonEvent& joystickButton) { POT_UNUSED(joystickButton); }
		virtual void onJoystickMoved(const sf::Event::JoystickMoveEvent& joystickMove) { POT_UNUSED(joystickMove); }

	protected:
		sf::RenderWindow& m_window;
};

class SimpleInputListener: public InputListener
{
	public:
		SimpleInputListener(sf::RenderWindow& window);
		virtual ~SimpleInputListener() {}
		
		virtual void onWindowClosed(void);
		virtual void onKeyReleased(const sf::Event::KeyEvent& key);
};

}

#endif
