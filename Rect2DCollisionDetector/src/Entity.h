#pragma once

#include <vector>
#include "RigidShape2D.h"

enum ComponentType
{
	None = 0,
	Health = 1,
	Attack = 2,
	Movement = 3
};

class Component
{
public:
	virtual ComponentType GetComponentType() { return None; };

	virtual ~Component() = default;
};

// A few basic Components. Entities can have up to one of each Component type.
// Assume they will have more methods, and there will be more Components: those
// details are not important for this test.
// Add anything needed to support your implementation.
class HealthComponent : public Component
{
	ComponentType GetComponentType() override { return Health; };

private:
	int m_health = 0;
};

class AttackComponent : public Component
{
	ComponentType GetComponentType() override { return Attack; };

private:
	unsigned int m_attackPower = 0;
};

class MovementComponent : public Component
{
	ComponentType GetComponentType() override { return Movement; };

private:
	float m_speed = 0;
};

class Entity
{
public:
	RigidShape2D m_boundingBox;
	std::vector<Component> m_components;

	Entity();
	Entity(const RigidShape2D&, std::vector<Component>);
	Entity(const Entity& other);
	static long UniqueIntersectionsInEntities(const Entity*, const unsigned int&);
};