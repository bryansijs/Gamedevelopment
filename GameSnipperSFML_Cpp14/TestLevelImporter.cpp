#include "stdafx.h"
#include "TestLevelImporter.h"
#include "UnitTest.h"
#include "LevelImporter.h"

TestLevelImporter::TestLevelImporter()
{
	LevelImporter* levelImporter = new LevelImporter();
	UnitTest::Compare("TestLevelImporter, LevelImported", levelImporter->Import("./Resources/levels/Level_New.json"), true);
	UnitTest::Compare("TestLevelImporter, LevelImported", levelImporter->PrepareMusic("level1.ogg"), true);
	UnitTest::Compare("TestLevelImporter, LevelImported", levelImporter->tileSets.size(), 3);
	//UnitTest::Compare("TestLevelImporter, LevelImported", , );
}