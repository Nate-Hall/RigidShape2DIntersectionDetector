#include <cstring>
#include "RigidShape2D.h"



RigidShape2D::RigidShape2D()
{
	m_numVertices = 0;
	m_coordinates = nullptr;
}



RigidShape2D::RigidShape2D(const int& numVertices, Vector2* coordinates)
{
	m_numVertices = numVertices;
	m_coordinates = coordinates;
}



RigidShape2D::RigidShape2D(const RigidShape2D& other)
{
	memcpy(&m_numVertices, &other.m_numVertices, sizeof(unsigned int));

	delete[] m_coordinates;
	m_coordinates = new Vector2[other.m_numVertices];

	memcpy(m_coordinates, other.m_coordinates, sizeof(Vector2) * other.m_numVertices);
}



RigidShape2D::~RigidShape2D()
{
	delete[] m_coordinates;
}