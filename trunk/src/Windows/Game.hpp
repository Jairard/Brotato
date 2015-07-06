#ifndef __GAMEUPDATER__
#define __GAMEUPDATER__

#include "InputListener.hpp"
#include "../Physics/World.hpp"
#include "../Graphics/Renderer.hpp"

class Window;

class Game
{
	public:
		Game(Window& window, Phy::World* world);
		virtual ~Game();
		
		float framerate(void) const  { return m_world->timestep(); }
		void setInputListener(InputListener* listener);
		void setRenderer(Graphics::Renderer* renderer);
		
		void handleInput(const sf::Event& event);
		void updateLogics(void);
		void render(float coef);
		
	protected:
		Phy::World* m_world;
		InputListener* m_inputListener;
		Graphics::Renderer* m_renderer;
		
		void initScene1(void);
		void initScene2(void);
		void initScene3(void);
};

#endif
