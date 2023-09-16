#pragma once

#include "Vector2.h"



struct RigidShape2D
{
	unsigned int m_numVertices;
	Vector2* m_coordinates;

	RigidShape2D();
	RigidShape2D(const int&, Vector2*);
	RigidShape2D(const RigidShape2D& other);
	~RigidShape2D();
};