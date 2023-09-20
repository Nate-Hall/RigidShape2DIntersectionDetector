#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include "RigidShape2DHelper.h"
#include "test_RigidShape2DHelper.h"
#include "Entity.h"



static const bool _isInTestMode = false;


int main(int argc, const char* argv[])
{
	if (_isInTestMode)
		test_RigidShape2DHelper::RunAllTests();

	if (argc < 2)
	{
		std::cerr << "Specify a file to run this program.\n";
		return 1;
	}
	std::cout << "Running program against file: " << argv[1] << "\n";
	std::ifstream file(argv[1], std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file.\n";
		return 2;
	}
	unsigned int numberOfEntities = 0;
	if (!(file >> numberOfEntities))
	{
		std::cerr << "Failed to get number of Entities from file.\n";
		return 3;
	}

	std::queue<Component> componentQueue;
	Entity* entities = new Entity[numberOfEntities];

	for (unsigned int i = 0; i < numberOfEntities; ++i)
	{
		float x = 0;
		float y = 0;
		float width = 0;
		float height = 0;
		if (!(file >> x >> y >> width >> height))
		{
			std::cerr << "Error getting bounds on line " << i + 1 << ".\n";
			return 4;
		}
		// Not every Entity has Components.
		std::string componentTypes;
		const auto currentPos = file.tellg();
		file >> componentTypes;
		if (!componentTypes.empty() && !std::isalpha(componentTypes.back()))
		{
			file.seekg(currentPos);
			componentTypes.clear();
		}

		for (const char type : componentTypes)
		{
			switch (type)
			{
			case 'H':
				componentQueue.push(HealthComponent());
				break;
			case 'A':
				componentQueue.push(AttackComponent());
				break;
			case 'M':
				componentQueue.push(MovementComponent());
				break;
			default:
				std::cerr << "Unknown Component type: " << type << "\n";
				break;
			}
		}

		// Create an Entity with a Rectangle2D bounding box and given Components.
		int numComponents = componentQueue.size();
		std::vector<Component> components(numComponents);
		for (size_t i = 0; i < numComponents; i++)
		{
			components[i] = componentQueue.front();
			componentQueue.pop();
		}

		std::vector<Vector2> rectPoints(4);
		rectPoints[0] = { x, y };
		rectPoints[1] = { x, y + height };
		rectPoints[2] = { x + width, y + height };
		rectPoints[3] = { x + width, y };

		RigidShape2D rect2D(rectPoints);
		entities[i] = Entity(rect2D, components);
	}
	file.close();
	const auto start = std::chrono::high_resolution_clock::now();
	
	std::cout << "Total number of unique intersections: " << Entity::UniqueIntersectionsInEntities(entities, numberOfEntities) << std::endl;
	delete[] entities;

	const auto end = std::chrono::high_resolution_clock::now();
	const auto runMS =
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Algorithm executed in " << runMS.count() << "ms.\n";
	return 0;
}