#ifndef __RENDER_COMPONENT__
#define __RENDER_COMPONENT__

#include <list>
#include <SFML/Graphics.hpp>
#include "../Core/Component.hpp"

namespace Graphics
{
	class GeometryComponent;
	
	class RenderComponent: public Component
	{
		public:
			RenderComponent(sf::RenderTarget& window);
			virtual ~RenderComponent() {}
			
			virtual void init(void);
			
		protected:
			virtual void render(const sf::Transformable& transform) { UNUSED(transform); }//= 0;
			
		private:
			virtual void onUpdate(float interpolationCoef);
			virtual void onLogicsUpdate(void);
			
		protected:
			GeometryComponent* m_geometry;
			sf::RenderTarget& m_target;
			sf::RenderStates m_states;
			
		private:
			sf::Transformable m_lastTransform, m_delta;
	};
}

#endif
