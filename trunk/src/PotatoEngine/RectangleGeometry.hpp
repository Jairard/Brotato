#ifndef __RECTANGLEGEOMETRY__
#define __RECTANGLEGEOMETRY__

#include "GeometryCell.hpp"
#include "../Core/Vector2.hpp"

namespace Pot
{

class Potato;

class RectangleGeometry: public GeometryCell
{
	friend class Potato;
	
	protected:
		RectangleGeometry(Potato* potato);
	public:
		virtual ~RectangleGeometry() {}
		
		void setSize(const Vector2f& size);
		const Vector2f& size() const { return m_size; }
		
	protected:
		virtual void updateAABB();
		
	protected:
		Vector2f m_size;
};

}

#endif
