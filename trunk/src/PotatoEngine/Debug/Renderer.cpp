#include "../stdafx.h"
#include <cstdio>
#include <iostream>
#include <cstring>

#include "Renderer.hpp"
#include "../Core/LibsHelpers.hpp"
#include "assert.hpp"

namespace Pot
{
namespace Debug
{
const sf::Color Renderer::TRANSPARENT_COLOR = sf::Color(0, 0, 0, 0);
# ifdef POT_COMPILER_MSC
const char* Renderer::DEFAULT_FONT_FILE = "arial.ttf";
#else
const char* Renderer::DEFAULT_FONT_FILE = "../res/arial.ttf";
#endif

Renderer::Renderer(sf::RenderTarget& window, const char* fontFile):
	b2Draw(),
	m_window(window),
	m_font(),
	m_isFontLoaded(false),
	m_isLocked(false)
{
	m_isFontLoaded = m_font.loadFromFile(fontFile);
}

// Box2D Manipulators
void Renderer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	DrawPoint(b2v_2_sfv(p), size, b2c_2_sfc(color));
}

void Renderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	DrawSegment(b2v_2_sfv(p1), b2v_2_sfv(p2), b2c_2_sfc(color));
}

void Renderer::DrawTransform(const b2Transform& t)
{
	ASSERT_DEBUG(!m_isLocked);

	// TODO: b2Transform -> sf::Transform conversion ?
	b2Color xColor(1.f, 0.f, 0.f), yColor(0.f, 1.f, 0.f);
	const float32 k_axisScale = 0.4f;
	b2Vec2 p1 = t.p;
	b2Vec2 px = p1 + k_axisScale * t.q.GetXAxis();
	b2Vec2 py = p1 + k_axisScale * t.q.GetYAxis();

	DrawSegment(p1, px, xColor);
	DrawSegment(p1, py, yColor);
}

void Renderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::Vector2f* sfVertices = b2va_2_sfva(vertices, vertexCount);
	DrawPolygon(sfVertices, static_cast<size_t>(vertexCount), b2c_2_sfc(color));
	delete[] sfVertices;
}

void Renderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::Vector2f* sfVertices = b2va_2_sfva(vertices, vertexCount);
	DrawPolygon(sfVertices, static_cast<size_t>(vertexCount), b2c_2_sfc(color));
	delete[] sfVertices;
}

void Renderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	DrawCircle(b2v_2_sfv(center), radius, b2c_2_sfc(color));
}

void Renderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	DrawSolidCircle(b2v_2_sfv(center), radius, b2v_2_sfv(axis), b2c_2_sfc(color));
}

void Renderer::DrawAABB(b2AABB* aabb, const b2Color& color)
{
	ASSERT_DEBUG(!m_isLocked);

	// TODO: test with rect
	/*
	AARect rect(aabb->lowerBound.x,
				aabb->lowerBound.y,
				aabb->upperBound.x - aabb->lowerBound.x,
				aabb->upperBound.y - aabb->lowerBound.y);

	DrawRect(rect, b2c_2_sfc(color));
	/*/
	sf::Color c = b2c_2_sfc(color);
	Vector2f p1(aabb->lowerBound.x, -aabb->lowerBound.y),
			 p2(aabb->upperBound.x, -aabb->lowerBound.y),
			 p3(aabb->upperBound.x, -aabb->upperBound.y),
			 p4(aabb->lowerBound.x, -aabb->upperBound.y);

	DrawSegment(p1, p2, c);
	DrawSegment(p2, p3, c);
	DrawSegment(p3, p4, c);
	DrawSegment(p4, p1, c);
	//*/
}

void Renderer::DrawString(int x, int y, const b2Color& color, const char* string, ...)
{
	va_list arg;
	va_start(arg, string);
	vDrawString(x, y, string, arg, b2c_2_sfc(color));
	va_end(arg);
}

sf::Vector2f* Renderer::b2va_2_sfva(const b2Vec2* vertices, size_t vertexCount) const
{
	sf::Vector2f* res = new sf::Vector2f[vertexCount];

	for (size_t i = 0; i < vertexCount; ++i)
		res[i] = b2v_2_sfv(vertices[i]);

	return res;
}

// Potato manipulators
void Renderer::DrawPoint(const Vector2f& p, float32 size, const sf::Color& color)
{
	DrawPoint(pv_2_sfv(p), size, color);
}

