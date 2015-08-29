#include "Transform.hpp"

#include <iostream>
#include "../Debug/Logger.hpp"
#include "LibsHelpers.hpp"
#include "Math.hpp"

namespace Pot
{

const unsigned int Transform::c_matrixSize = 16;

Transform::Transform(TransformOrder::Type order):
	m_order(order),
	m_position(0.f, 0.f),
	m_rotation(0.f),
	m_scale(1.f, 1.f),
	m_transform()
{
	m_transform.soil();
}

Transform::Transform(const Transform& other):
	m_order(other.m_order),
	m_position(other.m_position),
	m_rotation(other.m_rotation),
	m_scale(other.m_scale),
	m_transform()
{
	m_transform.soil();
}

// Position manipulators
void Transform::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
	m_transform.soil();
}

void Transform::setPosition(const Vector2f& position)
{
	setPosition(position.x, position.y);
}

void Transform::move(float offsetX, float offsetY)
{
	setPosition(m_position.x + offsetX, m_position.y + offsetY);
}

void Transform::move(const Vector2f& offset)
{
	move(offset.x, offset.y);
}

// Rotation manipulators
void Transform::setRotation(float angle)
{
	m_rotation = angle;
	m_transform.soil();
}

void Transform::rotate(float angle)
{
	setRotation(m_rotation + angle);
}

// Scale manipulators
void Transform::setScale(float factorX, float factorY)
{
	m_scale.x = factorX;
	m_scale.y = factorY;
	m_transform.soil();
}

void Transform::setScale(const Vector2f& scale)
{
	setScale(scale.x, scale.y);
}

void Transform::scale(float factorX, float factorY)
{
	setScale(m_scale.x * factorX, m_scale.y * factorY);
}

void Transform::scale(const Vector2f& factor)
{
	scale(factor.x, factor.y);
}

// Transformation order manipulators
void Transform::setOrder(TransformOrder::Type order)
{
	m_order = order;
	m_transform.soil();
}

const char* Transform::order_str() const
{
	switch (m_order)
	{
		case Pot::TransformOrder::ROTATION_SCALE_TRANSLATION:
			return "ROTATION_SCALE_TRANSLATION";
		case Pot::TransformOrder::ROTATION_TRANSLATION_SCALE:
			return "ROTATION_TRANSLATION_SCALE";
		case Pot::TransformOrder::SCALE_ROTATION_TRANSLATION:
			return "SCALE_ROTATION_TRANSLATION";
		case Pot::TransformOrder::SCALE_TRANSLATION_ROTATION:
			return "SCALE_TRANSLATION_ROTATION";
		case Pot::TransformOrder::TRANSLATION_ROTATION_SCALE:
			return "TRANSLATION_ROTATION_SCALE";
		case Pot::TransformOrder::TRANSLATION_SCALE_ROTATION:
			return "TRANSLATION_SCALE_ROTATION";
		default:
			ASSERT_NOT_REACHED_MSG("TransformOrder");
			return "INVALID_TRANSFORM_ORDER";
	}
}

// Transformation manipulators
const sf::Transform& Transform::SFMLTransform() const
{
	recomputeIFN();
	return m_transform.const_object();
}

Vector2f Transform::transformPoint(float x, float y) const
{
	return sfv_2_pv(SFMLTransform().transformPoint(x, y));
}

Vector2f Transform::transformPoint(const Vector2f& p) const
{
	return transformPoint(p.x, p.y);
}

Rect Transform::transformRect(const AARect& rect) const
{
	return transformRect(paar_2_pr(rect));
}

Rect Transform::transformRect(const Rect& rect) const
{
	Rect res;
	
	for (unsigned int i = 0; i < Rect::c_pointCount; ++i)
		res.points[i] = transformPoint(rect.points[i]);
	
	return res;
}

// Operators
Transform Transform::operator*(const Transform& other) const
{
	Transform res(m_order);
	res.move(position() + other.position());
	res.rotate(rotation() + other.rotation());
	
	const Vector2f& leftScale = scale();
	const Vector2f& rightScale = other.scale();
	res.scale(leftScale.x * rightScale.x, leftScale.y * rightScale.y);
	
	return res;
}

Transform& Transform::operator*=(const Transform& other)
{
	move(other.position());
	rotate(other.rotation());
	scale(other.scale());
	
	return *this;
}

Vector2f Transform::operator*(const Vector2f& point)
{
	return transformPoint(point);
}

Rect Transform::operator*(const AARect& rect)
{
	return transformRect(rect);
}

