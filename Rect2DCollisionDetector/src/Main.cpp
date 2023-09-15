#include <iostream>
#include "RigidShape2DHelper.h"
#include "test_RigidShape2DHelper.h"



static const bool _isInTestMode = true;

int main()
{
	if (_isInTestMode)
		test_RigidShape2DHelper::RunAllTests();
}