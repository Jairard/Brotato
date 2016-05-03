#ifndef __POT_BASE_DNA__
#define __POT_BASE_DNA__

#include <Core/Tools.hpp>
#include <Debug/assert.hpp>

namespace std
{
	class type_info;
}

namespace Pot { namespace DnaSystem
{

class BaseOrganism;
class Collector;

class BaseDNA
{
	friend class Collector;

	public:
		virtual ~BaseDNA();
		const BaseOrganism* organism() const;

		bool isValid() const;

	protected:
		BaseDNA();

		template <typename OrganismType>
		const OrganismType* organism() const;
		
		template <typename OrganismType>
		void setOrganism(const OrganismType* organism);

		void selfRegister(const std::type_info& organismType);
		void selfUnregister();
		void onOrganismDeath(const BaseOrganism* organism);

	private:
		const BaseOrganism* m_organism;
};

template <typename OrganismType>
const OrganismType* BaseDNA::organism() const
{
	return Tools::as<const OrganismType>(m_organism);
}

template <typename OrganismType>
void BaseDNA::setOrganism(const OrganismType* organism)
{
	ASSERT_DEBUG(Tools::is<const OrganismType>(m_organism));
	m_organism = Tools::as<const BaseOrganism>(organism);
}

}}

#endif
