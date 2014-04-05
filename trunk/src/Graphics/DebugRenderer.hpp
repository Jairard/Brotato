#ifndef __GRAPHICS_DEBUGRENDERER__
#define __GRAPHICS_DEBUGRENDERER__

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Box2D/Collision/b2Collision.h>

namespace Graphics
{	
	class DebugRenderer: public b2Draw
	{
		public:
			DebugRenderer(sf::RenderWindow& window);
	
			void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
			void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
			void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
			void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
			void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
			void DrawTransform(const b2Transform& xf);
		    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
		    void DrawString(int x, int y, const char* string, ...); 
			void DrawString(int x, int y, const b2Color& color, const char* string, ...);
			void vDrawString(int x, int y, const char* string, va_list arg, const b2Color& color=b2Color(1., 1., 1.));
		    void DrawAABB(b2AABB* aabb, const b2Color& color);
	
		protected:
			static const sf::Color TRANSPARENT_COLOR;
			static const char* FONT_FILE;
	
			sf::RenderWindow& _window;
			sf::Font _font;
			bool _isFontLoaded;
	};
}

#endif
