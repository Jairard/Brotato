#ifndef __GEOMETRYCELL__
#define __GEOMETRYCELL__

#include <SFML/Graphics.hpp>
#include "Cell.hpp"

namespace Pot
{

class Potato;

class GeometryCell: public Cell
{
	friend class Potato;
	
	protected:
		GeometryCell(Potato* potato);
	public:
		virtual ~GeometryCell() {}
	
	public:
		virtual void update() {}
	
		const sf::VertexArray& vertices() const { return m_array; }
		const sf::FloatRect& aabb() const       { return m_aabb; }
		void setColor(const sf::Color& color);
		
	protected:
		virtual void updateAABB();
	
	protected:
		sf::VertexArray m_array;
		sf::FloatRect m_aabb;
};

}

#endif
