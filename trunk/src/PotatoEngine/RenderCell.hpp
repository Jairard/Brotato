#ifndef __POT_RENDERCELL__
#define __POT_RENDERCELL__

#include <SFML/Graphics.hpp>
#include "Core/ClassHelpers.hpp"
#include "Debug/Logger.hpp"
#include "Cell.hpp"

namespace Pot
{

class Potato;

class RenderCell: public Cell
{
	friend class Potato;
	
	protected:
		RenderCell(Potato* potato);
	public:
		IMPL_VIRTUAL_DESTRUCTOR(RenderCell);

		virtual void update() {}
		SAFE_ACCESSOR_WITH_NAME(sf::RenderTarget*, target, sTarget);
		MUTATOR_WITH_NAME(sf::RenderTarget*, target, setTarget);
		
	protected:
		virtual void render();

	protected:
		sf::RenderTarget* m_target;
	
	//private:
	/*
	public:
		template<>
		void initialize<sf::RenderTarget*>(sf::RenderTarget* target)
		{
			std::cout << "Yay !" << std::endl;
			m_target = target;
		}
	//*/
};

/*
#include <iostream>
template<>
void initializeCell<RenderCell*, sf::RenderTarget*>(RenderCell* cell,  sf::RenderTarget* target)
{
	POT_UNUSED(cell);
	POT_UNUSED(target);
	std::cout << "Yay !" << std::endl;
	//m_target = target;
}
//*/

}

#endif
