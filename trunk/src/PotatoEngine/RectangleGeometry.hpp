#ifndef __POT_RECTANGLEGEOMETRY__
#define __POT_RECTANGLEGEOMETRY__

#include <Core/ClassHelpers.hpp>
#include <Core/Vector2.hpp>
#include <GeometryCell.hpp>

namespace Pot
{

class Potato;

class RectangleGeometry: public GeometryCell
{
	friend class Potato;
	
	protected:
		RectangleGeometry(Potato* potato);
		IMPL_VIRTUAL_DESTRUCTOR(RectangleGeometry);
		
		CONST_REF_ACCESSOR(Vector2f, size);
		
	public:
		void setSize(const Vector2f& size);
		
	protected:
		virtual void updateLocalAABB();
		
	protected:
		Vector2f m_size;
};

}

#endif
