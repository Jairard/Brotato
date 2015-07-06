#ifndef __POTATO__
#define __POTATO__

#include <assert.h>
#include <string>
#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../Core/Tools.hpp"
#include "../Core/Stainable.hpp"
#include "../Core/Pool.hpp"
#include "Stem.hpp"

#include "Cell.hpp"

namespace Pot
{

namespace Debug
{
	class Renderer;
}

class Cell;

class Potato
{
	friend class Stem;
	// Does not work. Goal: set Potato() as private
	template <typename T> friend class Pool;
		
	public:
		std::string& name()                     { return m_name; }
		const std::string& name() const         { return m_name; }
		Stem* sStem()                           { assert(m_stem != nullptr); return m_stem; }
		const Stem* sStem() const               { assert(m_stem != nullptr); return m_stem; }
		
		// Hierarchy manipulators
		const Potato* sParent() const                   { assert(m_parent != nullptr); return m_parent; }
		const std::vector<Potato*>& children() const    { return m_children; }
		unsigned int childCount() const                 { return m_children.size(); }
		Potato* child(unsigned int i);
		const Potato* child(unsigned int i) const;
		
		// Transform manipulators
		sf::Transformable& localTransformable()             { return m_localTransform.object(); }
		const sf::Transformable& localTransformable() const { return m_localTransform.const_object(); }
		const sf::Transform& localTransform() const         { return m_localTransform.const_object().getTransform(); }
		sf::Transform& worldTransform();
		const sf::Transform& worldTransform_const();
		
		// Cells manipulators
		//void addCell(Cell* cell);
		//*
		template<typename CellT>
		CellT* addCell()
		{
			CellT* cell = new CellT(this);
			m_cells.push_back(cell);
			return cell;
		}
		/*/
		template<typename CellT, typename... ArgsT>
		CellT* addCell(ArgsT... args)
		{
			CellT* cell = new CellT(this);
			//initializeCell(cell, args...);
			cell->initialize(args...);
			m_cells.push_back(cell);
			return cell;
		}
		//*/
		
		template <typename T> T* fetchCellIFP()
		{
			for (std::list<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); it++)
				if (Tools::is<T>(*it))
					return (T*)*it;
			
			return nullptr;
		}
		
		template <typename T> const T* fetchCellIFP() const
		{
			for (std::list<Cell*>::const_iterator it = m_cells.begin(); it != m_cells.end(); it++)
				if (Tools::is<const T>(*it))
					return (const T*)*it;
			
			return nullptr;
		}
		
		template <typename T> void fetchCells(std::list<T*>& outCells)
		{
			for (std::list<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); it++)
				if (Tools::is<T>(*it))
					outCells.push_back((T*)*it);
		}
		
		template <typename T> void fetchCells(std::list<const T*>& outCells) const
		{
			for (std::list<Cell*>::const_iterator it = m_cells.begin(); it != m_cells.end(); it++)
				if (Tools::is<T>(*it))
					outCells.push_back((const T*)*it);
		}
		
		Potato();
	private:
		Potato(const Potato& toCopy) { UNUSED(toCopy); assert(false); }
		
		void initialize(const std::string& name = "__unnamed__", Stem* stem = nullptr, Potato* parent = nullptr);
		void shutdown();
		void addChild(Potato* child);
		void removeChild(const Potato* child);
		
		void update();
		void render(float elapsedTime);
		void debugRender(Debug::Renderer& renderer) const;
		
		Potato* sParent()                                         { assert(m_parent != nullptr); return m_parent; }
		sf::Transform& worldTransform_noCheck()                   { return m_worldTransform.object(); }
		const sf::Transform& worldTransform_const_noCheck() const { return m_worldTransform.const_object(); }
		
	private:
		Stem* m_stem;
		std::string m_name;
		Potato* m_parent;
		std::vector<Potato*> m_children;
		Stainable<sf::Transform> m_worldTransform;
		Stainable<sf::Transformable> m_localTransform;
		std::list<Cell*> m_cells;
};

}

#endif
