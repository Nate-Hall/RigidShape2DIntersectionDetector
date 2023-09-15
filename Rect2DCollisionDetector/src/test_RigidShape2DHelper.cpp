#include <iostream>
#include <functional>
#include "RigidShape2DHelper.h"

using namespace std;

static const unsigned short _totalTests = 6;

class test_RigidShape2DHelper
{
public:
	static void RunAllTests()
	{
		unsigned int passedTests = 0;

		passedTests += RunTest("RigidShape2DHelper - NoIntersect test... ", &Test_NoIntersect);
		passedTests += RunTest("RigidShape2DHelper - SimpleIntersect test... ", &Test_SimpleIntersect);
		passedTests += RunTest("RigidShape2DHelper - CollinearPointIntersect test... ", &Test_CollinearPointIntersect);
		passedTests += RunTest("RigidShape2DHelper - CollinearEdgeIntersect test... ", &Test_CollinearEdgeIntersect);
		passedTests += RunTest("RigidShape2DHelper - IdenticalPointsIntersect test... ", &Test_IdenticalPointIntersect);
		passedTests += RunTest("RigidShape2DHelper - EntirelyWithinBoundsIntersect test... ", &Test_EntirelyWithinBoundsIntersect);

		cout << endl;
		cout << "RigidShape2DHelper - Tests finished!" << endl;
		cout << passedTests << " out of " << _totalTests << " passed!" << endl;
	}



private:
	static bool RunTest(const char* consoleText, function<bool()> testFunc)
	{
		bool testPassed = testFunc();

		cout << consoleText << (testPassed ? "PASSED!" : "FAILED!") << endl;

		return testPassed;
	}


	// Test: That two shapes entirely seperate will not trigger an intersection
	//
	// Case: Neither shape overlap in any way
	static bool Test_NoIntersect()
	{
		Vector2D shapeACoords[4] = { Vector2D(-2, -2),
										Vector2D(-2, -1),
										Vector2D(-1, -1),
										Vector2D(-1, -2) };
		RigidShape2D shapeA(4, shapeACoords);

		Vector2D shapeBCoords[4] = { Vector2D(1, 1),
										Vector2D(1, 2),
										Vector2D(2, 2),
										Vector2D(2, 1) };
		RigidShape2D shapeB(4, shapeBCoords);

		return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
	}


	// Test: That a point existing entirely inside of another shape will trigger an intersection
	//
	// Case: The point (0,0) in shapeB lives entirely within the bounds of shapeA
	static bool Test_SimpleIntersect()
	{
		Vector2D shapeACoords[4] = { Vector2D(-1, -1),
										Vector2D(-1, 1),
										Vector2D(1, 1),
										Vector2D(1, -1) };
		RigidShape2D shapeA(4, shapeACoords);

		Vector2D shapeBCoords[4] = { Vector2D(0, 0),
										Vector2D(0, 2),
										Vector2D(2, 2),
										Vector2D(2, 0) };
		RigidShape2D shapeB(4, shapeBCoords);

		return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
	}


	//Test: That a single point lying on the line of another shape will trigger an intersection
	//
	//Case: The point (1,0) in shapeB lies on the line between (1,1) -> (1,-1) on shapeA
	static bool Test_CollinearPointIntersect()
	{
		Vector2D shapeACoords[4] = { Vector2D(-1, -1),
										Vector2D(-1, 1),
										Vector2D(1, 1),
										Vector2D(1, -1) };
		RigidShape2D shapeA(4, shapeACoords);

		Vector2D shapeBCoords[4] = { Vector2D(1, 0),
										Vector2D(2, 1),
										Vector2D(3, 0),
										Vector2D(2, -1) };
		RigidShape2D shapeB(4, shapeBCoords);

		return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
	}



	//Test: That an entire line overlapping the line of another shape will trigger an intersection
	//
	//Case: The line (1,-2) -> (1,2) of shapeB lies along the line between (1,1) -> (1,-1) on shapeA
	static bool Test_CollinearEdgeIntersect()
	{
		Vector2D shapeACoords[4] = { Vector2D(-1, -1),
										Vector2D(-1, 1),
										Vector2D(1, 1),
										Vector2D(1, -1) };
		RigidShape2D shapeA(4, shapeACoords);

		Vector2D shapeBCoords[4] = { Vector2D(1, -2),
										Vector2D(1, 2),
										Vector2D(2, 2),
										Vector2D(2, -2) };
		RigidShape2D shapeB(4, shapeBCoords);

		return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
	}



	//Test: That a single point sharing the same point of another shape will trigger an intersection
	//
	//Case: Both shapeA and shapeB share the point (1,1)
	static bool Test_IdenticalPointIntersect()
	{
		Vector2D shapeACoords[4] = { Vector2D(-1, -1),
										Vector2D(-1, 1),
										Vector2D(1, 1),
										Vector2D(1, -1) };
		RigidShape2D shapeA(4, shapeACoords);

		Vector2D shapeBCoords[4] = { Vector2D(1, 1),
										Vector2D(1, 2),
										Vector2D(2, 2),
										Vector2D(2, 1) };
		RigidShape2D shapeB(4, shapeBCoords);

		return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
	}



	//Test: That a whole shape existing entirely within another shape will trigger an intersection
	//
	//Case: ShapeB existing entirely within shapeA
	static bool Test_EntirelyWithinBoundsIntersect()
	{
		Vector2D shapeACoords[4] = { Vector2D(-1, -1),
										Vector2D(-1, 1),
										Vector2D(1, 1),
										Vector2D(1, -1) };
		RigidShape2D shapeA(4, shapeACoords);

		Vector2D shapeBCoords[4] = { Vector2D(-0.5, -0.5),
										Vector2D(-0.5, 0.5),
										Vector2D(0.5, 0.5),
										Vector2D(0.5, -0.5) };
		RigidShape2D shapeB(4, shapeBCoords);

		return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
	}
};