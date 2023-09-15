#include <iostream>
#include "RigidShape2DHelper.h"
#include "test_RigidShape2DHelper.cpp"



static const bool _isInTestMode = true;

int main()
{
	if (_isInTestMode)
		test_RigidShape2DHelper::RunAllTests();


}