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
	m_potatoPool(true, 512)
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
	assert(potato != nullptr);
	
	isRotten |= potato->m_worldTransform.isRotten() | potato->m_localTransform.isRotten();
	if (isRotten)
	{
		assert(!isMotherPotato(potato));
		// We don't want to check matrix's state, it's ensured by the recursive call
		updateTransform(potato);
		Logger::log(c_tag, "render: updating transform for '%s'", potato->name().c_str());
		s_transformComputationCount++;
	}
	
	potato->render(elapsedTime);
	
	for (unsigned int i = 0; i < potato->childCount(); ++i)
		renderRec(potato->child(i), elapsedTime, isRotten);
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
	assert(potato != nullptr);
	
	potato->debugRender(renderer);
	for (unsigned int i = 0; i < potato->childCount(); ++i)
		debugRenderRec(potato->child(i), renderer);
}

void Stem::update()
{
	updatePotatoRec(m_motherPotato);
}

Potato* Stem::instantiatePotato(const char* name)
{
	Potato* potato = m_potatoPool.create();
	potato->initialize(name, this, m_motherPotato);
	m_motherPotato->m_children.push_back(potato);
	return potato;
}

bool Stem::isMotherPotato(const Potato* potato) const
{
	if (potato->m_parent == nullptr)
	{
		assert(potato->name() == c_motherPotatoName);
		return true;
	}
	
	return false;
}

void Stem::setParent(Potato* potato, Potato* parent) const
{
	// Check that potato is not an ancestor of parent ?
	assert(!isMotherPotato(potato));
	assert(parent != nullptr);
	
	potato->m_parent->removeChild(potato);
	potato->m_parent = parent;
	parent->m_children.push_back(potato);
	
	// To preserve local transform and recompute world transform
	potato->m_localTransform.soil();
}

void Stem::destroyPotato(Potato* potato, bool deleteRecursively)
{
	assert(potato != nullptr);
	assert(!isMotherPotato(potato));
	
	Potato* parent = potato->m_parent;
	parent->removeChild(potato);
	
	if (deleteRecursively)
		destroyPotatoRec(potato);
	else
	{
		for (unsigned int i = 0; i < potato->childCount(); ++i)
			setParent(potato->child(i), parent);
	
		potato->shutdown();
		m_potatoPool.destroy(potato);
	}
}

void Stem::ensureIntegrityIFN(Potato* potato) const
{
	assert(potato != nullptr);
	s_transformComputationCount = 0;
	std::list<Potato*> rottenAancestors;
	
	getRottenAncestorsIFP(potato, rottenAancestors);
	
	// Recomputing world transform for the rotten ancestors
	for (std::list<Potato*>::iterator it = rottenAancestors.begin(); it != rottenAancestors.end(); ++it)
	{
		updateTransform(*it);
		s_transformComputationCount++;
	}
	
	if (s_transformComputationCount > 0)
		Logger::log(c_tag, "ensureIntegrityAsc caused %d transform recomputation", s_transformComputationCount);
}

void Stem::updatePotatoRec(Potato* potato)
{
	assert(potato != nullptr);
	
	potato->update();
	for (unsigned int i = 0; i < potato->childCount(); ++i)
		updatePotatoRec(potato->child(i));
}

void Stem::destroyPotatoRec(Potato* potato)
{
	assert(potato != nullptr);
	
	for (unsigned int i = 0; i < potato->childCount(); ++i)
		destroyPotatoRec(potato->child(i));
	
	potato->shutdown();
	m_potatoPool.destroy(potato);
}

void Stem::updateTransform(Potato* potato) const
{
	assert(potato != nullptr);
	assert(!isMotherPotato(potato));
	assert( potato->m_worldTransform.isRotten() ||  potato->m_localTransform.isRotten());
	assert(!potato->m_worldTransform.isRotten() || !potato->m_localTransform.isRotten());
	
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
		potato->child(i)->m_localTransform.soil();
	
	assert(!potato->m_worldTransform.isRotten() && !potato->m_invWorldTransform.isRotten() &&
		   !potato->m_localTransform.isRotten() && !potato->m_invLocalTransform.isRotten());
}

void Stem::getRottenAncestorsIFP(Potato* potato, std::list<Potato*>& outRottenAncestors) const
{
	assert(potato != nullptr);
	
	if (isMotherPotato(potato))
		return;
	
	std::list<Potato*> ancestors;
	Potato* closest = getClosestRottenAncestorIFP(potato, ancestors);
	
	if (closest != nullptr)
	{
		outRottenAncestors.insert(outRottenAncestors.begin(), ancestors.begin(), ancestors.end());
		getRottenAncestorsIFP((*ancestors.begin())->m_parent, outRottenAncestors);
	}
}

Potato* Stem::getClosestRottenAncestorIFP(Potato* potato, std::list<Potato*>& outRottenAncestors) const
{
	assert(potato != nullptr);
	
	// If the mother potato is reached, then there is no rotten potato in the ancestors
	if (isMotherPotato(potato))
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
