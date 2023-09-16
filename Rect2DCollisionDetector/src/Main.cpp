#include <iostream>
#include "RigidShape2DHelper.h"
#include "test_RigidShape2DHelper.h"
#include "Entity.h"



static const bool _isInTestMode = true;

int main()
{
	if (_isInTestMode)
		test_RigidShape2DHelper::RunAllTests();

	Entity a = Entity();

	Vector2 shapeACoords[4] = { Vector2(-2, -2),
									Vector2(-2, -1),
									Vector2(-1, -1),
									Vector2(-1, -2) };
	RigidShape2D shapeA(4, shapeACoords);
	a.m_boundingBox = RigidShape2D(shapeA);
	Component comps[] = {AttackComponent(), HealthComponent()};
	a.m_components = comps;
	a.m_numComponents = 2;

	Entity b = Entity(a);

	a.m_boundingBox.m_coordinates[0].X = 5.0f;
	a.m_numComponents = 3;
}