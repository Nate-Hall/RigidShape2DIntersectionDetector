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
	static bool DoShapesIntersect(const RigidShape2D&, const RigidShape2D&);
	static bool DoLinesIntersect(const Vector2&, const Vector2&, const Vector2&, const Vector2&);
	static TriPointOrientation GetOrientationOfThreePoints(const Vector2&, const Vector2&, const Vector2&);
	static bool DoesPointExistWithinShapeBounds(const Vector2&, const RigidShape2D&);
	static bool DoesPointExistWithinLineBounds(const Vector2&, const Vector2&, const Vector2&);
};