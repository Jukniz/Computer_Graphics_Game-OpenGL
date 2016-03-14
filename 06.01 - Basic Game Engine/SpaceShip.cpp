#pragma once
#include "Game.h"


SpaceShip::SpaceShip()
{
	
}

	
SpaceShip::~SpaceShip()
{
}

void SpaceShip::init() {
	Game::getInstance()->getGeometry()->createGeometrySpaceShip();
}

void SpaceShip::updateRotation()
{
	if (Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._angle < 180) {
		Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._angle += 5;
		//Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._rotation.y += 1;
	}
	else if (Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._angle > 180) {
		Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._angle -= 5;
		//Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._rotation.y -= 1;
	}

}

void SpaceShip::moveSpaceShip(int direction)
{
	
	switch (direction)
	{
	case (1):
		Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._translate.x -= 0.01;
		Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._angle += 10;
		//Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._rotation.x = 0;
		//Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._rotation.y = 1;
		if (Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._angle > 270) {
			Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._angle = 270;
		}
		break;
	case (2) :
		Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._translate.y += 0.01;
		break;
	case (3) :
		Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._translate.x += 0.01;
		Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._angle -= 10;
		//Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._rotation.x = 0;
		//Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._rotation.y = 1;
		if (Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._angle < 90) {
			Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._angle = 90;
		}
		break;
	case (4) :
		Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._translate.y -= 0.01;
		break;
	default:
		break;
	}

	}
