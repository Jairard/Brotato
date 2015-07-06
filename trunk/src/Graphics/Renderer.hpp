#ifndef __WINDOWS_GRAPHICSUPDATER__
#define __WINDOWS_GRAPHICSUPDATER__

#include <list>
#include "../Graphics/Entity.hpp"

class Window;

namespace Graphics
{
	class Renderer
	{
		public:
			Renderer(Window& window);
			virtual ~Renderer();
			
			void addEntity(Entity* entity);
			void drawGrid(void);
			void drawAxes(void);
			
			virtual void render(float coef);
			
		protected:
			std::list<Entity*> m_entities;
			Window& m_window;
	};
}

#endif
