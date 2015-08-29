#ifndef __POTATO__
#define __POTATO__

#include <assert.h>
#include <string>
#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Core/Transform.hpp"
#include "Core/Tools.hpp"
#include "Core/Stainable.hpp"
#include "Core/Pool.hpp"
#include "Core/ClassHelpers.hpp"
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
		REF_ACCESSOR(std::string, name);
		CONST_REF_ACCESSOR(std::string, name);
		SAFE_ACCESSOR_WITH_NAME(Stem*, stem, sStem);
		SAFE_CONST_ACCESSOR_WITH_NAME(Stem*, stem, sStem);
		
		// Hierarchy manipulators
		SAFE_CONST_ACCESSOR_WITH_NAME(Potato*, parent, sParent);
		CONST_REF_ACCESSOR(std::vector<Potato*>, children);
	public:
		unsigned int childCount() const                 { return m_children.size(); }
		Potato* child(unsigned int i);
		const Potato* child(unsigned int i) const;
		
		// Transform manipulators
		Transform& localTransform();
		const Transform& localTransform() const;
		Transform& worldTransform();
		const Transform& worldTransform() const;
		
		const Transform& localToWorldTransform() const;
		const Transform& worldToLocalTransform() const;
		const Transform& localToParentTransform() const;
		const Transform& parentToLocalTransform() const;
		
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
		// TODO: inherit from NonCopyable ?
		Potato(const Potato& other) { UNUSED(other); ASSERT_NOT_REACHED(); }
		
		void initialize(const std::string& name = "__unnamed__", Stem* stem = nullptr, Potato* parent = nullptr);
		void shutdown();
		void addChild(Potato* child);
		void removeChild(const Potato* child);
		
		void update();
		void render(float elapsedTime);
		void debugRender(Debug::Renderer& renderer) const;
		
	private:
		Stem* m_stem;
		std::string m_name;
		Potato* m_parent;
		std::vector<Potato*> m_children;
		mutable Transform m_worldTransform, m_invWorldTransform;   // local -> world, world -> local
		mutable Transform m_localTransform, m_invLocalTransform;   // local -> parent, parent -> local
		std::list<Cell*> m_cells;
};

}

#endif
