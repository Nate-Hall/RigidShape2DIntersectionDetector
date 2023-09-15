#include "RigidShape2DHelper.h"



bool RigidShape2DHelper::DoesIntersect(RigidShape2D shapeA, RigidShape2D shapeB)
{
	for (auto i = 0; i < shapeA.NumVertices; i++)
	{

	}

	return false;
}

TriPointOrientation RigidShape2DHelper::GetOrientationOfThreePoints(Vector2D pointA, Vector2D pointB, Vector2D pointC)
{
	int slopeA = (pointB.Y - pointA.Y) * (pointC.X - pointB.X);
	int slopeB = (pointB.X - pointA.X) * (pointC.Y - pointB.Y);
		
	if (slopeA == slopeB)
		return TriPointOrientation::Collinear;
	else if (slopeA > slopeB)
		return TriPointOrientation::Clockwise;
	else
		return TriPointOrientation::CounterClockwise;
}
