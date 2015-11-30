#include "stdafx.h"
#include "UnitTestMain.h"
#include "TestDemo.h"
#include "TestLevelImporter.h"
#include "UnitTestGameObjectFactory.h"

UnitTestMain::UnitTestMain()
{
	RunTests(true);
}

void UnitTestMain::RunTests(bool enabled)
{
	if (!enabled)
		return;

	TestLevelImporter tli;
	UnitTestGameObjectFactory td2;
}