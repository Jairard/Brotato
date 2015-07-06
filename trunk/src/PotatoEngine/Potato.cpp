#include "Potato.hpp"

#include <assert.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../Core/Tools.hpp"
#include "Debug/Renderer.hpp"
#include "Stem.hpp"
#include "Cell.hpp"
#include "RenderCell.hpp"

namespace Pot
{

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
	m_worldTransform = sf::Transform();
	m_localTransform = sf::Transformable();
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
	assert(child != nullptr);
	
	std::vector<Potato*>::iterator it;
	
	for (it = m_children.begin(); it != m_children.end(); ++it)
	{
		if (*it == child)
		{
			m_children.erase(it);
			return;
		}
	}
	
	assert(false);
}

void Potato::addChild(Potato* child)
{
	assert(child != nullptr);
	m_children.push_back(child);
}

Potato* Potato::child(unsigned int i)
{
	assert(i >= 0);
	assert(i < childCount());
	
	Potato* child = m_children[i];
	assert(child != nullptr);
	
	return m_children[i];
}

const Potato* Potato::child(unsigned int i) const
{
	assert(i >= 0);
	assert(i < childCount());
	
	const Potato* child = m_children[i];
	assert(child != nullptr);
	
	return m_children[i];
}

sf::Transform& Potato::worldTransform()
{
	m_stem->ensureIntegrityAsc(this);
	return m_worldTransform.object();
}

const sf::Transform& Potato::worldTransform_const()
{
	m_stem-> ensureIntegrityAsc(this);
	return m_worldTransform.const_object();
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
	
	// Render potato using render / geometry / interpolation cells
	RenderCell* renderer = fetchCellIFP<RenderCell>();
	if (renderer == nullptr)
		return;
	
	sf::RectangleShape rectangle;
	
	if (m_name == "red rectangle")
	{
		rectangle.setSize(sf::Vector2f(100, 50));
		rectangle.setFillColor(sf::Color::Red);
		//localTransformable().rotate(0.5f * elapsedTime);
	}
	else if (m_name == "green rectangle")
	{
		rectangle.setSize(sf::Vector2f(100, 50));
		rectangle.setFillColor(sf::Color::Green);
		//localTransformable().move(0.1f * elapsedTime, 0.1f * elapsedTime);
	}
	else if (m_name == "potato 1.1.2" || m_name == "potato 1.1")
	{
		rectangle.setSize(sf::Vector2f(100, 50));
		rectangle.setOutlineColor(sf::Color::Blue);
		rectangle.setOutlineThickness(5);
		
		sf::FloatRect aabb = rectangle.getGlobalBounds();
		// transformRect returns the aabb of the transformed rect \o/
		aabb = m_worldTransform.const_object().transformRect(aabb);
		Debug::Renderer debugRenderer(*renderer->sTarget());
		//debugRenderer.DrawAABB(aabb, sf::Color::Red);
	}
	else
	{
		rectangle.setSize(sf::Vector2f(100, 50));
		rectangle.setOutlineColor(sf::Color::Blue);
		rectangle.setOutlineThickness(5);
		//rectangle.setPosition(150, 150);
	}
	
	/*
	sf::RenderStates states;
	states.transform = m_worldTransform.const_object();
	renderer->sTarget()->draw(rectangle, states);
	//*/
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
