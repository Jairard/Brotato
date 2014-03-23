#ifndef __SEGMENT_SHAPE__
#define __SEGMENT_SHAPE__

#include <SFML/Graphics.hpp>

/*
class SegmentShape: public sf::Drawable, public sf::Transformable
{
	public:
		SegmentShape(const sf::Vector2f& p1=sf::Vector2f(), const sf::Vector2f& p2=sf::Vector2f());
		virtual ~SegmentShape() {}

		void setFirstPoint(const sf::Vector2f& p);
		void setSecondPoint(const sf::Vector2f& p);
		void setPoints(const sf::Vector2f& p1, const sf::Vector2f& p2);
		void setColor(const sf::Color& color);
		void setColor(const sf::Color& c1, const sf::Color& c2);

	protected:
		sf::VertexArray _array;

	private:
    	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class PointShape: public sf::Drawable, public sf::Transformable
{
	public:
		PointShape(const sf::Vector2f& p=sf::Vector2f());
		~PointShape() {}

		void setPosition(const sf::Vector2f& pos);
		void setColor(const sf::Color& color);

	protected:
		sf::Vertex _v;

	private:
    	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
//*/

class ThickPointShape: public sf::RectangleShape
{
	public:
		ThickPointShape(const sf::RenderWindow* window, const sf::Vector2f center=sf::Vector2f());
		~ThickPointShape() {}

		void setThickness(float thickness);
		void setColor(const sf::Color& color);

	protected:
		float _thickness;
		const sf::RenderWindow* _window;

	private:
    	void update(void);
};

#endif
