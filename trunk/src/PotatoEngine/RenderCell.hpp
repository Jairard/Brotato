#ifndef __RENDERCELL__
#define __RENDERCELL__

#include <SFML/Graphics.hpp>
#include "Cell.hpp"
#include "Debug/Logger.hpp"

namespace Pot
{

class Potato;

class RenderCell: public Cell
{
	friend class Potato;
	
	protected:
		RenderCell(Potato* potato);
	public:
		virtual ~RenderCell();

		virtual void update() {}
		sf::RenderTarget* sTarget()               { assert(m_target != nullptr); return m_target; }
		void setTarget(sf::RenderTarget* target)  { m_target = target; }
		
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
	UNUSED(cell);
	UNUSED(target);
	std::cout << "Yay !" << std::endl;
	//m_target = target;
}
//*/

}

#endif
