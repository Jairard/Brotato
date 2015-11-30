#ifndef __POT_POTATO__
#define __POT_POTATO__

#include <assert.h>
#include <string>
#include <vector>
#include <list>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Core/Transform.hpp"
#include "Core/Tools.hpp"
#include "Core/Stainable.hpp"
#include "Core/ClassHelpers.hpp"
#include "Stem.hpp"
#include "Cell.hpp"
#include "DNA.hpp"

namespace Pot
{

namespace Debug
{
	class Renderer;
}

template <typename T> class Pool;
class Cell;

//DEFINE_DNA_TYPE(Potato);

class Potato//: public DefaultOrganismImpl<Potato>
{
	friend class Stem;
	template <typename T> friend class Pool;

	public:
		REF_ACCESSOR(std::string, name);
		CONST_REF_ACCESSOR(std::string, name);
		SAFE_ACCESSOR_WITH_NAME(Stem*, stem, sStem);
		SAFE_CONST_ACCESSOR_WITH_NAME(Stem*, stem, sStem);

	public:
		// Hierarchy manipulators
		/*
		PotatoDNA parent() const        { return PotatoDNA(m_parent); }
		unsigned int childCount() const { return m_children.size(); }
		PotatoDNA child(unsigned int i);
		/*/
		Potato* parent() const        { return m_parent; }
		unsigned int childCount() const { return m_children.size(); }
		Potato* child(unsigned int i);
		//*/

		// Transform manipulators
		Transform& localTransform();
		const Transform& localTransform() const;
		Transform& worldTransform();
		const Transform& worldTransform() const;

		const Transform& localToWorldTransform() const;
		const Transform& worldToLocalTransform() const;
		const Transform& localToParentTransform() const;
		const Transform& parentToLocalTransform() const;

		// OrganismDNA<Potato> implementation
		/*
		void registerDNA(PotatoDNA* dna) const;
		void unregisterDNA(PotatoDNA* dna) const;
		void onOrganismDeath();
		// TODO: only in test mode
		size_t DNACount() const { return m_DNAs.size(); }
		*/

		// Cells manipulators
		//void addCell(Cell* cell);
		//*
		// TODO: return OrganismDNA<CellType>
		template<typename CellType>
		CellType* addCell()
		{
			static_assert(Tools::is<CellType, Cell>(), "This cell does not inherit form ::Pot::Cell");
			CellType* cell = new CellType(this);
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

		// TODO: return OrganismDNA<CellType>
		template <typename CellType> CellType* fetchCellIFP()
		{
			for (std::vector<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); it++)
				if (Tools::is<CellType>(*it))
					return (CellType*)*it;
			
			return nullptr;
		}
		
		// TODO: return OrganismDNA<CellType>
		template <typename CellType> const CellType* fetchCellIFP() const
		{
			for (std::vector<Cell*>::const_iterator it = m_cells.begin(); it != m_cells.end(); it++)
				if (Tools::is<CellType>(*it))
					return (const CellType*)*it;
			
			return nullptr;
		}

		// TODO: std::list<OrganismDNA<CellType>>& outCells
		template <typename CellType> void fetchCells(std::list<CellType*>& outCells)
		{
			for (std::vector<Cell*>::iterator it = m_cells.begin(); it != m_cells.end(); it++)
				if (Tools::is<CellType>(*it))
					outCells.push_back((CellType*)*it);
		}

		// TODO: std::list<OrganismDNA<CellType>>& outCells
		template <typename CellType> void fetchCells(std::list<const CellType*>& outCells) const
		{
			for (std::vector<Cell*>::const_iterator it = m_cells.begin(); it != m_cells.end(); it++)
				if (Tools::is<CellType>(*it))
					outCells.push_back((const CellType*)*it);
		}

		// TODO: CCellDNA cell;
		void removeCell(const Cell* cell);

	private:
		Potato();
		// TODO: inherit from NonCopyable ?
		Potato(const Potato& other) { UNUSED(other); ASSERT_NOT_REACHED(); }

		void initialize(const std::string& name = "__unnamed__", Stem* stem = nullptr, Potato* parent = nullptr);
		void shutdown();

		void addChild(Potato* child);
		void removeChild(const Potato* child);
		Potato* childPtr(unsigned int i);
		const Potato* childPtr(unsigned int i) const;

		void update();
		void render(float elapsedTime);
		void debugRender(Debug::Renderer& renderer) const;

	private:
		static const std::string c_deadPotatoName;

		//DefaultOrganismImpl<Potato> m_organismImpl;
		Stem* m_stem;
		std::string m_name;
		Potato* m_parent;
		std::vector<Potato*> m_children;
		mutable Transform m_worldTransform, m_invWorldTransform;   // local -> world, world -> local
		mutable Transform m_localTransform, m_invLocalTransform;   // local -> parent, parent -> local
		std::vector<Cell*> m_cells;
		//mutable std::vector<PotatoDNA*> m_DNAs;
};

}

#endif
