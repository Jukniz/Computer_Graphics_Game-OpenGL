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

void SpaceShip::moveSpaceShip(bool direction)
{
	
	if (direction) {
		Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._translate += 0.01;
	}
	else {
		Game::getInstance()->getGeometry()->getGameElement(SPACE_SHIP)._translate -= 0.01;
	}




	}
