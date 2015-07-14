#include "RenderCell.hpp"

#include <list>
#include "Debug/Logger.hpp"
#include "Debug/Renderer.hpp"
#include "Core/Rect.hpp"
#include "Core/LibsHelpers.hpp"
#include "GeometryCell.hpp"

namespace Pot
{

RenderCell::RenderCell(Potato* potato):
	Cell(potato),
	m_target(nullptr)
{
	// Default render target is the window
	if (m_target == nullptr)
		m_target = sPotato()->sStem()->sPlant()->window();
}

void RenderCell::render()
{
	if (m_target == nullptr)
	{
		Debug::Logger::log(Debug::Logger::CWarning, "render cell has not target for potato %s", sPotato()->name().c_str());
		return;
	}
	
	GeometryCell* gc = sPotato()->fetchCellIFP<GeometryCell>();
	if (gc == nullptr)
		return;
	
	sf::RenderStates states;
	states.transform = sPotato()->worldTransform_const();
	m_target->draw(gc->vertices(), states);
}

/*
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

