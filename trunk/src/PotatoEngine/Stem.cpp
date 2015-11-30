#include "Stem.hpp"

#include <assert.h>
#include "Core/Tools.hpp"
#include "Core/LibsHelpers.hpp"
#include "Debug/Logger.hpp"
#include "Debug/Renderer.hpp"
#include "PotatoPlant.hpp"
#include "Potato.hpp"

namespace Pot
{

using Debug::Logger;

const std::string Stem::c_motherPotatoName = "__motherPotato__";
const char* Stem::c_tag = "Stem";
int Stem::s_transformComputationCount = 0;

Stem::Stem(PotatoPlant* plant):
	m_plant(plant),
	m_potatoPool(512)
{
	UNUSED(m_plant);
	m_motherPotato = m_potatoPool.create();
	m_motherPotato->initialize(c_motherPotatoName, this);
}

Stem::~Stem()
{
	destroyPotatoRec(m_motherPotato);
}

void Stem::render(float elapsedTime) const
{
	s_transformComputationCount = 0;
	renderRec(m_motherPotato, elapsedTime, false);
	
	if (s_transformComputationCount > 0)
		Logger::log(c_tag, "render caused %d transform recomputations", s_transformComputationCount);
}

void Stem::renderRec(Potato* potato, float elapsedTime, bool isRotten) const
{
	ASSERT_RELEASE(potato != nullptr);
	
	isRotten |= potato->m_worldTransform.isRotten() | potato->m_localTransform.isRotten();
	if (isRotten)
	{
		ASSERT_DEBUG(!isMotherPotatoPtr(potato));
		// We don't want to check matrix's state, it's ensured by the recursive call
		updateTransform(potato);
		Logger::log(c_tag, "render: updating transform for '%s'", potato->name().c_str());
		s_transformComputationCount++;
	}
	
	potato->render(elapsedTime);
	
	for (unsigned int i = 0; i < potato->childCount(); ++i)
		renderRec(potato->childPtr(i), elapsedTime, isRotten);
}

void Stem::debugRender(Debug::Renderer& renderer) const
{
	debugRenderRec(m_motherPotato, renderer);
	
	// Draw world transform
	sf::Transform t;
	t.scale(20.f, 20.f);
	renderer.DrawTransform(t);
}

void Stem::debugRenderRec(const Potato* potato, Debug::Renderer& renderer) const
{
	ASSERT_RELEASE(potato != nullptr);
	
	potato->debugRender(renderer);
	for (unsigned int i = 0; i < potato->childCount(); ++i)
		debugRenderRec(potato->childPtr(i), renderer);
}

void Stem::update()
{
	updatePotatoRec(m_motherPotato);
}

/*
PotatoDNA Stem::instantiatePotato(const char* name)
/*/
Potato* Stem::instantiatePotato(const char* name)
//*/
{
	ASSERT_DEBUG_MSG(name != c_motherPotatoName, "this potato name is reserved");
	Potato* potato = m_potatoPool.create();
	potato->initialize(name, this, m_motherPotato);
	m_motherPotato->m_children.push_back(potato);
	/*
	return PotatoDNA(potato);
	/*/
	return potato;
	//*/
}

/*
bool Stem::isMotherPotato(PotatoDNA dna) const
{
	ASSERT_DEBUG(dna.isValid());
	return isMotherPotatoPtr(dna.operator->()); // TODO: *dna ?
}
/*/
bool Stem::isMotherPotato(Potato* dna) const
{
	return isMotherPotatoPtr(dna);
}
//*/

bool Stem::isMotherPotatoPtr(const Potato* potato) const
{
	if (potato == m_motherPotato)
	{
		ASSERT_DEBUG(potato->m_parent == nullptr);
		ASSERT_DEBUG(potato->name() == c_motherPotatoName); // TODO: ptr comparison
		return true;
	}
	
	return false;
}

/*
void Stem::setParent(PotatoDNA dna, PotatoDNA parentDna) const
{
	ASSERT_DEBUG(dna.isValid());
	ASSERT_DEBUG(parentDna.isValid());
	setParent_internal(dna.operator->(), parentDna.operator->());
}
/*/
void Stem::setParent(Potato* dna, Potato* parentDna) const
{
	setParent_internal(dna, parentDna);
}
//*/

void Stem::setParent_internal(Potato* potato, Potato* parent) const
{
	// TODO: Check that potato is not an ancestor of parent ? (or handle this case ?)
	ASSERT_DEBUG(!isMotherPotatoPtr(potato));
	ASSERT_RELEASE(parent != nullptr);
	
	potato->m_parent->removeChild(potato);
	potato->m_parent = parent;
	parent->m_children.push_back(potato);
	
	// To preserve local transform and recompute world transform
	potato->m_localTransform.soil();
}

/*
void Stem::destroyPotato(PotatoDNA dna, bool deleteRecursively)
{
	ASSERT_DEBUG(dna.isValid());
	destroyPotato_internal(dna.operator->(), deleteRecursively);
}
/*/
void Stem::destroyPotato(Potato* dna, bool deleteRecursively)
{
	destroyPotato_internal(dna, deleteRecursively);
}
//*/

void Stem::destroyPotato_internal(Potato* potato, bool deleteRecursively)
{
	ASSERT_RELEASE(potato != nullptr);
	ASSERT_DEBUG(!isMotherPotatoPtr(potato));
	
	Potato* parent = potato->m_parent;
	parent->removeChild(potato);
	
	if (deleteRecursively)
		destroyPotatoRec(potato);
	else
	{
		for (unsigned int i = 0; i < potato->childCount(); ++i)
			setParent_internal(potato->childPtr(i), parent);
	
		potato->shutdown();
		m_potatoPool.destroy(potato);
	}
}

void Stem::ensureIntegrityIFN(const Potato* potato) const
{
	ASSERT_DEBUG(potato != nullptr);
	s_transformComputationCount = 0;
	std::list<const Potato*> rottenAncestors;
	
	getRottenAncestorsIFP(potato, rottenAncestors);
	
	// Recomputing world transform for the rotten ancestors
	for (std::list<const Potato*>::const_iterator it = rottenAncestors.begin(); it != rottenAncestors.end(); ++it)
	{
		updateTransform(*it);
		s_transformComputationCount++;
	}
	
	if (s_transformComputationCount > 0)
		Logger::log(c_tag, "ensureIntegrityAsc caused %d transform recomputation", s_transformComputationCount);
}

void Stem::updatePotatoRec(Potato* potato)
{
	ASSERT_RELEASE(potato != nullptr);
	
	potato->update();
	for (unsigned int i = 0; i < potato->childCount(); ++i)
		updatePotatoRec(potato->childPtr(i));
}

void Stem::destroyPotatoRec(Potato* potato)
{
	ASSERT_RELEASE(potato != nullptr);
	
	for (unsigned int i = 0; i < potato->childCount(); ++i)
		destroyPotatoRec(potato->childPtr(i));
	
	potato->shutdown();
	m_potatoPool.destroy(potato);
}

void Stem::updateTransform(const Potato* potato) const
{
	ASSERT_RELEASE(potato != nullptr);
	ASSERT_DEBUG(!isMotherPotatoPtr(potato));
	ASSERT_DEBUG( potato->m_worldTransform.isRotten() ||  potato->m_localTransform.isRotten());
	ASSERT_DEBUG(!potato->m_worldTransform.isRotten() || !potato->m_localTransform.isRotten());
	
	// Recomputing the transforms who need it
	if (potato->m_worldTransform.isRotten())
		potato->m_localTransform = potato->m_parent->m_invWorldTransform * potato->m_worldTransform;
	else
		potato->m_worldTransform = potato->m_parent->m_worldTransform * potato->m_localTransform;
	
	// We have to recompute both inverse transform because both transform changed
	potato->m_invWorldTransform = potato->m_worldTransform.inverse();
	potato->m_invLocalTransform = potato->m_localTransform.inverse();
	
	potato->m_worldTransform.recomputeIFN();
	potato->m_invWorldTransform.recomputeIFN();
	potato->m_localTransform.recomputeIFN();
	potato->m_invLocalTransform.recomputeIFN();
	
	// Soil children's local transform so that their world transforms will be recomputed
	for (unsigned int i = 0; i < potato->childCount(); ++i)
		potato->childPtr(i)->m_localTransform.soil();
	
	ASSERT_DEBUG(!potato->m_worldTransform.isRotten() && !potato->m_invWorldTransform.isRotten() &&
	             !potato->m_localTransform.isRotten() && !potato->m_invLocalTransform.isRotten());
}

void Stem::getRottenAncestorsIFP(const Potato* potato, std::list<const Potato*>& outRottenAncestors) const
{
	ASSERT_DEBUG(potato != nullptr);
	
	if (isMotherPotatoPtr(potato))
		return;
	
	std::list<const Potato*> ancestors;
	const Potato* closest = getClosestRottenAncestorIFP(potato, ancestors);
	
	if (closest != nullptr)
	{
		outRottenAncestors.insert(outRottenAncestors.begin(), ancestors.begin(), ancestors.end());
		getRottenAncestorsIFP((*ancestors.begin())->m_parent, outRottenAncestors);
	}
}

const Potato* Stem::getClosestRottenAncestorIFP(const Potato* potato, std::list<const Potato*>& outRottenAncestors) const
{
	ASSERT_DEBUG(potato != nullptr);
	
	// If the mother potato is reached, then there is no rotten potato in the ancestors
	if (isMotherPotatoPtr(potato))
		return nullptr;
	
	// It's really important to call push_front and not push_back,
	// this way the recomputation will be descending,
	// preventing transform to be soiled just after being recomputed.
	outRottenAncestors.push_front(potato);
	
	// If this potato is rotten, end the search here
	if (potato->m_worldTransform.isRotten() || potato->m_localTransform.isRotten())
		return potato;
	
	// Else look into its ancestors
	return getClosestRottenAncestorIFP(potato->m_parent, outRottenAncestors);
}

}
