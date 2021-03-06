#include "Window.hpp"
#include "InputListener.hpp"
#include "../Core/Logger.hpp"

InputListener::InputListener(Window& window):
	m_window(window)
{}

void InputListener::onEvent(const sf::Event& event)
{
	switch (event.type)
	{
		/* Window */
		case sf::Event::LostFocus:               onFocusLost();                                   break;
		case sf::Event::GainedFocus:             onFocusGained();                                 break;
		case sf::Event::Closed:                  onWindowClosed();                                break;
		case sf::Event::Resized:                 onWindowResized(event.size);                     break;
			
		/* Keyboard */
		case sf::Event::TextEntered:             onTextEntered(event.text);                       break;
		case sf::Event::KeyPressed:              onKeyPressed(event.key);                         break;
		case sf::Event::KeyReleased:             onKeyReleased(event.key);                        break;
			
		/* Mouse */
		case sf::Event::MouseEntered:            onMouseEntered();                                break;
		case sf::Event::MouseLeft:               onMouseLeft();                                   break;
		case sf::Event::MouseMoved:              onMouseMoved(event.mouseMove);                   break;
		case sf::Event::MouseWheelMoved:         onMouseWheelMoved(event.mouseWheel);             break;
		case sf::Event::MouseButtonPressed:      onMouseButtonPressed(event.mouseButton);         break;
		case sf::Event::MouseButtonReleased:     onMouseButtonReleased(event.mouseButton);        break;
			
		/* Joystick */
		case sf::Event::JoystickConnected:       onJoystickConnected(event.joystickConnect);      break;
		case sf::Event::JoystickDisconnected:    onJoystickDisconnected(event.joystickConnect);   break;
		case sf::Event::JoystickButtonPressed:   onJoystickButtonPressed(event.joystickButton);   break;
		case sf::Event::JoystickButtonReleased:  onJoystickButtonReleased(event.joystickButton);  break;
		case sf::Event::JoystickMoved:           onJoystickMoved(event.joystickMove);             break;
			
		default:
			Logger::log("Warning", "Unknow event type: %d", event.type);
			break;
	}
}

void InputListener::onWindowClosed()
{
	m_window.close();
}

void InputListener::onKeyReleased(const sf::Event::KeyEvent& key)
{
	if (key.code == sf::Keyboard::Escape)
		m_window.close();
}

