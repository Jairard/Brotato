#ifndef __POTATOPLANT__
#define __POTATOPLANT__

#include <SFML/Graphics.hpp>
#include "Debug/Renderer.hpp"
#include "../Windows/InputListener.hpp"

namespace Pot
{

namespace Debug
{
	class Renderer;
}

class Stem;
// TODO: remove
class Potato;

// TODO: add physics
class PotatoPlant// : Singleton<PotatoPlant>
{
	public:
		PotatoPlant(const sf::String& title, sf::VideoMode mode,
		            unsigned int targetUps=PotatoPlant::DEFAULT_UPS,
		            sf::Uint32 style=sf::Style::Default,
		            const sf::ContextSettings& settings=sf::ContextSettings());
		
		void initialize();
		void shutdown();
		int loop();
		
		bool cellsDebugStatus() const           { return m_debugCells; }
		void SetCellsDebugStatus(bool status)   { m_debugCells = status; }
		bool physicsDebugStatus() const         { return m_debugPhysics; }
		void SetPhysicsDebugStatus(bool status) { m_debugPhysics = status; }
		sf::RenderTarget* window()              { return &m_window; }
		
	private:
		void handleInput();
		// TODO: find a better name for 'elapsedTime'
		// for it actually is the interpolation value 
		// between 2 logics updates.
		void render(float elapsedTime);
		void update();
		
		void checkTime(void); // Debug purpose
		
		// Temp
		void setupPotato(Potato* potato);
		
	private:
		static const unsigned int DEFAULT_UPS;
		
		sf::RenderWindow m_window;
		InputListener m_inputListener;
		Stem* m_stem;
		// TODO: check why implementing the accessor here does not compile (after cleaning)
		// and set m_debugRenderer as an instance (and not a pointer)
		Debug::Renderer* m_debugRenderer;
		sf::Clock m_countingClock;
		unsigned int m_targetUps;
		unsigned int m_frameCount, m_updateCount;
		unsigned int m_fps, m_ups;
		bool m_debugCells, m_debugPhysics;
};

}

#endif
