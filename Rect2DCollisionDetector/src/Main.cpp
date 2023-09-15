#include <iostream>
#include "RigidShape2DHelper.h"

int main()
{
	Vector2D testArray[4] = { Vector2D(-1, -1), Vector2D(-1, 1), Vector2D(1, 1), Vector2D(1, -1) };
	RigidShape2D testRig(4, testArray);

	std::cout << "NumVertices: " << testRig.NumVertices << std::endl;
	std::cout << "Point1.X: " << testRig.Coordinates[0].X << "  /  Point1.Y: " << testRig.Coordinates[0].Y << std::endl;
	std::cout << "Point2.X: " << testRig.Coordinates[1].X << "  /  Point2.Y: " << testRig.Coordinates[1].Y << std::endl;
	std::cout << "Point3.X: " << testRig.Coordinates[2].X << "  /  Point3.Y: " << testRig.Coordinates[2].Y << std::endl;
	std::cout << "Point4.X: " << testRig.Coordinates[3].X << "  /  Point4.Y: " << testRig.Coordinates[3].Y << std::endl;
}