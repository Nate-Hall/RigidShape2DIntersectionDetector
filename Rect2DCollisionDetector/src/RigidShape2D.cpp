#include <cstring>
#include "RigidShape2D.h"



RigidShape2D::RigidShape2D(){}



RigidShape2D::RigidShape2D(const std::vector<Vector2> coordinates)
	: m_coordinates(coordinates){}



RigidShape2D::RigidShape2D(const RigidShape2D& other)
	: m_coordinates(other.m_coordinates){}