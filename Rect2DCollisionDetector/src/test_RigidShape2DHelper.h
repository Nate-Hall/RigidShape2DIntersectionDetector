#pragma once

#include <functional>

class test_RigidShape2DHelper
{
public:
	static void RunAllTests();

	static bool RunTest(const char*, std::function<bool()>);

	static bool Test_NoIntersect();
	static bool Test_SimpleIntersect();
	static bool Test_CollinearPointIntersect();
	static bool Test_CollinearEdgeIntersect();
	static bool Test_IdenticalPointIntersect();
	static bool Test_EntirelyWithinBoundsIntersect();
};