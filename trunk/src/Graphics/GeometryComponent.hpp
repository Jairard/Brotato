#ifndef __GRAPHICS_GEOMETRYCOMPONENT__
#define __GRAPHICS_GEOMETRYCOMPONENT__

#include <SFML/Graphics.hpp>
#include "../Core.hpp"
#include "../Core/Component.hpp"

namespace Graphics
{
	class GeometryComponent : public Component
	{
		public:
			GeometryComponent(sf::PrimitiveType type, unsigned int vertexCount);
			virtual ~GeometryComponent();
			
			virtual void setColor(const sf::Color& color);
			virtual void init(void) {}
			virtual void onUpdate(float interpolationCoef) { UNUSED(interpolationCoef); }
			virtual void onLogicsUpdate(void) {}
			
			sf::VertexArray& vertices(void)  { return m_array; }
			
		protected:
			sf::VertexArray m_array;
	};
	
	class DummyGeo : public GeometryComponent
	{
		public:
			DummyGeo(sf::PrimitiveType type, unsigned int vertexCount):
				GeometryComponent(type, vertexCount)
			{}
	};
}

#endif
