#pragma once

#include "RigidShape2D.h"



enum TriPointOrientation
{
	Collinear = 0,
	Clockwise = 1,
	CounterClockwise = 2
};

class RigidShape2DHelper
{
public:
	static bool DoShapesIntersect(RigidShape2D, RigidShape2D);
	static bool DoLinesIntersect(Vector2D, Vector2D, Vector2D, Vector2D);
	static TriPointOrientation GetOrientationOfThreePoints(Vector2D, Vector2D, Vector2D);
	static bool DoesPointExistWithinLineBounds(Vector2D, Vector2D, Vector2D);
};