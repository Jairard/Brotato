#include <cstdio>
#include <iostream>
#include <cstring>

#include "../PotatoEngine/Core/Vector2.hpp"
#include "../PotatoEngine/Core/LibsHelpers.hpp"
#include "../Graphics.hpp"
#include "_ThickPointShape.hpp"

namespace Graphics
{
	const sf::Color DebugRenderer::TRANSPARENT_COLOR = sf::Color(0, 0, 0, 0);
	const char* DebugRenderer::DEFAULT_FONT_FILE = "../res/arial.ttf";
	
	DebugRenderer::DebugRenderer(sf::RenderTarget& window, const char* fontFile):
		b2Draw(),
		m_window(window),
		m_font()
	{
		m_isFontLoaded = m_font.loadFromFile(fontFile);
	}

	// Box2D Manipulators
	void DebugRenderer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
	{
		DrawPoint(b2v_2_sfv(p), size, b2c_2_sfc(color));
	}
	
	void DebugRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
	{
		DrawSegment(b2v_2_sfv(p1), b2v_2_sfv(p2), b2c_2_sfc(color));
	}
	
	void DebugRenderer::DrawTransform(const b2Transform& t)
	{
		// TODO: b2Transform -> sf::Transform conversion ?
		sf::Color xColor(255, 0, 0), yColor(0, 255, 0);
		const float32 k_axisScale = 0.4f;
		b2Vec2 p1 = t.p, p2;
		Graphics::SegmentShape segment(b2v_2_pv(p1), Pot::Vector2f());

		p2 = p1 + k_axisScale * t.q.GetXAxis();
		segment.setSecondPoint(b2v_2_pv(p2));
		segment.setColor(xColor);

		m_window.draw(segment);

		p2 = p1 + k_axisScale * t.q.GetYAxis();
		segment.setSecondPoint(b2v_2_pv(p2));
		segment.setColor(yColor);

		m_window.draw(segment);
	}
	
