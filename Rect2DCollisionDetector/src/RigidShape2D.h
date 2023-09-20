#pragma once

#include <vector>
#include "Vector2.h"



struct RigidShape2D
{
	std::vector<Vector2> m_coordinates;

	RigidShape2D();
	RigidShape2D(const std::vector<Vector2>);
	RigidShape2D(const RigidShape2D& other);
};