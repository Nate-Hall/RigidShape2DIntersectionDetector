#pragma once

#include "RigidShape2D.h"

enum TriPointOrientation
{
	Collinear = 0,
	Clockwise = 1,
	CounterClockwise = 2
};

static class RigidShape2DHelper
{
public:
	static bool DoesIntersect(RigidShape2D, RigidShape2D);
	static TriPointOrientation GetOrientationOfThreePoints(Vector2D, Vector2D, Vector2D);
};