	void DebugRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::Vector2f* sfVertices = b2va_2_sfva(vertices, vertexCount);
		DrawPolygon(sfVertices, vertexCount, b2c_2_sfc(color));
		delete[] sfVertices;
	}
	
	void DebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::Vector2f* sfVertices = b2va_2_sfva(vertices, vertexCount);
		DrawPolygon(sfVertices, vertexCount, b2c_2_sfc(color));
		delete[] sfVertices;
	}
	
	void DebugRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
	{
		DrawCircle(b2v_2_sfv(center), radius, b2c_2_sfc(color));
	}
	
	void DebugRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
	{
		DrawSolidCircle(b2v_2_sfv(center), radius, b2v_2_sfv(axis), b2c_2_sfc(color));
	}
	
	void DebugRenderer::DrawAABB(b2AABB* aabb, const b2Color& color)
	{
		sf::Color c(color.r*255., color.g*255., color.b*255.);

		Pot::Vector2f p1(aabb->lowerBound.x, -aabb->lowerBound.y),
		              p2(aabb->upperBound.x, -aabb->lowerBound.y),
		              p3(aabb->upperBound.x, -aabb->upperBound.y),
		              p4(aabb->lowerBound.x, -aabb->upperBound.y);
		Graphics::SegmentShape s1(p1, p2), s2(p2, p3), s3(p3, p4), s4(p4, p1);

		s1.setColor(c);
		s2.setColor(c);
		s3.setColor(c);
		s4.setColor(c);

		m_window.draw(s1);
		m_window.draw(s2);
		m_window.draw(s3);
		m_window.draw(s4);
	}
	
	void DebugRenderer::DrawString(int x, int y, const b2Color& color, const char* string, ...)
	{
		va_list arg;
		va_start(arg, string);
		vDrawString(x, y, string, arg, b2c_2_sfc(color));
		va_end(arg);
	}
	
	sf::Vector2f* DebugRenderer::b2va_2_sfva(const b2Vec2* points, int32 pointCount) const
	{
		sf::Vector2f* res = new sf::Vector2f[pointCount];
		
		for (int32 i = 0; i < pointCount; ++i)
			res[i] = b2v_2_sfv(points[i]);
		
		return res;
	}
	
	// SFML manipulators
	void DebugRenderer::DrawPoint(const sf::Vector2f& p, float32 size, const sf::Color& color)
	{
		ThickPointShape point(&m_window, p);

		point.setColor(color);
		point.setThickness(size);

		m_window.draw(point);
	}
	
	void DebugRenderer::DrawSegment(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color)
	{
		Graphics::SegmentShape segment(p1, p2);
		segment.setColor(color);
		m_window.draw(segment);
	}
	
	void DebugRenderer::DrawTransform(const sf::Transform& t)
	{
		sf::Color xColor(255, 0, 0), yColor(0, 255, 0);
		const float32 k_axisScale = 0.4f;
		sf::Vector2f center(0.f, 0.f), xPoint(1.f, 0.f), yPoint(0.f, 1.f);
		sf::Vector2f xAxis = t.transformPoint(xPoint), yAxis = t.transformPoint(yPoint);
		
		DrawSegment(center, center + k_axisScale * xAxis, xColor);
		DrawSegment(center, center + k_axisScale * yAxis, yColor);
	}
	
	void DebugRenderer::DrawPolygon(const sf::Vector2f* vertices, int32 vertexCount, const sf::Color& color)
	{
		for (int32 i = 0; i < vertexCount; ++i)
		{
			int32 j = (i == 0) ? vertexCount-1 : i-1;
			DrawSegment(vertices[i], vertices[j], color);
		}
	}
	
	void DebugRenderer::DrawSolidPolygon(const sf::Vector2f* vertices, int32 vertexCount, const sf::Color& color)
	{
		sf::Color fillColor(color.r * 0.5f, color.g * 0.5f, color.b * 0.5f, 255.f * 0.5f);
		sf::ConvexShape poly(vertexCount);

		// Inside
		poly.setFillColor(fillColor);

		for (int32 i=0; i<vertexCount; i++)
			poly.setPoint(i, vertices[i]);

		m_window.draw(poly);

		// Contour
		DrawPolygon(vertices, vertexCount, color);
	}
	
	void DebugRenderer::DrawCircle(const sf::Vector2f& center, float32 radius, const sf::Color& color)
	{
		const int32 vertexCount = 32;
		sf::Vector2f* vertices = new sf::Vector2f[vertexCount];
		float32 theta = 0.0f;
		const float32 inc = 2.0f * b2_pi/(float32)vertexCount;

		for (int32 i = 0; i < vertexCount; ++i)
		{
			vertices[i] = center + radius * sf::Vector2f(cosf(theta), sinf(theta));
			theta += inc;
		}

		DrawPolygon(vertices, vertexCount, color);

		delete[] vertices;
	}
	
	void DebugRenderer::DrawSolidCircle(const sf::Vector2f& center, float32 radius, const sf::Vector2f& axis, const sf::Color& color)
	{
		/* circle */
		const int32 vertexCount = 32;
		sf::Vector2f* vertices = new sf::Vector2f[vertexCount];
		float32 theta = 0.0f;
		const float32 inc = 2.0f * b2_pi/(float32)vertexCount;

		for (int32 i = 0; i < vertexCount; ++i)
		{
			vertices[i] = center + radius * sf::Vector2f(cosf(theta), sinf(theta));
			theta += inc;
		}

		/* axis */
		sf::Vector2f p2 = center + radius * axis;

		/* rendering */
		DrawSolidPolygon(vertices, vertexCount, color);
		DrawSegment(center, p2, color);
		
		delete[] vertices;
	}
	
	void DebugRenderer::DrawAABB(const sf::FloatRect& aabb, const sf::Color& color)
	{
		const int32 vertexCount = 4;
		sf::Vector2f vertices[vertexCount];
				
		vertices[0] = sf::Vector2f(aabb.left             , aabb.top              ),
		vertices[1] = sf::Vector2f(aabb.left + aabb.width, aabb.top              ),
		vertices[2] = sf::Vector2f(aabb.left + aabb.width, aabb.top + aabb.height),
		vertices[3] = sf::Vector2f(aabb.left             , aabb.top + aabb.height);
		
		DrawPolygon(vertices, vertexCount, color);
	}
	
	void DebugRenderer::DrawString(int x, int y, const sf::Color& color, const char* string, ...)
	{
		va_list arg;
		va_start(arg, string);
		vDrawString(x, y, string, arg, color);
		va_end(arg);
	}
	
	void DebugRenderer::vDrawString(int x, int y, const char* string, va_list arg, const sf::Color& color)
	{
		if (!m_isFontLoaded)
			return;
		
		char buffer[512];
		vsprintf(buffer, string, arg);

		sf::FloatRect viewport = m_window.getView().getViewport();
		sf::Vector2u sfWindowSize = m_window.getSize();
		Pot::Vector2f windowSize(sfWindowSize.x, sfWindowSize.y);
		const float realX = viewport.left*windowSize.x + x*viewport.width;
		const float realY = viewport.top*windowSize.y + y*viewport.height;
		const float yRatio = 0.5 * m_window.getView().getSize().y / (float)m_window.getSize().y;
		sf::Text text;

		text.setFont(m_font);
		text.setString(buffer);
		text.setPosition(m_window.mapPixelToCoords(sf::Vector2i(realX, realY)));
		text.setCharacterSize(30);
		text.setScale(sf::Vector2f(yRatio, yRatio));
		text.setColor(color);

		m_window.draw(text);
	}
	
	void DebugRenderer::DrawString(int x, int y, const char* string, ...)
	{
		va_list arg;
		va_start(arg, string);
		vDrawString(x, y, string, arg);
		va_end(arg);
	}
}
