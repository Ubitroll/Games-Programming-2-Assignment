#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Screen
{
public:
	Screen();
	~Screen();
	void initiateScreen();
	void swapBuffer();
	void clearScreen(float r, float g, float b, float a);

	float findWidth();
	float findHeight();

private:

	void error(std::string errorMessage);
	
	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window
	float widthOfScreen;
	float heightOfScreen;
};

