#include <algorithm>
#include "RigidShape2DHelper.h"



bool RigidShape2DHelper::DoShapesIntersect(RigidShape2D shapeA, RigidShape2D shapeB)
{
	for (unsigned int i = 0; i < shapeA.NumVertices - 1; i++)
	{
		for (unsigned int j = 0; j < shapeB.NumVertices - 1; j++)
		{
			if (DoLinesIntersect(shapeA.Coordinates[i], shapeA.Coordinates[i + 1], shapeB.Coordinates[j], shapeB.Coordinates[j + 1]))
				return true;
		}
	}

	return false;
}



bool RigidShape2DHelper::DoLinesIntersect(Vector2D lineAStart, Vector2D lineAEnd, Vector2D lineBStart, Vector2D lineBEnd)
{
	TriPointOrientation orientation1 = GetOrientationOfThreePoints(lineAStart, lineAEnd, lineBStart);
	TriPointOrientation orientation2 = GetOrientationOfThreePoints(lineAStart, lineAEnd, lineBEnd);
	TriPointOrientation orientation3 = GetOrientationOfThreePoints(lineBStart, lineBEnd, lineAStart);
	TriPointOrientation orientation4 = GetOrientationOfThreePoints(lineBStart, lineBEnd, lineAEnd);

	if (orientation1 != orientation2 && orientation3 != orientation4)
		return true;

	if ((orientation1 == Collinear && DoesPointExistWithinLineBounds(lineBStart, lineAStart, lineAEnd))
		|| (orientation2 == Collinear && DoesPointExistWithinLineBounds(lineBEnd, lineAStart, lineAEnd))
		|| (orientation3 == Collinear && DoesPointExistWithinLineBounds(lineAStart, lineBStart, lineBEnd))
		|| (orientation4 == Collinear && DoesPointExistWithinLineBounds(lineAEnd, lineBStart, lineBEnd)))
			return true;

	return false;
}



TriPointOrientation RigidShape2DHelper::GetOrientationOfThreePoints(Vector2D pointA, Vector2D pointB, Vector2D pointC)
{
	float slopeA = (pointB.Y - pointA.Y) * (pointC.X - pointB.X);
	float slopeB = (pointB.X - pointA.X) * (pointC.Y - pointB.Y);
		
	if (slopeA == slopeB)
		return TriPointOrientation::Collinear;
	else if (slopeA > slopeB)
		return TriPointOrientation::Clockwise;
	else
		return TriPointOrientation::CounterClockwise;
}



bool RigidShape2DHelper::DoesPointExistWithinLineBounds(Vector2D point, Vector2D lineStart, Vector2D lineEnd)
{
	bool liesWithinX = point.X <= std::max(lineStart.X, lineEnd.X) && point.X >= std::min(lineStart.X, lineEnd.X);
	bool liesWithinY = point.Y <= std::max(lineStart.Y, lineEnd.Y) && point.Y >= std::min(lineStart.Y, lineEnd.Y);

	return liesWithinX && liesWithinY;
}
