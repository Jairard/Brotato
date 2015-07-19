#include "../Windows/Window.hpp"
#include "Renderer.hpp"

#include "../PotatoEngine/Core/Vector2.hpp"
#include "../PotatoEngine/Core/LibsHelpers.hpp"
#include "../PotatoEngine/Core/Tools.hpp"
#include "../Graphics.hpp"

namespace Graphics
{
	Renderer::Renderer(Window& window):
		m_entities(),
		m_window(window)
	{
	}
	
	Renderer::~Renderer()
	{
		std::list<Graphics::Entity*>::iterator it;
		
		for (it=m_entities.begin(); it!=m_entities.end(); it++)
			delete *it;
	}
	
	void Renderer::addEntity(Graphics::Entity* entity)
	{
		m_entities.push_back(entity);
	}
	
	void Renderer::render(float coef)
	{
		std::list<Graphics::Entity*>::iterator it;
		
		m_window.clear();
		
		//drawGrid();
		for (it=m_entities.begin(); it!=m_entities.end(); it++)
			(*it)->render(m_window, coef);
		//drawAxes();
		
		m_window.display();
	}
	
	void Renderer::drawGrid()
	{
		sf::View view = m_window.getView();
		Pot::Vector2f center = sfv_2_pv(view.getCenter()), size = sfv_2_pv(view.getSize());
		int minX = (int)ceil(center.x - size.x/2.), maxX = (int)floor(center.x + size.x/2.);
		int minY = (int)ceil(center.y - size.y/2.), maxY = (int)floor(center.y + size.y/2.);
		
		for (int x=minX; x <=maxX; x++)
		{
			for (int y=minY; y<maxY; y++)
			{
				Graphics::PointShape point(Pot::Vector2f(x, y));
				point.setColor(sf::Color::White);
				m_window.render(point);
			}
		}
	}
	
	void Renderer::drawAxes()
	{
		Graphics::SegmentShape xAxis(Pot::Vector2f(0., 0.), Pot::Vector2f(1., 0.)), yAxis(Pot::Vector2f(0., 0.), Pot::Vector2f(0., 1.));
		xAxis.setColor(sf::Color(255, 0, 0));
		yAxis.setColor(sf::Color(0, 255, 0));
		
		m_window.render(xAxis);
		m_window.render(yAxis);
	}
}

