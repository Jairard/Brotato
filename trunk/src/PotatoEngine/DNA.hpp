#ifndef __POT_CELLDNA__
#define __POT_CELLDNA__

#include "Core/Tools.hpp"
#include "Debug/assert.hpp"
#include "Debug/Logger.hpp" // TODO: remove
#include "DNACollector.hpp"

namespace Pot
{

//class DNACollector;
using Debug::Logger;

/*
template <typename OrganismType> class OrganismDNA;

template <typename OrganismType>
class IOrganism
{
	public:
		//typedef OrganismDNA<OrganismType> DNAType;

		virtual void registerDNA(OrganismDNA<OrganismType>* dna) = 0;
		virtual void unregisterDNA(OrganismDNA<OrganismType>* dna) = 0;
		virtual void onOrganismDeath() = 0;
		
};
*/

// DNA
template <typename OrganismType>
class DNA
{
	friend class DNACollector;
	//static_assert(Tools::is<OrganismType, IOrganism<OrganismType> >(), "You can't instanciate a DNA form a non-Organism object");
	//static_assert(std::is_assignable<O)

	private:
		DNA();

	public:
		DNA(OrganismType* organism);
		// We have to redefine the copy constructor because else the default
		// one would be called over the template version (it'd be more specialized)
		DNA(const DNA<OrganismType>& other);
		template <typename ExtOrganismType>
		DNA(const DNA<ExtOrganismType>& other);
		~DNA();
	
		bool isValid() const { return m_organism != nullptr; }
		void onOrganismDeath(const OrganismType* cell);

		template <typename ExtOrganismType>
		void operator=(const DNA<ExtOrganismType>& other);
		void operator=(OrganismType* cell);
		OrganismType* operator->();
	private:
		void selfRegister();
		void selfUnregister();

	private:
	public: // tmp
		OrganismType* m_organism;

