#ifndef __POT_CORE_TRANSFORM__
#define __POT_CORE_TRANSFORM__

#include <SFML/Graphics/Transform.hpp>
#include "Stainable.hpp"
#include "Vector2.hpp"
#include "ClassHelpers.hpp"
#include "AARect.hpp"
#include "Rect.hpp"

namespace Pot
{

namespace TransformOrder
{
	enum Type
	{
		ROTATION_SCALE_TRANSLATION,
		ROTATION_TRANSLATION_SCALE,
		SCALE_ROTATION_TRANSLATION,
		SCALE_TRANSLATION_ROTATION,
		TRANSLATION_ROTATION_SCALE,
		TRANSLATION_SCALE_ROTATION
	};
}

class Stem;
class Potato;

class Transform
{
	friend class Stem;
	friend class Potato;

	public:
		Transform(TransformOrder::Type type = TransformOrder::SCALE_ROTATION_TRANSLATION);
		Transform(const Transform& other);

	public:
		// Position manipulators
		void setPosition(float x, float y);
		void setPosition(const Vector2f& position);
		void move(float offsetX, float offsetY);
		void move(const Vector2f& offset);
		
		// Rotation manipulators
		void setRotation(float angle);
		void rotate(float angle);
		
		// Scale manipulators
		void setScale(float factorX, float factorY);
		void setScale(const Vector2f& scale);
		void scale(float factorX, float factorY);
		void scale(const Vector2f& factor);
		
		// Transformation order manipulators
		void setOrder(TransformOrder::Type order);
		const char* order_str() const;
		
		// Transformation manipulators
		const sf::Transform& SFMLTransform() const;
		Vector2f transformPoint(float x, float y) const;
		Vector2f transformPoint(const Vector2f& point) const;
		Rect transformRect(const AARect& rect) const;
		Rect transformRect(const Rect& rect) const;
		
		// Operators
		Transform operator*(const Transform& other) const;
		Transform& operator*=(const Transform& other);
		Vector2f operator*(const Vector2f& point);
		Rect operator*(const AARect& rect);
		Rect operator*(const Rect& rect);
		
		// Misc
		Transform inverse() const;
		void recomputeIFN() const;
		void log(const char* tag) const;
		
		// Accessors
		CONST_REF_ACCESSOR(Vector2f, position);
		SIMPLE_CONST_ACCESSOR(float, rotation);
		CONST_REF_ACCESSOR(Vector2f, scale);
		SIMPLE_CONST_ACCESSOR(TransformOrder::Type, order);
		
	private:
		// Stainable proxies
		void soil()           { m_transform.soil(); }
		void wash()           { m_transform.wash(); }
		bool isRotten() const { return m_transform.isRotten(); }
		
		void computeTransform() const;
		TransformOrder::Type inverseOrder() const;
	
	private:
		static const unsigned int c_matrixSize;
		
		TransformOrder::Type m_order;
		Vector2f m_position;
		float m_rotation;
		Vector2f m_scale;
		mutable Stainable<sf::Transform> m_transform;
};

}

#endif
