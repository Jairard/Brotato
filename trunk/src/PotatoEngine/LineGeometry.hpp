#ifndef __POT_LINEGEOMETRY__
#define __POT_LINEGEOMETRY__

#include <SFML/System/Vector2.hpp>
#include <Core/ClassHelpers.hpp>
#include <Core/LibsHelpers.hpp>
#include <Core/Vector2.hpp>
#include <GeometryCell.hpp>

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
		void setPoint2(const Vector2f& coords);
		void setPoints(const Vector2f& p1, const Vector2f& p2);
		
	protected:
		virtual void updateLocalAABB();
};

}

#endif
