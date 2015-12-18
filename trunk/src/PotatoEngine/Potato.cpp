#include "stdafx.h"
#include "Potato.hpp"

#include <assert.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Core/Tools.hpp"
#include "Debug/Renderer.hpp"
#include "Debug/Logger.hpp"
#include "Stem.hpp"
#include "Cell.hpp"
//#include "PotatoDNA.hpp"
#include "RenderCell.hpp"

namespace Pot
{

using Debug::Logger;

// TODO: regroup all reserved names here (mother potato, unnamed)
const std::string Potato::c_deadPotatoName = "__deadPotato__";

Potato::Potato():
	//m_organismImpl(),
	m_stem(nullptr),
	m_name(c_deadPotatoName),
	m_parent(nullptr),
	m_children(),
	m_worldTransform(),
	m_invWorldTransform(),
	m_localTransform(),
	m_invLocalTransform(),
	m_cells()/*,
	m_DNAs()*/
{
	initialize();
}

void Potato::initialize(const std::string& name, Stem* stem, Potato* parent)
{
	//ASSERT_DEBUG(m_organismImpl.DNACount() == 0);
	ASSERT_DEBUG(m_parent == nullptr);
	ASSERT_DEBUG(m_stem == nullptr);
	// TODO: check why this asserts
	//ASSERT_DEBUG(m_name == c_deadPotatoName);
	ASSERT_DEBUG(m_children.empty());
	ASSERT_DEBUG(m_cells.empty());
	//ASSERT_DEBUG(m_DNAs.empty());

	m_stem = stem;
	m_name = name;
	m_parent = parent;
	m_worldTransform = Transform();
	m_worldTransform.recomputeIFN();
	m_localTransform = Transform();
	m_localTransform.recomputeIFN();
}

void Potato::shutdown()
{
	m_parent = nullptr;
	m_stem = nullptr;
	m_name = c_deadPotatoName;

	m_children.clear();

	for (std::vector<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); ++it)
		delete *it;
	m_cells.clear();

	//m_organismImpl.onOrganismDeath();
	//onOrganismDeath();
	//m_DNAs.clear();
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

Potato* Potato::childPtr(size_t i)
{
	ASSERT_RELEASE(i < childCount());
	
	Potato* child = m_children[i];
	ASSERT_DEBUG(child != nullptr);
	
	return child;
}

const Potato* Potato::childPtr(size_t i) const
{
	ASSERT_RELEASE(i < childCount());
	
	const Potato* child = m_children[i];
	ASSERT_DEBUG(child != nullptr);
	
	return child;
}

Transform& Potato::localTransform()
{
	m_stem->ensureIntegrityIFN(this);
	ASSERT_DEBUG(!m_localTransform.isRotten());
	return m_localTransform;
}

const Transform& Potato::localTransform() const
{
	m_stem->ensureIntegrityIFN(this);
	ASSERT_DEBUG(!m_localTransform.isRotten());
	return m_localTransform;
}

Transform& Potato::worldTransform()
{
	m_stem->ensureIntegrityIFN(this);
	// TOOD: remove this assert ?
	ASSERT_DEBUG(!m_worldTransform.isRotten());
	return m_worldTransform;
}

const Transform& Potato::worldTransform() const
{
	m_stem->ensureIntegrityIFN(this);
	// TOOD: remove this assert ?
	ASSERT_DEBUG(!m_worldTransform.isRotten());
	return m_worldTransform;
}

const Transform& Potato::localToWorldTransform() const
{
	return worldTransform();
}

const Transform& Potato::worldToLocalTransform() const
{
	m_stem->ensureIntegrityIFN(this);
	ASSERT_DEBUG(!m_invWorldTransform.isRotten());
	return m_invWorldTransform;
}

const Transform& Potato::localToParentTransform() const
{
	return localTransform();
}

const Transform& Potato::parentToLocalTransform() const
{
	m_stem->ensureIntegrityIFN(this);
	ASSERT_DEBUG(!m_invLocalTransform.isRotten());
	return m_invLocalTransform;
}

/*
void Potato::registerDNA(PotatoDNA* dna) const
{
	ASSERT_DEBUG(dna != nullptr);
	Logger::log(Logger::CWarning, "registering %d", dna);
	m_DNAs.push_back(dna);
}

void Potato::unregisterDNA(PotatoDNA* dna) const
{
	ASSERT_DEBUG(dna != nullptr);
	Logger::log(Logger::CWarning, "unregistering %d", dna);

	for (std::vector<PotatoDNA*>::iterator it = m_DNAs.begin(); it != m_DNAs.end(); ++it)
	{
		if (dna == *it)
		{
			m_DNAs.erase(it);
			return;
		}
	}

	ASSERT_NOT_REACHED();
}

void Potato::onOrganismDeath()
{
	for (std::vector<PotatoDNA*>::iterator it = m_DNAs.begin(); it != m_DNAs.end(); ++it)
		(*it)->onOrganismDeath(this);
}
*/

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

void Potato::removeCell(const Cell* cell)
{
	for (std::vector<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); ++it)
	{
		if (cell == *it)
		{
			m_cells.erase(it);
			return;
		}
	}

	ASSERT_NOT_REACHED();
}

void Potato::update()
{
	for (std::vector<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); ++it)
		(*it)->update();
}

void Potato::render(float elapsedTime)
{
	POT_UNUSED(elapsedTime);
	
	RenderCell* renderer = fetchCellIFP<RenderCell>();
	if (renderer != nullptr)
		renderer->render();
}

void Potato::debugRender(Debug::Renderer& renderer) const
{
	// debugRender() is not handled by the potato itself
	// but each cell can have its own rendering method
	for (std::vector<Cell*>::const_iterator it = m_cells.begin(); it != m_cells.end(); ++it)
		(*it)->debugRender(renderer);
}

}
