#include "Geometry.h"
#include "ErrorManagement.h"
#include <iostream>
#include <fstream>

using namespace std;


/*
* Constructor 
*/
Geometry::Geometry(){
	
}


Geometry::~Geometry(){
	
}

/*
* Load the game elements from a text file
*/
void Geometry::loadGameElements(char fileName[100]) {
	/* Text format
	<number of game elements>
	<type of game element> <vec3 position> <angle> <vec3 rotation> <vec3 scale>
	*/
	GameObject tempObject;
	glm::vec3 vector3fElements;
	ifstream file;
	file.open(fileName);

	if (file.is_open()) {
		int numElements;
		file >> numElements;

		for (int i = 0; i < numElements; i++) {

			file >> tempObject._objectType;
			file >> tempObject._translate.x;
			file >> tempObject._translate.y;
			file >> tempObject._translate.z;
			file >> tempObject._angle;
			file >> tempObject._rotation.x;
			file >> tempObject._rotation.y;
			file >> tempObject._rotation.z;
			file >> tempObject._scale.x;
			file >> tempObject._scale.y;
			file >> tempObject._scale.z;

			_listOfObjects.push_back(tempObject);
		}

		file.close();
	}
	else {
		string message = "The file " + string(fileName) + " doesn't exists";
		ErrorManagement::errorRunTime(message);
	}

}

void Geometry::createGeometryCube() {

	//set position of every vertex
	for (int i = 0; i < NUMCUBE; i++) {
		std::cout << "hola "  << i<< std::endl;
		_numVertices[i] = 36;
		_verticesData[i] = new  Vertex[_numVertices[i]];

		_verticesData[i][0].setPosition(1, 1, -1); //Triangulo fondo
		_verticesData[i][1].setPosition(-1, -1, -1);
		_verticesData[i][2].setPosition(-1, 1, -1);

		_verticesData[i][3].setPosition(1, 1, -1); //triangulo fondo 2
		_verticesData[i][4].setPosition(1, -1, -1);
		_verticesData[i][5].setPosition(-1, -1, -1);

		_verticesData[i][6].setPosition(1, 1, 1); //lateral derecho 1
		_verticesData[i][7].setPosition(1, 1, -1);
		_verticesData[i][8].setPosition(1, -1, -1);

		_verticesData[i][9].setPosition(1, -1, 1); //lateral derecho 2
		_verticesData[i][10].setPosition(1, 1, 1);
		_verticesData[i][11].setPosition(1, -1, -1);

		_verticesData[i][12].setPosition(1, 1, 1); //superior 1
		_verticesData[i][13].setPosition(-1, 1, 1);
		_verticesData[i][14].setPosition(-1, 1, -1);

		_verticesData[i][15].setPosition(1, 1, 1);//superior 2
		_verticesData[i][16].setPosition(-1, 1, -1);
		_verticesData[i][17].setPosition(1, 1, -1);

		_verticesData[i][18].setPosition(-1, 1, -1);//lateral izquierdo 1
		_verticesData[i][19].setPosition(-1, 1, 1);
		_verticesData[i][20].setPosition(-1, -1, 1);

		_verticesData[i][21].setPosition(-1, 1, -1); //lateral izquierdo 2
		_verticesData[i][22].setPosition(-1, -1, 1);
		_verticesData[i][23].setPosition(-1, -1, -1);

		_verticesData[i][24].setPosition(1, -1, 1); //inferior 1
		_verticesData[i][25].setPosition(-1, -1, 1);
		_verticesData[i][26].setPosition(-1, -1, -1);

		_verticesData[i][27].setPosition(1, -1, 1); //inferior 2
		_verticesData[i][28].setPosition(-1, -1, -1);
		_verticesData[i][29].setPosition(1, -1, -1);

		_verticesData[i][30].setPosition(1, 1, 1);//Frontal 1	
		_verticesData[i][31].setPosition(-1, 1, 1);
		_verticesData[i][32].setPosition(-1, -1, 1);

		_verticesData[i][33].setPosition(1, 1, 1);//Frontal 2
		_verticesData[i][34].setPosition(-1, -1, 1);
		_verticesData[i][35].setPosition(1, -1, 1);
		

		//set color of every vertex
		switch (i)
		{
		case 0:
			for (int j = 0; j < _numVertices[i]; j++) _verticesData[i][j].setColor(0, 0, 255, 255);
			break;
		case 1:
			for (int j = 0; j < _numVertices[i]; j++) _verticesData[i][j].setColor(255, 0, 0, 255);
			break;
		default:
			for (int j = 0; j < _numVertices[i]; j++) _verticesData[i][j].setColor(255, 255, 255, 255);
			break;
		}
	}
}


void Geometry::createGeometrySpaceShip() {

	_numVertices[SPACE_SHIP] = 12;
	_verticesData[SPACE_SHIP] = new  Vertex[_numVertices[SPACE_SHIP]];


	_verticesData[SPACE_SHIP][0].setPosition(0, 1, 0);
	_verticesData[SPACE_SHIP][1].setPosition(-1, -1, 0);
	_verticesData[SPACE_SHIP][2].setPosition(1, -1, 0);


	_verticesData[SPACE_SHIP][3].setPosition(1, -1, 0);
	_verticesData[SPACE_SHIP][4].setPosition(0, 1, 0);
	_verticesData[SPACE_SHIP][5].setPosition(0, 0, 1);


	_verticesData[SPACE_SHIP][6].setPosition(0, 1, 0);
	_verticesData[SPACE_SHIP][7].setPosition(-1, -1, 0);
	_verticesData[SPACE_SHIP][8].setPosition(0, 0, 1);


	_verticesData[SPACE_SHIP][9].setPosition(-1, -1, 0);
	_verticesData[SPACE_SHIP][10].setPosition(1, -1, 0);
	_verticesData[SPACE_SHIP][11].setPosition(0, 0, 1);




	for (int j = 0; j < _numVertices[SPACE_SHIP]; j++) {

		if (j < 3) {
			_verticesData[SPACE_SHIP][j].setColor(255, 0, 0, 255);
		}
		else if (j < 6) {
			_verticesData[SPACE_SHIP][j].setColor(0, 255, 0, 255);
		}
		else if (j < 9) {
			_verticesData[SPACE_SHIP][j].setColor(0, 0, 255, 255);
		}
		else {
			_verticesData[SPACE_SHIP][j].setColor(255, 255, 255, 255);
		}
	
	}
}


/*
* Get the vertices data for an specific object
* @param objectID is the identifier of the requested object
* @return Vertex * is an array with all the vertices data
*/
Vertex * Geometry::getData(int objectID){
	return _verticesData[objectID];
}

/*
* Get the number of vertices for an specific object
* @param objectID is the identifier of the requested object
* @return int is the number of vertices
*/

int Geometry::getNumVertices(int objectID){
	return _numVertices[objectID];
}

/*
* Get the number of elements to render
*/
int Geometry::getNumGameElements() {
	return _listOfObjects.size();
}

/*
* Get the number of vertices of an specific game element
* @param objectID is the identifier of the requested object
*/
GameObject & Geometry::getGameElement(int objectID) {
	return (_listOfObjects[objectID]);
}

