#include "stdafx.h"
#include "TestDemo.h"
#include "UnitTest.h"

TestDemo::TestDemo()
{
	UnitTest::Compare("TestDemo, voorbeeld 1", 1, 1);
	UnitTest::Compare("TestDemo, voorbeeld 2", 1, 2);
	UnitTest::Compare("TestDemo, voorbeeld 3", true, false);
	UnitTest::Compare("TestDemo, voorbeeld 4", true, true);
	UnitTest::Compare("TestDemo, voorbeeld 5", "een", "een");
	UnitTest::Compare("TestDemo, voorbeeld 6", "een", "twee");

	std::string test = "een";
	UnitTest::Compare("TestDemo, voorbeeld 7", test, "een");
	UnitTest::Compare("TestDemo, voorbeeld 8", test, "twee");
}