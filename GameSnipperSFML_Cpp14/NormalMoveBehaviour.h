#pragma once
#include "MoveBehaviour.h"

class NormalMoveBehaviour : public MoveBehaviour
{
public:
	NormalMoveBehaviour(GameObject* gameObject);
	~NormalMoveBehaviour();

	void Update();
	bool checkVisible(int screenX, int screenY);
};

