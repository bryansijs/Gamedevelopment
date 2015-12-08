#pragma once
#include <Box2D\Box2D.h>
class CollisionListener : public b2ContactListener
{
public:
	CollisionListener();
	~CollisionListener();

	void BeginContact(b2Contact* contact);

	void EndContact(b2Contact* contact);

};

