#pragma once
class Enemy
{
private:
	float _velocity = 0.02;

public:
	Enemy();
	~Enemy();


	void init();
	void updateEnemyPosition();
};

