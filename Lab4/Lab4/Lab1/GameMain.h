#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Screen.h" 
#include "ShaderManager.h"
#include "MeshMaker.h"
#include "TextureManager.h"
#include "TransformManager.h"

enum class GameState{PLAY, EXIT};

class GameMain
{
public:
	GameMain();
	~GameMain();

	void run();

private:

	void initialise();
	void input();
	void gameLoop();
	void drawGame();

	Screen screen;
	GameState state;
	Mesh mesh1;
	Mesh mesh2;
	View myCamera;
	TextureManager texture; 
	ShaderManager shader;


	float counter;


};

