#include "stdafx.h"
#include "FilterEnum.h"

FilterEnum::create_map FilterEnum::vcreate_map = {
	{ "TILE", 0x001 },
	{ "ENEMY", 0x002 },
	{ "PLAYER", 0x004 },
	{ "OBJECT", 0x008 },
};