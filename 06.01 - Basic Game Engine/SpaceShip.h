#pragma once



class SpaceShip
{

public:

	SpaceShip();
	~SpaceShip();

	void init();

	void moveSpaceShip(bool direction); //True -> Derecha | Izquierda <- False [En un futuro podr� ser un INT si hay mas direcciones]
									
};

