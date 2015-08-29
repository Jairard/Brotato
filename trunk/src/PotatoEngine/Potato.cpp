#include "Potato.hpp"

#include <assert.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Core/Tools.hpp"
#include "Debug/Renderer.hpp"
#include "Debug/Logger.hpp"
#include "Stem.hpp"
#include "Cell.hpp"
#include "RenderCell.hpp"

namespace Pot
{

using Debug::Logger;

Potato::Potato()
{
	initialize();
}

void Potato::initialize(const std::string& name, Stem* stem, Potato* parent)
{
	m_stem = stem;
	m_name = name;
	m_parent = parent;
	m_children.clear();
	m_worldTransform = Transform();
	m_worldTransform.recomputeIFN();
	m_localTransform = Transform();
	m_localTransform.recomputeIFN();
	m_cells.clear();
}

void Potato::shutdown()
{
	for (std::list<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); ++it)
		delete *it;
	m_cells.clear();
}

void Potato::removeChild(const Potato* child)
{
	ASSERT_DEBUG(child != nullptr);
	
	std::vector<Potato*>::iterator it;
	
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		if (*it == child)
		{
			m_children.erase(it);
			return;
		}
	}
	
	ASSERT_NOT_REACHED();
}

void Potato::addChild(Potato* child)
{
	ASSERT_DEBUG(child != nullptr);
	m_children.push_back(child);
}

Potato* Potato::child(unsigned int i)
{
	ASSERT_RELEASE(i < childCount());
	
	Potato* child = m_children[i];
	ASSERT_DEBUG(child != nullptr);
	
	return m_children[i];
}

const Potato* Potato::child(unsigned int i) const
{
	ASSERT_RELEASE(i < childCount());
	
	const Potato* child = m_children[i];
	ASSERT_DEBUG(child != nullptr);
	
	return m_children[i];
}

Transform& Potato::localTransform()
{
	m_stem->ensureIntegrityIFN(this);
	ASSERT_DEBUG(!m_localTransform.isRotten());
	return m_localTransform;
}

const Transform& Potato::localTransform_const()
{
	m_stem->ensureIntegrityIFN(this);
	assert(!m_localTransform.isRotten());
	return m_localTransform;
}

Transform& Potato::worldTransform()
{
	m_stem->ensureIntegrityIFN(this);
	// TOOD: remove this assert ?
	ASSERT_DEBUG(!m_worldTransform.isRotten());
	return m_worldTransform;
}

const Transform& Potato::worldTransform_const()
{
	m_stem->ensureIntegrityIFN(this);
	assert(!m_worldTransform.isRotten());
	return m_worldTransform;
}

const Transform& Potato::localToWorldTransform()
{
	return worldTransform_const();
}

const Transform& Potato::worldToLocalTransform()
{
	m_stem->ensureIntegrityIFN(this);
	ASSERT_DEBUG(!m_invWorldTransform.isRotten());
	return m_invWorldTransform;
}

const Transform& Potato::localToParentTransform()
{
	return localTransform_const();
}

const Transform& Potato::parentToLocalTransform()
{
	m_stem->ensureIntegrityIFN(this);
	ASSERT_DEBUG(!m_invLocalTransform.isRotten());
	return m_invLocalTransform;
}

/*
void Potato::addCell(Cell* cell)
{
	m_cells.push_back(cell);
}
//*/

/*
template<typename CellT>
CellT* Potato::addCell()
{
	CellT* cell = new CellT(this);
	m_cells.push_back(cell);
	return cell;
}
//*/

/*
template<typename CellT, typename... ArgsT>
CellT* Potato::addCell(ArgsT... args)
{
	CellT* cell = new CellT();
	cell->initializeCell(args...);
	m_cells.push_back(cell);
	return cell;
}
//*/

/*
template <typename T>
T* Potato::fetchCellIFP()
{
	for (std::list<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); it++)
		if (Tools::is<T>(*it))
			return (T*)*it;
	
	return nullptr;
}

template <typename T>
const T* Potato::fetchCellIFP() const
{
	for (std::list<Cell*>::const_iterator it = m_cells.begin(); it != m_cells.end(); it++)
		if (Tools::is<const T>(*it))
			return (const T*)*it;
	
	return nullptr;
}

template <typename T>
void Potato::fetchCells(std::list<T*>& outCells)
{
	for (std::list<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); it++)
		if (Tools::is<T>(*it))
			outCells.push_back((T*)*it);
}

template <typename T>
void Potato::fetchCells(std::list<const T*>& outCells) const
{
	for (std::list<Cell*>::const_iterator it = m_cells.begin(); it != m_cells.end(); it++)
		if (Tools::is<T>(*it))
			outCells.push_back((const T*)*it);
}
//*/

void Potato::update()
{
	for (std::list<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); it++)
		(*it)->update();
}

void Potato::render(float elapsedTime)
{
	UNUSED(elapsedTime);
	
	RenderCell* renderer = fetchCellIFP<RenderCell>();
	if (renderer != nullptr)
		renderer->render();
}

void Potato::debugRender(Debug::Renderer& renderer) const
{
	// debugRender() is not handled by the potato itself
	// but each cell can have its own rendering method
	for (std::list<Cell*>::const_iterator it = m_cells.begin(); it != m_cells.end(); ++it)
		(*it)->debugRender(renderer);
}

}
