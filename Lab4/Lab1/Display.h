#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class Display
{
public:
	Display();
	~Display();
	void initDisplay(); // Initialises display
	void swapBuffer(); // Generates and uses the swap buffer
	void clearDisplay(float r, float g, float b, float a); // Clears the display

	float getWidth(); // Method to retrieve screen width
	float getHeight(); // Methid to retrieve screen height

private:

	// Method to print an error message
	void returnError(std::string errorString);
	
	SDL_GLContext glContext; //global variable to hold the context
	SDL_Window* sdlWindow; //holds pointer to out window
	float screenWidth; // Variable for setting screen width
	float screenHeight; // Variable for setting screen height
};

