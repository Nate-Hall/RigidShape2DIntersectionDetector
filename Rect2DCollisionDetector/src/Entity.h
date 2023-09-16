#pragma once

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
	virtual unsigned long long GetComponentMemorySize() { return sizeof(Component); };

	virtual ~Component() = default;
};

// A few basic Components. Entities can have up to one of each Component type.
// Assume they will have more methods, and there will be more Components: those
// details are not important for this test.
// Add anything needed to support your implementation.
class HealthComponent : public Component
{
	ComponentType GetComponentType() override { return Health; };
	unsigned long long GetComponentMemorySize() override { return sizeof(HealthComponent); };

private:
	int m_health = 0;
};

class AttackComponent : public Component
{
	ComponentType GetComponentType() override { return Attack; };
	unsigned long long GetComponentMemorySize() override { return sizeof(AttackComponent); };

private:
	unsigned int m_attackPower = 0;
};

class MovementComponent : public Component
{
	ComponentType GetComponentType() override { return Movement; };
	unsigned long long GetComponentMemorySize() override { return sizeof(MovementComponent); };

private:
	float m_speed = 0;
};

class Entity
{
public:
	RigidShape2D m_boundingBox;
	Component* m_components;
	int m_numComponents;

	Entity();
	Entity(const Entity& other);
};