#ifndef __POT_STEM__
#define __POT_STEM__

#include <string>
#include <list>
#include <SFML/Graphics/RenderTarget.hpp>
#include "Core/Pool.hpp"
#include "PotatoPlant.hpp"
#include "DnaSystem/DNA.hpp"

namespace Pot
{

namespace Debug
{
	class Renderer;
}

class Potato;
//class PotatoDNA;

class Stem
{
	public:
		Stem(PotatoPlant* plant);
		~Stem();
		
		void render(float elapsedTime) const;
		void debugRender(Debug::Renderer& renderer) const;
		void update(void);
		
		/*
		PotatoDNA instantiatePotato(const char* name="<unnamed potato>");
		bool isMotherPotato(PotatoDNA potato) const;
		void setParent(PotatoDNA potato, PotatoDNA parent) const;
		void destroyPotato(PotatoDNA potato, bool deleteRecursively = false);
		void ensureIntegrityIFN(const Potato* potato) const;
		/*/
		Potato* instantiatePotato(const char* name="<unnamed potato>");
		bool isMotherPotato(Potato* potato) const;
		void setParent(Potato* potato, Potato* parent) const;
		void destroyPotato(Potato* potato, bool deleteRecursively = false);
		void ensureIntegrityIFN(const Potato* potato) const;
		//*/
		
		SAFE_ACCESSOR_WITH_NAME(PotatoPlant*, plant, sPlant);
		
	private:
		// TODO: check method order in .cpp
		bool isMotherPotatoPtr(const Potato* potato) const;
		void setParent_internal(Potato* potato, Potato* parent) const;
		void destroyPotato_internal(Potato* potato, bool deleteRecursively = false);

		void renderRec(Potato* potato, float elapsedTime, bool isRotten) const;
		void debugRenderRec(const Potato* potato, Debug::Renderer& renderer) const;
		void updatePotatoRec(Potato* potato);
		void updateTransform(const Potato* potato) const;
		void destroyPotatoRec(Potato* potato);
		void getRottenAncestorsIFP(const Potato* potato, std::list<const Potato*>& outRottenAncestors) const;
		const Potato* getClosestRottenAncestorIFP(const Potato* potato, std::list<const Potato*>& outRottenAncestors) const;
		
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