void Renderer::DrawSegment(const Vector2f& p1, const Vector2f& p2, const sf::Color& color)
{
	DrawSegment(pv_2_sfv(p1), pv_2_sfv(p2), color);
}

void Renderer::DrawRect(const AARect& aabb, const sf::Color& color)
{
	DrawAABB(paar_2_sfr(aabb), color);
}

void Renderer::DrawRect(const Rect& rect, const sf::Color& color)
{
	DrawRect(rect.points, color);
}

void Renderer::DrawRect(const Vector2f& p1, const Vector2f& p2, const Vector2f& p3, const Vector2f& p4, const sf::Color& color)
{
	DrawRect(pv_2_sfv(p1), pv_2_sfv(p2), pv_2_sfv(p3), pv_2_sfv(p4), color);
}

void Renderer::DrawRect(const Vector2f* vertices, const sf::Color& color)
{
	sf::Vector2f* sfVertices = pva_2_sfva(vertices, 4);
	DrawRect(sfVertices, color);
	delete[] sfVertices;
}

void Renderer::DrawPolygon(const Vector2f* vertices, size_t vertexCount, const sf::Color& color)
{
	sf::Vector2f* sfVertices = pva_2_sfva(vertices, vertexCount);
	DrawPolygon(sfVertices, vertexCount, color);
	delete[] sfVertices;
}

void Renderer::DrawSolidPolygon(const Vector2f* vertices, size_t vertexCount, const sf::Color& color)
{
	sf::Vector2f* sfVertices = pva_2_sfva(vertices, vertexCount);
	DrawSolidPolygon(sfVertices, vertexCount, color);
	delete[] sfVertices;
}

void Renderer::DrawCircle(const Vector2f& center, float32 radius, const sf::Color& color)
{
	DrawCircle(pv_2_sfv(center), radius, color);
}

void Renderer::DrawSolidCircle(const Vector2f& center, float32 radius, const Vector2f& axis, const sf::Color& color)
{
	DrawSolidCircle(pv_2_sfv(center), radius, pv_2_sfv(axis), color);
}

sf::Vector2f* Renderer::pva_2_sfva(const Vector2f* vertices, size_t vertexCount) const
{
	sf::Vector2f* res = new sf::Vector2f[vertexCount];

	for (size_t i = 0; i < vertexCount; ++i)
		res[i] = pv_2_sfv(vertices[i]);

	return res;
}

// SFML manipulators
void Renderer::DrawPoint(const sf::Vector2f& p, float32 size, const sf::Color& color)
{
	ASSERT_DEBUG(!m_isLocked);

	// TODO: test
	const sf::Vector2u& windowSize = m_window.getSize();
	const sf::Vector2f& viewSize = m_window.getView().getSize();
	const float xRatio = viewSize.x / (float)windowSize.x;
	const float yRatio = viewSize.y / (float)windowSize.y;

	AARect rect(sfv_2_pv(p), Vector2f(size * xRatio, size * yRatio));
	DrawRect(rect, color);
}

void Renderer::DrawSegment(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color)
{
	ASSERT_DEBUG(!m_isLocked);

	sf::VertexArray array(sf::Lines, 2);
	array[0].position = p1;
	array[0].color = color;
	array[1].position = p2;
	array[1].color = color;

	m_window.draw(array);
}

void Renderer::DrawTransform(const sf::Transformable& t)
{
	DrawTransform(t.getTransform());
}

void Renderer::DrawTransform(const sf::Transform& t)
{
	sf::Color xColor = sf::Color::Red, yColor = sf::Color::Green;
	sf::Vector2f center(0.f, 0.f), xPoint(1.f, 0.f), yPoint(0.f, 1.f);
	sf::Vector2f xAxis = t.transformPoint(xPoint), yAxis = t.transformPoint(yPoint);

	DrawSegment(center, center + xAxis, xColor);
	DrawSegment(center, center + yAxis, yColor);
}

void Renderer::DrawRect(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4, const sf::Color& color)
{
	sf::Vector2f* vertices = new sf::Vector2f[4];
	vertices[0] = p1;
	vertices[1] = p2;
	vertices[2] = p3;
	vertices[3] = p4;

	DrawRect(vertices, color);

	delete[] vertices;
}

