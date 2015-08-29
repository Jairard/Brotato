#ifndef __STEM__
#define __STEM__

#include <string>
#include <list>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Core/Pool.hpp"
#include "PotatoPlant.hpp"

namespace Pot
{

namespace Debug
{
	class Renderer;
}

class Potato;

class Stem
{
	public:
		Stem(PotatoPlant* plant);
		~Stem();
		
		void render(float elapsedTime) const;
		void debugRender(Debug::Renderer& renderer) const;
		void update(void);
		
		Potato* instantiatePotato(const char* name="<unnamed potato>");
		bool isMotherPotato(const Potato* potato) const;
		void setParent(Potato* potato, Potato* parent) const;
		void destroyPotato(Potato* potato, bool deleteRecursively = false);
		void ensureIntegrityIFN(Potato* potato) const;
		
		PotatoPlant* sPlant(void)              { assert(m_plant != nullptr); return m_plant; }
		
	private:
		void renderRec(Potato* potato, float elapsedTime, bool isRotten) const;
		void debugRenderRec(const Potato* potato, Debug::Renderer& renderer) const;
		void updatePotatoRec(Potato* potato);
		void destroyPotatoRec(Potato* potato);
		void updateTransform(Potato* potato) const;
		void getRottenAncestorsIFP(Potato* potato, std::list<Potato*>& outRottenAncestors) const;
		Potato* getClosestRottenAncestorIFP(Potato* potato, std::list<Potato*>& outRottenAncestors) const;
		
	public:
		static const char*c_tag;
		
	private:
		static const std::string c_motherPotatoName;
		static int s_transformComputationCount;
		
		PotatoPlant* m_plant;
		Pool<Potato> m_potatoPool;
		Potato* m_motherPotato;
};

}

#endif