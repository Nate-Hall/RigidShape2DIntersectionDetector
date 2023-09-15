#pragma once

#include "Vector2D.h"

struct RigidShape2D
{
	int NumVertices;
	Vector2D* Coordinates;

	RigidShape2D();
	RigidShape2D(int, Vector2D*);
};