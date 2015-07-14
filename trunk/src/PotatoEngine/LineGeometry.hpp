#ifndef __LINEGEOMETRY__
#define __LINEGEOMETRY__

#include "GeometryCell.hpp"
#include <SFML/System/Vector2.hpp>
#include "../Core/Vector2.hpp"
#include "Core/LibsHelpers.hpp"
#include "Core/ClassHelpers.hpp"

namespace Pot
{

class LineGeometry : public GeometryCell
{
	friend class Potato;
	
	protected:
		LineGeometry(Potato* potato);
		IMPL_VIRTUAL_DESTRUCTOR(LineGeometry);
		
		virtual void update();
	
	public:
		const Vector2f point1() const { return sfv_2_pv(m_array[0].position); }
		const Vector2f point2() const { return sfv_2_pv(m_array[1].position); }
		void setPoint1(const Vector2f& coords);
		void setPoint1(const sf::Vector2f& coords);
		void setPoint2(const Vector2f& coords);
		void setPoint2(const sf::Vector2f& coords);
		void setPoints(const Vector2f& p1, const Vector2f& p2);
		void setPoints(const sf::Vector2f& p1, const sf::Vector2f& p2);
		
	protected:
		virtual void updateLocalAABB();
};

}

#endif
