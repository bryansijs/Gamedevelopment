#include "stdafx.h"
#include "GameObject.h"

#include "DrawContainer.h"
#include "MoveContainer.h"
#include "NormalDrawBehaviour.h"
#include "MoveBehaviour.h"
#include "Tile.h"

//GameObject::GameObject(std::vector<DrawBehaviour*>* draws, std::string textureUrl)
GameObject::GameObject(DrawContainer *drawContainer, std::string textureUrl)
{
	this->drawContainer = drawContainer;
	this->drawBehaviour = { new NormalDrawBehaviour(this, 10, "./Resources/sprites/"+textureUrl) };
	this->drawContainer->AddBehaviour(this->drawBehaviour);
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::setDrawBehaviour(DrawBehaviour* newDrawBehaviour)
{
	this->drawBehaviour = newDrawBehaviour;
}

void GameObject::SetMoveBehaviour(MoveBehaviour* moveBehaviour)
{
	this->moveBehaviour = moveBehaviour;
}

bool GameObject::isColliding(std::vector<Tile> tiles, float newX, float newY)
{
	for (int i = 0; i < tiles.size(); i++) {


		if (isone == false) {
			this->position.x = 200;
			this->position.y = 200;
			isone = true;
		}

		if (tiles.at(i).isCollidable) {
			if (newX < (tiles.at(i).x_Position + 32) && (newX + 32) > tiles.at(i).x_Position && newY < (tiles.at(i).y_Position + 32) && (newY + 32) > tiles.at(i).y_Position) {
				std::cout << "collide" << std::endl;
				return true;
			}
		}


		//std::cout << this->position.x << "    " << this->position.y << std::endl;
		//if (tiles.at(i).isCollidable) {
		//	//std::cout << i << "Tile Position:" << "X:" << tiles.at(i).x_Position << " Y:" << tiles.at(i).y_Position << std::endl;
		//	if (newX > tiles.at(i).x_Position) {
		//		//std::cout << "2" << std::endl;
		//		if (newX < (tiles.at(i).x_Position + 32)) {
		//			//std::cout << "3" << std::endl;
		//			if (newY > tiles.at(i).y_Position) {
		//				//std::cout << "4" << std::endl;
		//				if (newY < (tiles.at(i).y_Position + 32)) {
		//					//std::cout << "5" << std::endl;
		//					std::cout << i<<"Tile Position:" << "X:" << tiles.at(i).x_Position << " Y:" << tiles.at(i).y_Position << std::endl;
		//					//std::cout << "Colliding" << std::endl;
		//					return true;
		//				}
		//			}
		//		}
		//	}

		//	if (newX + 32 > tiles.at(i).x_Position) {
		//			if (newX + 32 < (tiles.at(i).x_Position + 32)) {
		//				//std::cout << "6" << std::endl;
		//				if (newY + 32 > tiles.at(i).y_Position) {
		//					//std::cout << "7" << std::endl;
		//					if (newY + 32 < (tiles.at(i).y_Position + 32)) {
		//						//std::cout << "7" << std::endl;
		//						//std::cout << "Tile Position:" << "X:" << tiles.at(i).x_Position << " Y:" << tiles.at(i).y_Position << std::endl;
		//						//std::cout << "Colliding" << std::endl;
		//						return true;
		//					}
		//				}
		//			}
		//	}
		//}
	}
	//std::cout << "done" << std::endl;
	return false;
}

