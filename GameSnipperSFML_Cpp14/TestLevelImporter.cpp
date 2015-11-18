#include "stdafx.h"
#include "TestLevelImporter.h"
#include "UnitTest.h"
#include "LevelImporter.h"

TestLevelImporter::TestLevelImporter()
{
	LevelImporter* levelImporter = new LevelImporter();
	UnitTest::Compare("TestLevelImporter, LevelImported", levelImporter->Import("./Resources/levels/UnitTestLevel.json"), true);
	UnitTest::Compare("TestLevelImporter, MusicPrepared", levelImporter->PrepareMusic("level1.ogg"), true);
	levelImporter->Prepare();
	UnitTest::Compare("TestLevelImporter, TileSets", levelImporter->tileSets.size(), 2);
	UnitTest::Compare("TestLevelImporter, Tiles", levelImporter->tiles.size(), 640);
	UnitTest::Compare("TestLevelImporter, GameObjects", levelImporter->game_objects.size(), 4);
}