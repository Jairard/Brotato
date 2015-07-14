#ifndef __RECTANGLEGEOMETRY__
#define __RECTANGLEGEOMETRY__

#include "GeometryCell.hpp"
#include "../Core/Vector2.hpp"
#include "Core/ClassHelpers.hpp"

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
