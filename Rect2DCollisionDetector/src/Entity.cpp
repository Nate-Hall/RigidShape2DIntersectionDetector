#include <cstring>
#include "Entity.h"



Entity::Entity()
{
	m_boundingBox = RigidShape2D();
	m_components = nullptr;
	m_numComponents = 0;
}

Entity::Entity(const Entity& other)
{
	m_boundingBox = RigidShape2D(other.m_boundingBox);

	// Determine memory size of m_components
	unsigned long memSize = 0;
	for (size_t i = 0; i < other.m_numComponents; i++)
	{
		memSize += other.m_components[i].GetComponentMemorySize();
	}

	memcpy(&m_components, &other.m_components, memSize);

	memcpy(&m_numComponents, &other.m_numComponents, sizeof(int));
}
