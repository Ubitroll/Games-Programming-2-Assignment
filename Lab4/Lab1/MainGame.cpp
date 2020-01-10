#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
    Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
	Audio* audioDevice();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

// Initilaise the systems
void MainGame::initSystems()
{
	// initialise the display
	_gameDisplay.initDisplay();
	// Set collision sound
	whistle = audioDevice.loadSound("..\\res\\bang.wav");
	// set background music
	backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	
	// Load models
	mesh1.loadModel("..\\res\\monkey3.obj");
	mesh2.loadModel("..\\res\\kanga.obj");
	mesh3.loadModel("..\\res\\Doglowpolymodal.obj");
	
	// intialise the camera
	myCamera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
}

// Generates the gameloop as an Update feature
void MainGame::gameLoop()
{
	// While the game is not in the exit state
	while (_gameState != GameState::EXIT)
	{
		processInput(); // Process inputs
		drawGame(); // Draw the game
		collision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius()); // Detect collisions
		playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f)); // Play background music
	}
}

// Process the player input
void MainGame::processInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			// If Escape is pressed set the game state to exit
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}

// Method that detects collisions
bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	// Variable to figure the distance between two models
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	// If the distance becomes less than the radius where the bounding spheres overlap
	if (distance < (m1Rad + m2Rad))
	{
		// Set the camera to be a listener
		audioDevice.setlistener(myCamera.getPos(), m1Pos); //add bool to mesh
		playAudio(whistle, m1Pos); // Play audio to show collsiion
		return true;
	}
	else
	{
		return false;
	}
}

// Plays audio
void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
{
	
	ALint state; 
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		audioDevice.playSound(Source, pos);
	}
}

// Method to load game
void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);
	
	Shader shader("..\\res\\shader"); //new shader
	Texture texture("..\\res\\bricks.jpg"); //load texture
	Texture texture1("..\\res\\water.jpg"); //load texture
	
	// Sets up position, rotation and scale for Mesh 1
	transform.SetPos(glm::vec3(sinf(counter), 0.5, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	// Generates Mesh 1 in game
	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh1.draw();
	mesh1.updateSphereData(*transform.GetPos(), 0.62f);
	
	// Sets up position, rotation and scale for Mesh 2 
	transform.SetPos(glm::vec3(-sinf(counter), -0.5, -sinf(counter)*5));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	// Generates Mesh 2 in game
	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh2.draw();
	mesh2.updateSphereData(*transform.GetPos(), 0.62f);
	counter = counter + 0.05f;

	// Sets up position, rotation and scale for Mesh 1
	transform.SetPos(glm::vec3(-sinf(counter), 0, -sinf(counter) * 5));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 5));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	// Generates Mesh 3 in game
	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	mesh3.draw();
	mesh3.updateSphereData(*transform.GetPos(), 0.62f);
	counter = counter + 0.05f;
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 