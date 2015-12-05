#ifndef __POT_CELLDNA__
#define __POT_CELLDNA__

#include "Core/Tools.hpp"
#include "Debug/assert.hpp"
#include "Debug/Logger.hpp"
#include "DNACollector.hpp"
#include "BaseDNA.hpp"

namespace Pot
{

using Debug::Logger;

template <typename OrganismType>
class DNA: public BaseDNA
{
	friend class DNACollector;

	private:
		DNA();

		void selfRegister();

	public:
		DNA(const OrganismType* organism);
		// We have to redefine the copy constructor because else the default
		// one would be called over the template version (it'd be more specialized)
		DNA(const DNA<OrganismType>& other);
		template <typename ExtOrganismType>
		DNA(const DNA<ExtOrganismType>& other);
		~DNA();

		bool isValid() const;

		template <typename ExtOrganismType>
		void operator=(const DNA<ExtOrganismType>& other);
		void operator=(const OrganismType* cell);
		OrganismType* operator->();

		const OrganismType* typedOrganism() const; // Private

	public:
		static DNA<OrganismType> Invalid;
};

template <typename OrganismType>
bool DNA<OrganismType>::isValid() const
{
	return organism() != nullptr;
}

template<typename OrganismType>
DNA<OrganismType> DNA<OrganismType>::Invalid = DNA<OrganismType>(nullptr);

template <typename OrganismType>
DNA<OrganismType>::DNA(): BaseDNA()
{
}

template <typename OrganismType>
DNA<OrganismType>::DNA(const OrganismType* organism):
	BaseDNA()
{
	ASSERT_RELEASE(organism != nullptr);
	setOrganism(organism);
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
	UNUSED(organism);
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
