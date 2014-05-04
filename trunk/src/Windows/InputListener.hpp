#ifndef __EVENTLISTENER__
#define __EVENTLISTENER__

#include <SFML/Graphics.hpp>
#include "../Core/Vector2.hpp"
#include "../Core/Tools.hpp"

class Window;

class InputListener
{
	public:
		InputListener(Window& window);
		virtual ~InputListener() {}
		
		virtual void onEvent(const sf::Event& event);
		
		/* Window-related events */
		virtual void onFocusLost(void) {}
		virtual void onFocusGained(void) {}
		virtual void onWindowClosed(void);
		virtual void onWindowResized(const sf::Event::SizeEvent size) { UNUSED(size); }
		
		/* Keyboard-related events */
		virtual void onTextEntered(const sf::Event::TextEvent& text) { UNUSED(text); }
		virtual void onKeyPressed(const sf::Event::KeyEvent& key) { UNUSED(key); }
		virtual void onKeyReleased(const sf::Event::KeyEvent& key);
		
		/* Mouse-related events */
		virtual void onMouseEntered(void) {}
		virtual void onMouseLeft(void) {}
		virtual void onMouseMoved(const sf::Event::MouseMoveEvent& mouseMove) { UNUSED(mouseMove); }
		virtual void onMouseWheelMoved(const sf::Event::MouseWheelEvent& mouseWheel) { UNUSED(mouseWheel); }
		virtual void onMouseButtonPressed(const sf::Event::MouseButtonEvent& mouseButton) { UNUSED(mouseButton); }
		virtual void onMouseButtonReleased(const sf::Event::MouseButtonEvent& mouseButton) { UNUSED(mouseButton); }
		
		/* Joystick-related events */
		virtual void onJoystickConnected(const sf::Event::JoystickConnectEvent& joystickConnect) { UNUSED(joystickConnect); }
		virtual void onJoystickDisconnected(const sf::Event::JoystickConnectEvent& joystickConnect) { UNUSED(joystickConnect); }
		virtual void onJoystickButtonPressed(const sf::Event::JoystickButtonEvent& joystickButton) { UNUSED(joystickButton); }
		virtual void onJoystickButtonReleased(const sf::Event::JoystickButtonEvent& joystickButton) { UNUSED(joystickButton); }
		virtual void onJoystickMoved(const sf::Event::JoystickMoveEvent& joystickMove) { UNUSED(joystickMove); }
		
	protected:
		Window& m_window;
};

#endif
