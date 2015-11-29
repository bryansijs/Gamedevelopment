#include "stdafx.h"
#include "UnitTestMain.h"
#include "TestDemo.h"
#include "UnitTestGameObjectFactory.h"
#include "UnitTestLevelSequence.h"

UnitTestMain::UnitTestMain()
{
	RunTests(true);
}

void UnitTestMain::RunTests(bool enabled)
{
	if (!enabled)
		return;

//	TestDemo td1;
	UnitTestGameObjectFactory td2;
	UnitTestLevelSequence td3;
}