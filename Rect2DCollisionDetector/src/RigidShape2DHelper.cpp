#include <algorithm>
#include "RigidShape2DHelper.h"



bool RigidShape2DHelper::DoShapesIntersect(const RigidShape2D& shapeA, const RigidShape2D& shapeB)
{
	for (size_t i = 0; i < shapeA.m_numVertices - 1; i++)
	{
		for (size_t j = 0; j < shapeB.m_numVertices - 1; j++)
		{
			if (DoLinesIntersect(shapeA.m_coordinates[i], shapeA.m_coordinates[i + 1], shapeB.m_coordinates[j], shapeB.m_coordinates[j + 1]))
				return true;
		}
	}

	// Special case: One shape lies entirely within other shape without touching
	if (shapeA.m_numVertices > 0 && shapeB.m_numVertices > 2
		&& DoesPointExistWithinShapeBounds(shapeA.m_coordinates[0], shapeB))
		return true;

	if (shapeA.m_numVertices > 2 && shapeB.m_numVertices > 0
		&& DoesPointExistWithinShapeBounds(shapeB.m_coordinates[0], shapeA))
		return true;

	return false;
}



bool RigidShape2DHelper::DoLinesIntersect(const Vector2& lineAStart, const Vector2& lineAEnd, const Vector2& lineBStart, const Vector2& lineBEnd)
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



TriPointOrientation RigidShape2DHelper::GetOrientationOfThreePoints(const Vector2& pointA, const Vector2& pointB, const Vector2& pointC)
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



bool RigidShape2DHelper::DoesPointExistWithinShapeBounds(const Vector2& point, const RigidShape2D& shape)
{
	// Create end coord from point that forms an infinite line to the right
	Vector2 pointEnd = Vector2(std::numeric_limits<float>::max(), point.Y);

	unsigned int intersectCount = 0;

	// Count how many times the infinite line intersects the shape
	for (size_t i = 0; i < shape.m_numVertices - 1; i++)
	{
		if (DoLinesIntersect(point, pointEnd, shape.m_coordinates[i], shape.m_coordinates[i + 1]))
			intersectCount++;
	}

	// If the intersection count is odd, the initial point exists within the shape
	return intersectCount % 2 != 0;
}



bool RigidShape2DHelper::DoesPointExistWithinLineBounds(const Vector2& point, const Vector2& lineStart, const Vector2& lineEnd)
{
	bool liesWithinX = point.X <= std::max(lineStart.X, lineEnd.X) && point.X >= std::min(lineStart.X, lineEnd.X);
	bool liesWithinY = point.Y <= std::max(lineStart.Y, lineEnd.Y) && point.Y >= std::min(lineStart.Y, lineEnd.Y);

	return liesWithinX && liesWithinY;
}
