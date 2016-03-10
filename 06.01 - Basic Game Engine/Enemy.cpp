#pragma once
#include "Game.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::init()
{
	Game::getInstance()->getGeometry()->createGeometryCube();
}

void Enemy::updateEnemyPosition() {


	
	Game::getInstance()->getGeometry()->getGameElement(ENEMY_01)._translate.x += _velocity;

	if (Game::getInstance()->getGeometry()->getGameElement(ENEMY_01)._translate.x > 1 || Game::getInstance()->getGeometry()->getGameElement(ENEMY_01)._translate.x < -1) {
		Game::getInstance()->getGeometry()->getGameElement(ENEMY_01)._translate.y -= 0.05;
		_velocity = _velocity*-1; //Cambiamos el sentido del enemigo
	}

}