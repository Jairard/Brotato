#ifndef __POT_GEOMETRYCELL__
#define __POT_GEOMETRYCELL__

#include <SFML/Graphics.hpp>
#include <Core/AARect.hpp>
#include <Core/ClassHelpers.hpp>
#include <Core/Rect.hpp>
#include <Cell.hpp>

namespace Pot
{

class Potato;
namespace Debug
{
	class Renderer;
}

class GeometryCell: public Cell
{
	friend class Potato;
	
	protected:
		GeometryCell(Potato* potato, sf::PrimitiveType primitiveType = sf::Points, size_t vertexCount = 1);
		
	public:
		IMPL_VIRTUAL_DESTRUCTOR(GeometryCell);
	
	public:
		virtual void update() {}
		virtual void debugRender(Debug::Renderer& renderer) const;
		void updateAABBs();
		
		void setColor(const sf::Color& color);
		CONST_REF_ACCESSOR_WITH_NAME(sf::VertexArray, array, vertices);
		CONST_REF_ACCESSOR(AARect, worldAABB);
		CONST_REF_ACCESSOR(AARect, localAABB);
		CONST_REF_ACCESSOR(Rect, localAABBInWorldSpace);
	public:
		
	protected:
		virtual void updateLocalAABB();
		virtual void updateWorldAABB();
		
	private:
		void updateLocalAABBInWorldSpace();
	
	protected:
		sf::VertexArray m_array;
		AARect m_worldAABB;
		AARect m_localAABB;
		Rect m_localAABBInWorldSpace;
};

}

#endif
