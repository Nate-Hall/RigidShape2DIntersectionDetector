#include "RigidShape2D.h"


RigidShape2D::RigidShape2D()
{
	NumVertices = 0;
	Coordinates = nullptr;
}

RigidShape2D::RigidShape2D(int numVertices, Vector2D* coordinates)
{
	NumVertices = numVertices;
	Coordinates = coordinates;
}