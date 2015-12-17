#include "stdafx.h"
#include "TestLevelImporter.h"
#include "UnitTest.h"
#include "LevelImporter.h"
#include "DrawContainer.h"
#include "GameObjectContainer.h"
#include "MoveContainer.h"

TestLevelImporter::TestLevelImporter()
{
	DrawContainer* drawcontainer = new DrawContainer();
	MoveContainer* movecontainer = new MoveContainer();
	GameObjectContainer* gameobjectcontainer = new GameObjectContainer();
	b2Vec2 gravity(0.f, 0.0f);
	b2World* world = { new b2World(gravity) };

	LevelImporter* levelImporter = new LevelImporter(drawcontainer, movecontainer, gameobjectcontainer, world);
	UnitTest::Compare("TestLevelImporter, LevelImported", levelImporter->Import("./Resources/test/UnitTestLevel.json"), true);
	UnitTest::Compare("TestLevelImporter, MusicPrepared", levelImporter->PrepareMusic("level1.ogg"), true);
	levelImporter->Prepare();
	Level* level = levelImporter->getLevel();
	UnitTest::Compare("TestLevelImporter, TileSets", level->tileSets.size(), 2);
	UnitTest::Compare("TestLevelImporter, GroundTiles", level->groundTiles.size(), 640);
	UnitTest::Compare("TestLevelImporter, RoofTiles", level->roofTiles.size(), 0);
	UnitTest::Compare("TestLevelImporter, GameObjects", level->game_objects.size(), 4);
}