	public:
		static DNA<OrganismType> Invalid;
};

template<typename OrganismType>
DNA<OrganismType> DNA<OrganismType>::Invalid = DNA<OrganismType>(nullptr);

template <typename OrganismType>
DNA<OrganismType>::DNA():
	m_organism(nullptr)
{
}

template <typename OrganismType>
DNA<OrganismType>::DNA(OrganismType* organism):
	m_organism(nullptr)
{
	ASSERT_RELEASE(organism != nullptr);
	m_organism = organism;
	selfRegister();
}

template <typename OrganismType>
DNA<OrganismType>::DNA(const DNA<OrganismType>& other):
	m_organism(other.m_organism)
{
	//if (isValid())
		selfRegister();
}

template <typename OrganismType> template <typename ExtOrganismType>
DNA<OrganismType>::DNA(const DNA<ExtOrganismType>& other):
	m_organism(nullptr)
{
	// TODO: test
	m_organism = Tools::as<OrganismType>(other.m_organism);
	if (other.isValid())
		selfRegister();
}

template <typename OrganismType>
DNA<OrganismType>::~DNA()
{
	//if (isValid())
		selfUnregister();
}

template <typename OrganismType> template <typename ExtOrganismType>
void DNA<OrganismType>::operator=(const DNA<ExtOrganismType>& other)
{
	Logger::log(Logger::CWarning, "= currentValid(%d), newValid(%d)", isValid(), other.isValid());
	//if (isValid())
		selfUnregister();

	m_organism = Tools::as<OrganismType>(other.m_organism);
	if (other.isValid())
		selfRegister();
}

template <typename OrganismType>
void DNA<OrganismType>::operator=(OrganismType* organism)
{
	UNUSED(organism);
	ASSERT_NOT_REACHED();
}

template <typename OrganismType>
OrganismType* DNA<OrganismType>::operator->()
{
	ASSERT_RELEASE(isValid());
	return m_organism;
}

template <typename OrganismType>
void DNA<OrganismType>::selfRegister()
{
	//ASSERT_DEBUG(isValid());
	DNACollector::instance().registerDNA(*this);
	//m_organism->registerDNA(this);
}

template <typename OrganismType>
void DNA<OrganismType>::selfUnregister()
{
	//ASSERT_DEBUG(isValid());
	DNACollector::instance().unregisterDNA(*this);
	//m_organism->unregisterDNA(this);
}

template <typename OrganismType>
void DNA<OrganismType>::onOrganismDeath(const OrganismType* organism)
{
	ASSERT_DEBUG(organism == m_organism);
	Logger::log(Logger::CWarning, "%u.onOrganismDeath(%u)", this, organism);
	m_organism = nullptr;
}

/*
template <typename OrganismType>
class DefaultOrganismImpl
{
	public:
		typedef DNA< DefaultOrganismImpl<OrganismType> > DNAType;
		//typedef DNA<OrganismType> DNAType;
		
		DefaultOrganismImpl(OrganismType* owner): m_owner(owner) {}
		virtual ~DefaultOrganismImpl();
		
		void registerDNA(DNAType* dna) const;
		void unregisterDNA(DNAType* dna) const;
		const OrganismType* owner() const { return m_owner; }
		
		void onOrganismDeath();
		// TODO: only in test mode
		size_t DNACount() const { return m_DNAs.size(); }

	private:
		DefaultOrganismImpl();

	private:
		OrganismType* m_owner;
		mutable std::vector<DNAType*> m_DNAs;
};

template <typename OrganismType>
void DefaultOrganismImpl<OrganismType>::registerDNA(DNAType* dna) const
{
	ASSERT_DEBUG(dna != nullptr);

#ifdef POT_DEBUG
	for (typename std::vector<DNAType*>::iterator it = m_DNAs.begin(); it != m_DNAs.end(); ++it)
		ASSERT_DEBUG_MSG(*it != dna, "This dna is already id the list");
#endif

	m_DNAs.push_back(dna);
	Logger::log(Logger::CWarning, "registered DNA %d, %d dnas in %d", dna, m_DNAs.size(), this);
}

template <typename OrganismType>
void DefaultOrganismImpl<OrganismType>::unregisterDNA(DNAType* dna) const
{
	ASSERT_DEBUG(dna != nullptr);

	for (typename std::vector<DNAType*>::iterator it = m_DNAs.begin(); it != m_DNAs.end(); ++it)
	{
		if (dna == *it)
		{
			m_DNAs.erase(it);
			Logger::log(Logger::CWarning, "unregistered DNA %d, %d dnas in %d", dna, m_DNAs.size(), this);
			return;
		}
	}

	ASSERT_NOT_REACHED();
}

template <typename OrganismType>
void DefaultOrganismImpl<OrganismType>::onOrganismDeath()
{
	Logger::log(Logger::CWarning, "%u is dying with %d dnas", this, m_DNAs.size());
	for (typename std::vector<DNAType*>::iterator it = m_DNAs.begin(); it != m_DNAs.end(); ++it)
		(*it)->onOrganismDeath(*//*static_cast<OrganismType*>*//*(this)); // Beurk
	
	m_DNAs.clear();
}

template <typename OrganismType>
DefaultOrganismImpl<OrganismType>::~DefaultOrganismImpl()
{
	Logger::log(Logger::CWarning, "Impl dst");
	onOrganismDeath();
	ASSERT_DEBUG(m_DNAs.empty());
}

// Misc
#define DEFINE_DNA_TYPES(className) \
	typedef ::Pot::DNA<className>        className##DNA; \
	typedef ::Pot::DNA<const className>  C##className##DNA;

// Defined here because of ciruclar dependencies
class Potato;
DEFINE_DNA_TYPES(Potato)
//typedef ::Pot::DNA< DefaultOrganismImpl<Potato> > PotatoDNA;

class Cell;
DEFINE_DNA_TYPES(Cell)
//*/

}

#endif
