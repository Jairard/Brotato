#include <cstdio>
#include <iostream>
#include <cstdarg>
#include <cstring>

#include "vector2.hpp"
#include "shapes.hpp"
#include "render.hpp"

const sf::Color DebugRenderer::TRANSPARENT_COLOR = sf::Color(0, 0, 0, 0);
const char* DebugRenderer::FONT_FILE = "../res/arial.ttf";

DebugRenderer::DebugRenderer(sf::RenderWindow& window):
	_window(window),
	_font()
{
	_isFontLoaded = _font.loadFromFile(FONT_FILE);
}

void DebugRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::Color c(color.r*255., color.g*255., color.b*255.);

	for (int32 i=0; i<vertexCount; i++)
	{
		int32 j = (i == 0) ? vertexCount-1 : i-1;
		b2Vec2 p1(vertices[i]), p2(vertices[j]);
		SegmentShape segment(sf::Vector2f(p1.x, -p1.y), sf::Vector2f(p2.x, -p2.y));
		segment.setColor(c);
		_window.draw(segment);
	}
}

void DebugRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	sf::Color outlineColor(   color.r*255.,    color.g*255.,    color.b*255.),
	             fillColor(color.r*255./2., color.g*255./2., color.b*255./2., 255./2.);
	sf::ConvexShape poly(vertexCount);

	poly.setFillColor(fillColor);

	for (int32 i=0; i<vertexCount; i++)
		poly.setPoint(i, sf::Vector2f(vertices[i].x, -vertices[i].y));

	_window.draw(poly);

	for (int32 i=0; i<vertexCount; i++)
	{
		int32 j = (i == 0) ? vertexCount-1 : i-1;
		b2Vec2 p1(vertices[i]), p2(vertices[j]);
		SegmentShape segment(sf::Vector2f(p1.x, -p1.y), sf::Vector2f(p2.x, -p2.y));
		segment.setColor(outlineColor);
		_window.draw(segment);
	}
}

void DebugRenderer::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	const int32 vertexCount = 32;
	b2Vec2* vertices = new b2Vec2[vertexCount];
	float32 theta = 0.0f;
	const float32 inc = 2.0f * b2_pi/(float32)vertexCount;

	for (int32 i=0; i<vertexCount; ++i)
	{
		vertices[i] = center + radius * b2Vec2(cosf(theta), sinf(theta));
		theta += inc;
	}

	DrawPolygon(vertices, vertexCount, color);

	delete vertices;
}

void DebugRenderer::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	/* circle */
	sf::Color outlineColor(   color.r*255.,    color.g*255.,    color.b*255.),
	             fillColor(color.r*255./2., color.g*255./2., color.b*255./2., 255./2.);
	const int32 vertexCount = 32;
	b2Vec2* vertices = new b2Vec2[vertexCount];
	float32 theta = 0.0f;
	const float32 inc = 2.0f * b2_pi/(float32)vertexCount;

	for (int32 i=0; i<vertexCount; ++i)
	{
		vertices[i] = center + radius * b2Vec2(cosf(theta), sinf(theta));
		theta += inc;
	}

	/* axis */
	b2Vec2 p2 = center + radius * axis;
	SegmentShape segment(sf::Vector2f(center.x, -center.y), sf::Vector2f(p2.x, -p2.y));

	segment.setColor(outlineColor);

	/* rendering */
	DrawSolidPolygon(vertices, vertexCount, color);
	_window.draw(segment);

	delete vertices;
}

void DebugRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	sf::Color c(color.r*255., color.g*255., color.b*255.);
	sf::Vector2f v1(p1.x, -p1.y), v2(p2.x, -p2.y);
	SegmentShape segment(v1, v2);

	segment.setColor(c);
	_window.draw(segment);
}

void DebugRenderer::DrawTransform(const b2Transform& xf)
{
	sf::Color xColor(255, 0, 0), yColor(0, 255, 0);
	const float32 k_axisScale = 0.4f;
	b2Vec2 p1 = xf.p, p2;
	SegmentShape segment(sf::Vector2f(p1.x, -p1.y));

	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	segment.setSecondPoint(sf::Vector2f(p2.x, -p2.y));
	segment.setColor(xColor);

	_window.draw(segment);

	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	segment.setSecondPoint(sf::Vector2f(p2.x, -p2.y));
	segment.setColor(yColor);

	_window.draw(segment);
}

void DebugRenderer::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	B2_NOT_USED(size);

	sf::Color c(color.r*255., color.g*255., color.b*255.);
	ThickPointShape point(&_window, sf::Vector2f(p.x, -p.y));

	point.setColor(c);
	point.setThickness(size);

	_window.draw(point);
}

void DebugRenderer::DrawString(int x, int y, const char* string, ...)
{
	va_list arg;
	va_start(arg, string);
	vDrawString(x, y, string, arg);
	va_end(arg);
}

void DebugRenderer::DrawString(int x, int y, const b2Color& color, const char* string, ...)
{
	va_list arg;
	va_start(arg, string);
	vDrawString(x, y, string, arg, color);
	va_end(arg);
}

void DebugRenderer::vDrawString(int x, int y, const char* string, va_list arg, const b2Color& color)
{
	char buffer[512];
	vsprintf(buffer, string, arg);

	if (!_isFontLoaded)
		return;

	sf::Color c(color.r*255., color.g*255., color.b*255.);

	sf::FloatRect viewport = _window.getView().getViewport();
	sf::Vector2f windowSize(_window.getSize());
	float realX = viewport.left*windowSize.x + x*viewport.width,
	      realY = viewport.top*windowSize.y + y*viewport.height;

	float xRatio = 0.5 * _window.getView().getSize().x / (float)_window.getSize().x;
	float yRatio = 0.5 * _window.getView().getSize().y / (float)_window.getSize().y;
	sf::Text text;

	text.setFont(_font);
	text.setString(buffer);
	text.setPosition(_window.mapPixelToCoords(sf::Vector2i(realX, realY)));
	text.setCharacterSize(30);
	text.setScale(sf::Vector2f(yRatio, yRatio));
	text.setColor(c);

	_window.draw(text);
}

void DebugRenderer::DrawAABB(b2AABB* aabb, const b2Color& color)
{
	sf::Color c(color.r*255., color.g*255., color.b*255.);

	sf::Vector2f p1(aabb->lowerBound.x, -aabb->lowerBound.y),
	             p2(aabb->upperBound.x, -aabb->lowerBound.y),
	             p3(aabb->upperBound.x, -aabb->upperBound.y),
	             p4(aabb->lowerBound.x, -aabb->upperBound.y);
	SegmentShape s1(p1, p2), s2(p2, p3), s3(p3, p4), s4(p4, p1);

	s1.setColor(c);
	s2.setColor(c);
	s3.setColor(c);
	s4.setColor(c);

	_window.draw(s1);
	_window.draw(s2);
	_window.draw(s3);
	_window.draw(s4);
}
