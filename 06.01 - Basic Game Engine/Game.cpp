#include "Game.h"


Game* Game::_instance = 0;

Game* Game::getInstance() {
	if (_instance == 0) {

		Game game("Free porno de tetas de lara croft", 700, 700, true, 60, false);
		if (_instance == 0) {
			throw std::exception("System is not able to allocate memory for the game engine");
		}

	}
	return _instance;
}


Game* Game::getInstance(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS){
	if (_instance == 0) {
		_instance = new Game(windowTitle, screenWidth, screenHeight,  enableLimiterFPS,  maxFPS,  printFPS);
		if (_instance == 0) {
			throw std::exception("System is not able to allocate memory for the game engine");
		}
	}
	return _instance;
}


/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS) :
	_windowTitle(windowTitle),
	_screenWidth(screenWidth),
	_screenHeight(screenHeight),
	_gameState(GameState::INIT),
	_camera(screenWidth, screenHeight),
	_fpsLimiter(enableLimiterFPS, maxFPS, printFPS) {


}

/**
* Destructor
*/
Game::~Game()
{
	delete _instance;
}

/*
* Game execution
*/
void Game::run() {
		//System initializations
	initSystems();
		//Start the game if all the elements are ready
	gameLoop();
}

/*
* Initializes all the game engine components
*/
void Game::initSystems() {
		//Create an Opengl window using SDL
	_window.create(_windowTitle, _screenWidth, _screenHeight, 0);		
		//Compile and Link shader
	initShaders();
		//Set up the openGL buffers
	_openGLBuffers.initializeBuffers(_colorProgram);
		//Load the current scenario
	_gameElements.loadGameElements("./resources/scene2D.txt");


	
	_enemy.init();
	_spaceShip.init();

}

/*
* Initialize the shaders:
* Compiles, sets the variables between C++ and the Shader program and links the shader program
*/
void Game::initShaders() {
		//Compile the shaders
	_colorProgram.addShader(GL_VERTEX_SHADER, "./resources/shaders/vertex-shader.txt");
	_colorProgram.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/fragment-shader.txt");
	_colorProgram.compileShaders();
		//Attributes must be added before linking the code
	_colorProgram.addAttribute("vertexPositionGame");
	_colorProgram.addAttribute("vertexColor");
		//Link the compiled shaders
	_colorProgram.linkShaders();
		//Bind the uniform variables. You must enable shaders before gettting the uniforme variable location
	_colorProgram.use();
	_modelMatrixUniform = _colorProgram.getUniformLocation("modelMatrix");
	_viewMatrixUniform= _colorProgram.getUniformLocation("viewMatrix");
	_projectionMatrixUniform = _colorProgram.getUniformLocation("projectionMatrix");
	_colorProgram.unuse();
}

/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	_gameState = GameState::PLAY;
	while (_gameState != GameState::EXIT) {		
			//Start synchronization between refresh rate and frame rate
		_fpsLimiter.startSynchronization();
			//Process the input information (keyboard and mouse)
		processInput();
			//Execute the player actions (keyboard and mouse)
		executePlayerCommands();
			//Update the game status
		doPhysics();
			//Draw the objects on the screen
		renderGame();	
			//Force synchronization
		_fpsLimiter.forceSynchronization();
	}
}

/*
* Processes input with SDL
*/
void Game::processInput() {
	_inputManager.update();
	//Review https://wiki.libsdl.org/SDL_Event to see the different kind of events
	//Moreover, table show the property affected for each event type
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		default:
			break;
		}
	}

}


/**
* Executes the actions sent by the user by means of the keyboard and mouse
*/
void Game::executePlayerCommands() {
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){
		glm::ivec2 mouseCoords = _inputManager.getMouseCoords();
		cout << mouseCoords.x << ", " << mouseCoords.y << endl;
	}

	if (_inputManager.isKeyDown(SDLK_w) || _inputManager.isKeyDown(SDLK_UP)) {
		_spaceShip.moveSpaceShip(2);
	}

	if (_inputManager.isKeyDown(SDLK_a) || _inputManager.isKeyDown(SDLK_LEFT)) {
		_spaceShip.moveSpaceShip(1);
	}


	if (_inputManager.isKeyDown(SDLK_s) || _inputManager.isKeyDown(SDLK_DOWN)) {
		_spaceShip.moveSpaceShip(4);
	}

	if (_inputManager.isKeyDown(SDLK_d) || _inputManager.isKeyDown(SDLK_RIGHT)) {
		_spaceShip.moveSpaceShip(3);
	}
	

}

/*
* Update the game objects based on the physics
*/
void Game::doPhysics() {

	_enemy.updateEnemyPosition();
	_spaceShip.updateRotation();
	
}

/**
* Draw the sprites on the screen
*/
void Game::renderGame() {
			//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Bind the GLSL program. Only one code GLSL can be used at the same time
	_colorProgram.use();

	_camera.perspectiveProjection();

	GameObject currentElement; // Variable temporal
	
	glUniformMatrix4fv(_viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera.getViewMatrix()));	
	glUniformMatrix4fv(_projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(_camera.getProjectionMatrix()));

	//For each one of the elements: Each object MUST BE RENDERED based on its position, rotation and scale data
	for (int i = 0; i < _gameElements.getNumGameElements(); i++) {			
		currentElement = _gameElements.getGameElement(i);

		glm::mat4 modelMatrix; //Indentity matrix
		
		modelMatrix = glm::translate(modelMatrix, currentElement._translate);
		//The fvec3 rotation vector only has sense if angle is different to 0
		if (currentElement._angle != 0) {
			modelMatrix = glm::rotate(modelMatrix, glm::radians(currentElement._angle), currentElement._rotation);
		}

		modelMatrix = glm::scale(modelMatrix, currentElement._scale);
		//Pass the model matrix
		
		glUniformMatrix4fv(_modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		_openGLBuffers.sendDataToGPU(_gameElements.getData(currentElement._objectType), _gameElements.getNumVertices(currentElement._objectType));
			
	}


	
	//Unbind the program
	_colorProgram.unuse();

	//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();
}

Geometry* Game::getGeometry()
{
	return &_gameElements;
}


