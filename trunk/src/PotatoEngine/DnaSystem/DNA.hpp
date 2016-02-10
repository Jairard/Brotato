#ifndef __POT_CELLDNA__
#define __POT_CELLDNA__

#include <Core/Tools.hpp>
#include <Debug/assert.hpp>
#include <Debug/Logger.hpp>
#include <Dnasystem/BaseDNA.hpp>
#include <Dnasystem/BaseOrganism.hpp>
#include <Dnasystem/DNACollector.hpp>

namespace Pot
{

using Debug::Logger;
class BaseOrganism;

template <typename OrganismType>
class DNA: public BaseDNA
{
	static_assert(POT_STATIC_IS(OrganismType, BaseOrganism), "This organism does not inherit from ::Pot::BaseOrganim");
	friend class DNACollector;

	private:
		DNA();

		void selfRegister();

	public:
		DNA(const BaseOrganism* organism);
		// We have to redefine the copy constructor because else the default
		// one would be called over the template version (it'd be more specialized)
		DNA(const DNA<OrganismType>& other);
		template <typename ExtOrganismType>
		DNA(const DNA<ExtOrganismType>& other);
		~DNA();

		template <typename ExtOrganismType>
		void operator=(const DNA<ExtOrganismType>& other);
		void operator=(const OrganismType* cell);
		OrganismType* operator->();

		const OrganismType* typedOrganism() const; // Private

	public:
		static DNA<OrganismType> Invalid;
};

template<typename OrganismType>
DNA<OrganismType> DNA<OrganismType>::Invalid = DNA<OrganismType>(nullptr);

template <typename OrganismType>
DNA<OrganismType>::DNA(): BaseDNA()
{
}

template <typename OrganismType>
DNA<OrganismType>::DNA(const BaseOrganism* organism):
	BaseDNA()
{
	ASSERT_DEBUG(organism != nullptr);
	// Force cast to ensure it's the same type
	setOrganism(Tools::as<const OrganismType>(organism));
	selfRegister();
}

template <typename OrganismType>
DNA<OrganismType>::DNA(const DNA<OrganismType>& other): BaseDNA()
{
	setOrganism(other.organism());
	selfRegister();
}

template <typename OrganismType> template <typename ExtOrganismType>
DNA<OrganismType>::DNA(const DNA<ExtOrganismType>& other): BaseDNA()
{
	setOrganism(Tools::as<const OrganismType>(other.organism()));
	selfRegister();
}

template <typename OrganismType>
DNA<OrganismType>::~DNA()
{
	selfUnregister();
}

template <typename OrganismType> template <typename ExtOrganismType>
void DNA<OrganismType>::operator=(const DNA<ExtOrganismType>& other)
{
	selfUnregister();
	setOrganism(Tools::as<const OrganismType>(other.typedOrganism()));
	selfRegister();
}

template <typename OrganismType>
void DNA<OrganismType>::operator=(const OrganismType* organism)
{
	POT_UNUSED(organism);
	ASSERT_NOT_REACHED();
}

template <typename OrganismType>
OrganismType* DNA<OrganismType>::operator->()
{
	ASSERT_RELEASE(isValid());
	return typedOrganism();
}

template <typename OrganismType>
void DNA<OrganismType>::selfRegister()
{
	BaseDNA::selfRegister(typeid(OrganismType));
}

template <typename OrganismType>
const OrganismType* DNA<OrganismType>::typedOrganism() const
{
	return organism<const OrganismType>();
}

}

#endif
