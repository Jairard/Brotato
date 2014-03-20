#include <iostream>
#include "../Math.hpp"
#include "Entity.hpp"
#include "World.hpp"

namespace Phy
{
	World::World(const Vector2f& gravity, float timeStep, int velocityIterations, int positionIterations):
	    b2World(gravity.toBox2D()),
		m_entities(),
		m_timeStep(timeStep),
		m_velocityIterations(velocityIterations),
		m_positionIterations(positionIterations)
	{
	}
	
	World::~World()
	{}
	
	bool World::RegisterEntity(Entity* entity, bool secure)
	{
		bool found = false;
		
		if (secure)
			found = UnregisterEntity(entity, true);
		
		m_entities.push_back(entity);
		return !found;
	}
	
	bool World::UnregisterEntity(Entity* entity, bool secure)
	{
		bool found = false;
		std::list<Entity*>::iterator it;
		
		for (it=m_entities.begin(); it!=m_entities.end(); it++)
		{
			if (*it == entity)
			{
				found = true;
				it = m_entities.erase(it);
				if (!secure)
					break;
			}
		}
	
		return found;
	}
	
	void World::step()
	{
		Step(m_timeStep, m_velocityIterations, m_positionIterations);
		
		std::list<Entity*>::iterator it;
		
		for (it=m_entities.begin(); it!=m_entities.end(); it++)
		{
			Entity* entity = *it;
			b2Body* body = entity->body();
			Vector2f position = transformPosition(body->GetPosition());
			float32 angle = transformAngle(body->GetAngle());
			
			entity->update(position, angle);
		}
	}
	
	Vector2f World::transformPosition(const Vector2f& position)
	{
		return Vector2f(position.x, -position.y);
	}
	
	float World::transformAngle(float angle)
	{
		return -Math::rad2deg(angle);
	}
}
