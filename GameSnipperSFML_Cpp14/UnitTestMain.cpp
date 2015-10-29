#include "stdafx.h"
#include "UnitTestMain.h"
#include "TestDemo.h"

UnitTestMain::UnitTestMain()
{
	RunTests(true);
}

void UnitTestMain::RunTests(bool enabled)
{
	if (!enabled)
		return;

	TestDemo td1;
}