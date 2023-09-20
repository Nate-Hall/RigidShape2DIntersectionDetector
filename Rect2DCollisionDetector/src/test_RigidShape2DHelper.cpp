#include <iostream>
#include <functional>

#include "test_RigidShape2DHelper.h"
#include "RigidShape2DHelper.h"

using namespace std;

static const unsigned short _totalTests = 6;

void test_RigidShape2DHelper::RunAllTests()
{
	unsigned int passedTests = 0;

	passedTests += test_RigidShape2DHelper::RunTest("RigidShape2DHelper - NoIntersect test... ", &test_RigidShape2DHelper::Test_NoIntersect);
	passedTests += test_RigidShape2DHelper::RunTest("RigidShape2DHelper - SimpleIntersect test... ", &test_RigidShape2DHelper::Test_SimpleIntersect);
	passedTests += test_RigidShape2DHelper::RunTest("RigidShape2DHelper - CollinearPointIntersect test... ", &test_RigidShape2DHelper::Test_CollinearPointIntersect);
	passedTests += test_RigidShape2DHelper::RunTest("RigidShape2DHelper - CollinearEdgeIntersect test... ", &test_RigidShape2DHelper::Test_CollinearEdgeIntersect);
	passedTests += test_RigidShape2DHelper::RunTest("RigidShape2DHelper - IdenticalPointsIntersect test... ", &test_RigidShape2DHelper::Test_IdenticalPointIntersect);
	passedTests += test_RigidShape2DHelper::RunTest("RigidShape2DHelper - EntirelyWithinBoundsIntersect test... ", &test_RigidShape2DHelper::Test_EntirelyWithinBoundsIntersect);

	cout << endl;
	cout << "RigidShape2DHelper - Tests finished!" << endl;
	cout << passedTests << " out of " << _totalTests << " passed!" << endl;
}



bool test_RigidShape2DHelper::RunTest(const char* consoleText, function<bool()> testFunc)
{
	bool testPassed = testFunc();

	cout << consoleText << (testPassed ? "PASSED!" : "FAILED!") << endl;

	return testPassed;
}


// Test: That two shapes entirely seperate will not trigger an intersection
//
// Case: Neither shape overlap in any way
bool test_RigidShape2DHelper::Test_NoIntersect()
{
	std::vector<Vector2>shapeACoords({ Vector2(-2, -2),
										Vector2(-2, -1),
										Vector2(-1, -1),
										Vector2(-1, -2) });
	RigidShape2D shapeA(shapeACoords);

	std::vector<Vector2>shapeBCoords({ Vector2(1, 1),
										Vector2(1, 2),
										Vector2(2, 2),
										Vector2(2, 1) });
	RigidShape2D shapeB(shapeBCoords);

	return !RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
}


// Test: That a point existing entirely inside of another shape will trigger an intersection
//
// Case: The point (0,0) in shapeB lives entirely within the bounds of shapeA
bool test_RigidShape2DHelper::Test_SimpleIntersect()
{
	std::vector<Vector2>shapeACoords({ Vector2(-1, -1),
										Vector2(-1, 1),
										Vector2(1, 1),
										Vector2(1, -1) });
	RigidShape2D shapeA(shapeACoords);

	std::vector<Vector2>shapeBCoords({ Vector2(0, 0),
										Vector2(0, 2),
										Vector2(2, 2),
										Vector2(2, 0) });
	RigidShape2D shapeB(shapeBCoords);

	return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
}


//Test: That a single point lying on the line of another shape will trigger an intersection
//
//Case: The point (1,0) in shapeB lies on the line between (1,1) -> (1,-1) on shapeA
bool test_RigidShape2DHelper::Test_CollinearPointIntersect()
{
	std::vector<Vector2>shapeACoords({ Vector2(-1, -1),
										Vector2(-1, 1),
										Vector2(1, 1),
										Vector2(1, -1) });
	RigidShape2D shapeA(shapeACoords);

	std::vector<Vector2>shapeBCoords({ Vector2(1, 0),
										Vector2(2, 1),
										Vector2(3, 0),
										Vector2(2, -1) });
	RigidShape2D shapeB(shapeBCoords);

	return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
}



//Test: That an entire line overlapping the line of another shape will trigger an intersection
//
//Case: The line (1,-2) -> (1,2) of shapeB lies along the line between (1,1) -> (1,-1) on shapeA
bool test_RigidShape2DHelper::Test_CollinearEdgeIntersect()
{
	std::vector<Vector2>shapeACoords({ Vector2(-1, -1),
										Vector2(-1, 1),
										Vector2(1, 1),
										Vector2(1, -1) });
	RigidShape2D shapeA(shapeACoords);

	std::vector<Vector2>shapeBCoords({ Vector2(1, -2),
										Vector2(1, 2),
										Vector2(2, 2),
										Vector2(2, -2) });
	RigidShape2D shapeB(shapeBCoords);

	return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
}



//Test: That a single point sharing the same point of another shape will trigger an intersection
//
//Case: Both shapeA and shapeB share the point (1,1)
bool test_RigidShape2DHelper::Test_IdenticalPointIntersect()
{
	std::vector<Vector2>shapeACoords({ Vector2(-1, -1),
										Vector2(-1, 1),
										Vector2(1, 1),
										Vector2(1, -1) });
	RigidShape2D shapeA(shapeACoords);

	std::vector<Vector2>shapeBCoords({ Vector2(1, 1),
										Vector2(1, 2),
										Vector2(2, 2),
										Vector2(2, 1) });
	RigidShape2D shapeB(shapeBCoords);

	return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
}



//Test: That a whole shape existing entirely within another shape will trigger an intersection
//
//Case: ShapeB existing entirely within shapeA
bool test_RigidShape2DHelper::Test_EntirelyWithinBoundsIntersect()
{
	std::vector<Vector2>shapeACoords({ Vector2(-1, -1),
										Vector2(-1, 1),
										Vector2(1, 1),
										Vector2(1, -1) });
	RigidShape2D shapeA(shapeACoords);

	std::vector<Vector2>shapeBCoords({ Vector2(-0.5, -0.5),
										Vector2(-0.5, 0.5),
										Vector2(0.5, 0.5),
										Vector2(0.5, -0.5) });
	RigidShape2D shapeB(shapeBCoords);

	return RigidShape2DHelper::DoShapesIntersect(shapeA, shapeB);
}