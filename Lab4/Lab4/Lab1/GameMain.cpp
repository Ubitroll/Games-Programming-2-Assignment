#include "GameMain.h"
#include "View.h"
#include <iostream>
#include <string>



Vertex vertices[] = { Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
					Vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
					Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)) };

unsigned int indices[] = { 0, 1, 2 };

TransformManager transform;

GameMain::GameMain()
{
	state = GameState::PLAY;
	Screen* _gameDisplay = new Screen(); //new display
    Mesh* mesh1();
	Mesh* mesh2();
	TextureManager* texture();
	ShaderManager* shader();
}

GameMain::~GameMain()
{
}

void GameMain::run()
{
	initialise(); 
	gameLoop();
}

void GameMain::initialise()
{
	screen.initiateScreen(); 
	//mesh1.init(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0])); //size calcuated by number of bytes of an array / no bytes of one element
	mesh2.loadModel("..\\res\\monkey3.obj");
	
	texture.init("..\\res\\bricks.jpg"); //
	shader.init("..\\res\\shader"); //new shader

	myCamera.initialiseCamera(glm::vec3(0, 0, -5), 70.0f, (float)screen.findWidth()/screen.findHeight(), 0.01f, 1000.0f);
	counter = 0.0f;
}

void GameMain::gameLoop()
{
	while (state != GameState::EXIT)
	{
		input();
		drawGame();
	}
}

void GameMain::input()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				state = GameState::EXIT;
				break;
		}
	}
	
}


void GameMain::drawGame()
{
	screen.clearScreen(0.0f, 0.0f, 0.0f, 1.0f);
	
	transform.SetPos(glm::vec3(sinf(counter), 0.0, 0.0));
	transform.SetRot(glm::vec3(0.0, 0.0, counter * 0.05f));
	transform.SetScale(glm::vec3(sinf(counter), sinf(counter), sinf(counter)));

	shader.Bind();
	shader.Update(transform, myCamera);
	texture.Bind(0);
	//mesh1.draw();
	mesh2.draw();
	counter = counter + 0.001f;
				
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	screen.swapBuffer();
} 