Rect Transform::operator*(const Rect& rect)
{
	return transformRect(rect);
}

// Misc
Transform Transform::inverse() const
{
	Transform t(inverseOrder());
	t.setPosition(-m_position.x, -m_position.y);
	t.setRotation(-m_rotation);
	t.setScale(1.f / m_scale.x, 1.f / m_scale.y);
	return t;
}

void Transform::recomputeIFN() const
{
	if (m_transform.isRotten())
	{
		computeTransform();
		m_transform.wash();
	}
	
	ASSERT_DEBUG(!m_transform.isRotten());
}

void Transform::log(const char* tag) const
{
	Debug::Logger::log(tag, "Transform: isRotten(%d), position(%f, %f), rotation(%f), scale(%f, %f)",
		m_transform.isRotten(), m_position.x, m_position.y, m_rotation, m_scale.x, m_scale.y);
}

// Private manipulators
void Transform::computeTransform() const
{
	const float angle  = Math::deg2rad(m_rotation);
	const float cosine = static_cast<float>(std::cos(angle));
	const float sine   = static_cast<float>(std::sin(angle));
	const float sxc    = m_scale.x * cosine;
	const float syc    = m_scale.y * cosine;
	const float sxs    = m_scale.x * sine;
	const float sys    = m_scale.y * sine;
	float tx, ty;
	
	switch (m_order)
	{
		case TransformOrder::ROTATION_SCALE_TRANSLATION:
			tx = m_position.x;
			ty = m_position.y;
			m_transform.object() = sf::Transform(sxc, -sxs, tx,
			                                     sys,  syc, ty,
			                                     0.f,  0.f, 1.f);
			break;
			
		case TransformOrder::ROTATION_TRANSLATION_SCALE:
			tx = m_position.x * m_scale.x;
			ty = m_position.y * m_scale.y;
			m_transform.object() = sf::Transform(sxc, -sxs, tx,
			                                     sys,  syc, ty,
			                                     0.f,  0.f, 1.f);
			break;
			
		case TransformOrder::SCALE_ROTATION_TRANSLATION:
			tx = m_position.x;
			ty = m_position.y;
			m_transform.object() = sf::Transform(sxc, -sys, tx,
			                                     sxs,  syc, ty,
			                                     0.f,  0.f, 1.f);
			break;
			
		case TransformOrder::SCALE_TRANSLATION_ROTATION:
			tx = m_position.x * cosine - m_position.y * sine;
			ty = m_position.x * sine   + m_position.y * cosine;
			m_transform.object() = sf::Transform(sxc, -sys, tx,
			                                     sxs,  syc, ty,
			                                     0.f,  0.f, 1.f);
			break;
			
		case TransformOrder::TRANSLATION_ROTATION_SCALE:
			tx = m_position.x * sxc - m_position.y * sxs;
			ty = m_position.x * sys + m_position.y * syc;
			m_transform.object() = sf::Transform(sxc, -sxs, tx,
			                                     sys,  syc, ty,
			                                     0.f,  0.f, 1.f);
			break;
			
		case TransformOrder::TRANSLATION_SCALE_ROTATION:
			tx = m_position.x * sxc - m_position.y * sys;
			ty = m_position.x * sxs + m_position.y * syc;
			m_transform.object() = sf::Transform(sxc, -sxs, tx,
			                                     sys,  syc, ty,
			                                     0.f,  0.f, 1.f);
			break;
			
		default:
			ASSERT_NOT_REACHED_MSG("TransformOrder");
			break;
	}
}

TransformOrder::Type Transform::inverseOrder() const
{
	switch (m_order)
	{
		case TransformOrder::ROTATION_SCALE_TRANSLATION:
			return TransformOrder::TRANSLATION_SCALE_ROTATION;
		case TransformOrder::ROTATION_TRANSLATION_SCALE:
			return TransformOrder::SCALE_TRANSLATION_ROTATION;
		case TransformOrder::SCALE_ROTATION_TRANSLATION:
			return TransformOrder::TRANSLATION_ROTATION_SCALE;
		case TransformOrder::SCALE_TRANSLATION_ROTATION:
			return TransformOrder::ROTATION_TRANSLATION_SCALE;
		case TransformOrder::TRANSLATION_ROTATION_SCALE:
			return TransformOrder::SCALE_ROTATION_TRANSLATION;
		case TransformOrder::TRANSLATION_SCALE_ROTATION:
			return TransformOrder::ROTATION_SCALE_TRANSLATION;
		default:
			ASSERT_NOT_REACHED_MSG("TransformOrder");
			break;
	}
}

}
