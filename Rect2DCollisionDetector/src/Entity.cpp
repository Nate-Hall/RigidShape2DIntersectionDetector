#include <cstring>
#include <memory>
#include "Entity.h"
#include "RigidShape2DHelper.h"



Entity::Entity()
{
	m_boundingBox = RigidShape2D();
}

Entity::Entity(const RigidShape2D& boundingBox, std::vector<Component> components)
	: m_boundingBox(boundingBox), m_components(components){}

Entity::Entity(const Entity& other)
	: m_boundingBox(other.m_boundingBox), m_components(other.m_components) {}


long Entity::UniqueIntersectionsInEntities(const Entity* entities, const unsigned int& numEntities)
{
	unsigned long numIntersections = 0;

	for (size_t i = 0; i < numEntities; i++)
	{
		for (size_t j = i + 1; j < numEntities; j++)
		{
			if (RigidShape2DHelper::DoShapesIntersect(entities[i].m_boundingBox, entities[j].m_boundingBox))
				numIntersections++;
		}
	}

	return numIntersections;
}
