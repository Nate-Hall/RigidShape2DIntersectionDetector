#include <algorithm>
#include "RigidShape2DHelper.h"



bool RigidShape2DHelper::DoShapesIntersect(RigidShape2D shapeA, RigidShape2D shapeB)
{
	for (size_t i = 0; i < shapeA.NumVertices - 1; i++)
	{
		for (size_t j = 0; j < shapeB.NumVertices - 1; j++)
		{
			if (DoLinesIntersect(shapeA.Coordinates[i], shapeA.Coordinates[i + 1], shapeB.Coordinates[j], shapeB.Coordinates[j + 1]))
				return true;
		}
	}

	// Special case: One shape lies entirely within other shape without touching
	if (shapeA.NumVertices > 0 && shapeB.NumVertices > 2
		&& DoesPointExistWithinShapeBounds(shapeA.Coordinates[0], shapeB))
		return true;

	if (shapeA.NumVertices > 2 && shapeB.NumVertices > 0
		&& DoesPointExistWithinShapeBounds(shapeB.Coordinates[0], shapeA))
		return true;

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

	// Special case: a collinear point lies along the line
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
		return Collinear;
	else if (slopeA > slopeB)
		return Clockwise;
	else
		return CounterClockwise;
}



bool RigidShape2DHelper::DoesPointExistWithinShapeBounds(Vector2D point, RigidShape2D shape)
{
	// Create end coord from point that forms an infinite line to the right
	Vector2D pointEnd = Vector2D(std::numeric_limits<float>::max(), point.Y);

	unsigned int intersectCount = 0;

	// Count how many times the infinite line intersects the shape
	for (size_t i = 0; i < shape.NumVertices - 1; i++)
	{
		if (DoLinesIntersect(point, pointEnd, shape.Coordinates[i], shape.Coordinates[i + 1]))
			intersectCount++;
	}

	// If the intersection count is odd, the initial point exists within the shape
	return intersectCount % 2 != 0;
}



bool RigidShape2DHelper::DoesPointExistWithinLineBounds(Vector2D point, Vector2D lineStart, Vector2D lineEnd)
{
	bool liesWithinX = point.X <= std::max(lineStart.X, lineEnd.X) && point.X >= std::min(lineStart.X, lineEnd.X);
	bool liesWithinY = point.Y <= std::max(lineStart.Y, lineEnd.Y) && point.Y >= std::min(lineStart.Y, lineEnd.Y);

	return liesWithinX && liesWithinY;
}
