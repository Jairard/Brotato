#include "PotatoDNA.hpp"
#include "Debug/assert.hpp"
#include "Debug/Logger.hpp"
#include "Potato.hpp"

namespace Pot
{

using Debug::Logger;

PotatoDNA::PotatoDNA(Potato* potato):
	m_potato(nullptr)
{
	ASSERT_DEBUG(potato != nullptr);
	m_potato = potato;
	m_potato->registerDNA(this);
}

PotatoDNA::PotatoDNA(const PotatoDNA &other):
	m_potato(other.m_potato)
{
	if (m_potato != nullptr)
		m_potato->registerDNA(this);
}

PotatoDNA::~PotatoDNA()
{
	if (m_potato != nullptr)
		m_potato->unregisterDNA(this);
}

void PotatoDNA::onPotatoShutdown(const Potato* potato)
{
	ASSERT_DEBUG(potato == m_potato);
	m_potato = nullptr;
}

void PotatoDNA::operator=(const PotatoDNA& other)
{
	if (isValid())
		m_potato->unregisterDNA(this);

	m_potato = other.m_potato;
	if (other.isValid())
		m_potato->registerDNA(this);
}

void PotatoDNA::operator=(const Potato* potato)
{
	UNUSED(potato);
	ASSERT_NOT_REACHED();
}

Potato* PotatoDNA::operator->()
{
	ASSERT_RELEASE(isValid());
	return m_potato;
}

}