void Renderer::DrawRect(const sf::Vector2f* vertices, const sf::Color& color)
{
	DrawPolygon(vertices, 4, color);
}

void Renderer::DrawPolygon(const sf::Vector2f* vertices, size_t vertexCount, const sf::Color& color)
{
	for (size_t i = 0; i < vertexCount; ++i)
	{
		size_t j = (i == 0) ? vertexCount-1 : i-1;
		DrawSegment(vertices[i], vertices[j], color);
	}
}

void Renderer::DrawSolidPolygon(const sf::Vector2f* vertices, size_t vertexCount, const sf::Color& color)
{
	ASSERT_DEBUG(!m_isLocked);

	sf::Color fillColor(static_cast<sf::Uint8>(color.r * 0.5f),
						static_cast<sf::Uint8>(color.g * 0.5f),
						static_cast<sf::Uint8>(color.b * 0.5f),
						static_cast<sf::Uint8>(  255.f * 0.5f));
	sf::ConvexShape poly(vertexCount);

	// Inside
	poly.setFillColor(fillColor);

	for (size_t i=0; i<vertexCount; i++)
		poly.setPoint(i, vertices[i]);

	m_window.draw(poly);

	// Contour
	DrawPolygon(vertices, vertexCount, color);
}

void Renderer::DrawCircle(const sf::Vector2f& center, float32 radius, const sf::Color& color)
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

void Renderer::DrawSolidCircle(const sf::Vector2f& center, float32 radius, const sf::Vector2f& axis, const sf::Color& color)
{
	/* circle */
	const size_t vertexCount = 32;
	sf::Vector2f* vertices = new sf::Vector2f[vertexCount];
	float32 theta = 0.0f;
	const float32 inc = 2.0f * b2_pi/(float32)vertexCount;

	for (size_t i = 0; i < vertexCount; ++i)
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

void Renderer::DrawAABB(const sf::FloatRect& aabb, const sf::Color& color)
{
	const int32 vertexCount = 4;
	sf::Vector2f* vertices = new sf::Vector2f[vertexCount];

	vertices[0] = sf::Vector2f(aabb.left             , aabb.top              ),
	vertices[1] = sf::Vector2f(aabb.left + aabb.width, aabb.top              ),
	vertices[2] = sf::Vector2f(aabb.left + aabb.width, aabb.top + aabb.height),
	vertices[3] = sf::Vector2f(aabb.left             , aabb.top + aabb.height);

	DrawPolygon(vertices, vertexCount, color);
	delete[] vertices;
}

void Renderer::DrawString(int x, int y, const sf::Color& color, const char* string, ...)
{
	va_list arg;
	va_start(arg, string);
	vDrawString(x, y, string, arg, color);
	va_end(arg);
}

void Renderer::vDrawString(int x, int y, const char* string, va_list arg, const sf::Color& color)
{
	ASSERT_DEBUG(!m_isLocked);

	if (!m_isFontLoaded)
		return;

	const size_t bufferSize = 512;
	char buffer[bufferSize];
	vsnprintf(buffer, bufferSize, string, arg);

	sf::FloatRect viewport = m_window.getView().getViewport();
	sf::Vector2u sfWindowSize = m_window.getSize();
	Vector2f windowSize(static_cast<float>(sfWindowSize.x), static_cast<float>(sfWindowSize.y));
	const float realX = viewport.left*windowSize.x + x*viewport.width;
	const float realY = viewport.top*windowSize.y + y*viewport.height;
	const float yRatio = 0.5f * m_window.getView().getSize().y / (float)m_window.getSize().y;
	sf::Text text;

	text.setFont(m_font);
	text.setString(buffer);
	text.setPosition(m_window.mapPixelToCoords(sf::Vector2i(static_cast<int>(realX), static_cast<int>(realY))));
	text.setCharacterSize(30);
	text.setScale(sf::Vector2f(yRatio, yRatio));
	text.setColor(color);

	m_window.draw(text);
}

void Renderer::DrawString(int x, int y, const char* string, ...)
{
	va_list arg;
	va_start(arg, string);
	vDrawString(x, y, string, arg);
	va_end(arg);
}

void Renderer::lock()
{
	m_isLocked = true;
}

void Renderer::unlock()
{
	m_isLocked = false;
}

}
}
