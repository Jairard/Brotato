#ifndef __POT_DEBUG_RENDERER__
#define __POT_DEBUG_RENDERER__

#include <cstdarg>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Box2D/Collision/b2Collision.h>
#include "../Core/NonCopyable.hpp"
#include "../Core/Vector2.hpp"
#include "../Core/AARect.hpp"
#include "../Core/Rect.hpp"

namespace Pot
{
namespace Debug
{
	class Renderer: public b2Draw, public NonCopyable
	{
		public:
			Renderer(sf::RenderTarget& window, const char* fontFile = DEFAULT_FONT_FILE);

		// Box2D manipulators
		public:
			void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
			void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
			void DrawTransform(const b2Transform& t);
			void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
			void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
			void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
			void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
			void DrawAABB(b2AABB* aabb, const b2Color& color);
			void DrawString(int x, int y, const b2Color& color, const char* string, ...);
			
		private:
			sf::Vector2f* b2va_2_sfva(const b2Vec2* vertices, int32 vertexCount) const;
		
		// Potato maniipulators
		public:
			void DrawPoint(const Vector2f& p, float32 size, const sf::Color& color);
			void DrawSegment(const Vector2f& p1, const Vector2f& p2, const sf::Color& color);
			void DrawRect(const Rect& rect, const sf::Color& color);
			void DrawRect(const AARect& aabb, const sf::Color& color);
			void DrawRect(const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, const Vector2f& p4, const sf::Color& color);
			void DrawRect(const Vector2f* vertices, const sf::Color& color);
			void DrawPolygon(const Vector2f* vertices, int32 vertexCount, const sf::Color& color);
			void DrawSolidPolygon(const Vector2f* vertices, int32 vertexCount, const sf::Color& color);
			void DrawCircle(const Vector2f& center, float32 radius, const sf::Color& color);
			void DrawSolidCircle(const Vector2f& center, float32 radius, const Vector2f& axis, const sf::Color& color);
			
		private:
			sf::Vector2f* pva_2_sfva(const Vector2f* vertices, int32 vertexCount) const;
		
		// SFML manipulators
		public:
			void DrawPoint(const sf::Vector2f& p, float32 size, const sf::Color& color);
			void DrawSegment(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color);
			void DrawTransform(const sf::Transformable& t);
			void DrawTransform(const sf::Transform& t);
			void DrawRect(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4, const sf::Color& color);
			void DrawRect(const sf::Vector2f* vertices, const sf::Color& color);
			void DrawPolygon(const sf::Vector2f* vertices, int32 vertexCount, const sf::Color& color);
			void DrawSolidPolygon(const sf::Vector2f* vertices, int32 vertexCount, const sf::Color& color);
			void DrawCircle(const sf::Vector2f& center, float32 radius, const sf::Color& color);
			void DrawSolidCircle(const sf::Vector2f& center, float32 radius, const sf::Vector2f& axis, const sf::Color& color);
			void DrawAABB(const sf::FloatRect& aabb, const sf::Color& color);
			void DrawString(int x, int y, const sf::Color& color, const char* string, ...);
			void vDrawString(int x, int y, const char* string, va_list arg, const sf::Color& color=sf::Color(1., 1., 1.));
		
		// Common:
		public:
			void DrawString(int x, int y, const char* string, ...);
			void lock();
			void unlock();

		protected:
			static const sf::Color TRANSPARENT_COLOR;
			static const char* DEFAULT_FONT_FILE;

			sf::RenderTarget& m_window;
			sf::Font m_font;
			bool m_isFontLoaded, m_isLocked;
	};
}
}

#endif
