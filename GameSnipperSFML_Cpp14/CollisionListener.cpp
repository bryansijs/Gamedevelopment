#include "stdafx.h"
#include "CollisionListener.h"
#include "GameObject.h"

CollisionListener::CollisionListener()
{
}


CollisionListener::~CollisionListener()
{
}

void CollisionListener::BeginContact(b2Contact * contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData) {
		static_cast<GameObject*>(bodyUserData)->startContact(contact->GetFixtureB());
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData) {
		static_cast<GameObject*>(bodyUserData)->startContact(contact->GetFixtureA());
	}
}

void CollisionListener::EndContact(b2Contact * contact)
{
	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	if (bodyUserData) {
		static_cast<GameObject*>(bodyUserData)->endContact(contact->GetFixtureB());
	}

	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	if (bodyUserData) {
		static_cast<GameObject*>(bodyUserData)->endContact(contact->GetFixtureA());
	}

}
