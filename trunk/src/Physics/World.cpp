#include <iostream>
#include "../PotatoEngine/Core/Math.hpp"
#include "../PotatoEngine/Core/LibsHelpers.hpp"
#include "Entity.hpp"
#include "World.hpp"

namespace Phy
{
	World::World(const Pot::Vector2f& gravity, float timeStep, int velocityIterations, int positionIterations):
	             b2World(pv_2_b2v(gravity)),
		m_entities(),
		m_timeStep(timeStep),
		m_velocityIterations(velocityIterations),
		m_positionIterations(positionIterations),
		m_drawDebug(false)
	{
	}

	World::~World()
	{}

	bool World::RegisterEntity(Entity* entity, bool secure)
	{
		bool found = false;

		if (!entity->isSetup())
			entity->setup();

		if (secure)
			found = UnregisterEntity(entity, secure);

		m_entities.push_back(entity);
		//m_entities.sort(compareEntities);
		//m_entities.unique(areEntitiesEqual);
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
		
		//m_entities.remove(entity);

		return found;
	}
	
	/*
	bool World::compareEntities(const Entity* first, const Entity* second)
	{
		return (int)first < (int)second;
	}
	
	bool World::areEntitiesEqual(const Entity* first, const Entity* second)
	{
		return first == second;
	}
	*/
	
	void World::setDebugRenderer(b2Draw* renderer)
	{
		SetDebugDraw(renderer);
		renderer->SetFlags(b2Draw::e_shapeBit);
		m_drawDebug = true;
	}
	
	void World::unsetDebugRenderer()
	{
		m_drawDebug = false;
	}

	void World::step()
	{
		Step(m_timeStep, m_velocityIterations, m_positionIterations);

		std::list<Entity*>::iterator it;

		for (it=m_entities.begin(); it!=m_entities.end(); it++)
		{
			Entity* entity = *it;
			b2Body* body = entity->body();
			Pot::Vector2f position = vectorFromPhy(b2v_2_pv(body->GetPosition()));
			float32 angle = angleFromPhy(body->GetAngle());

			entity->update(position, angle);
		}
		
		if (m_drawDebug)
			DrawDebugData();
	}

	Pot::Vector2f World::vectorFromPhy(const Pot::Vector2f& v)
	{
		return Pot::Vector2f(v.x, v.y);
	}

	Pot::Vector2f World::vectorToPhy(const Pot::Vector2f v)
	{
		return Pot::Vector2f(v.x, v.y);
	}

	float World::angleFromPhy(float angle)
	{
		return -Pot::Math::rad2deg(angle);
	}

	float World::angleToPhy(float angle)
	{
		return -Pot::Math::deg2rad(angle);
	}

	b2BodyType World::toBox2DType(BodyType type)
	{
		switch (type)
		{
			case Dynamic:
				return b2_dynamicBody;
			case Kinematic:
				return b2_kinematicBody;
			case Static:
				return b2_staticBody;
			default:
				return b2_staticBody;
		}
	}
}
