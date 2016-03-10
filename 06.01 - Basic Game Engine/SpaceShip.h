#pragma once



class SpaceShip
{

public:

	SpaceShip();
	~SpaceShip();

	void init();

	void updateRotation();
	void moveSpaceShip(int direction); //1 izq 2 Arriba 3 derecha 4 abajo]
									
};

