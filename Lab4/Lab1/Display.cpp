#include "Display.h"

// Constructor
Display::Display()
{
	sdlWindow = nullptr; //initialise to generate null access violation for debugging. 
	screenWidth = 1024.0f; // Sets screen width to 1024
	screenHeight = 768.0f;  // Sets screen height to 768
}

Display::~Display()
{
	SDL_GL_DeleteContext(glContext); // delete context
	SDL_DestroyWindow(sdlWindow); // detete window (make sure to delete the context and the window in the opposite order of creation in initDisplay())
	SDL_Quit();
}

float Display::getWidth() { return screenWidth; } // returns the screen width
float Display::getHeight() { return screenHeight; } // returns the screen height

// Method to ouput a message in the case of an error
void Display::returnError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

// Triggers the swap buffer
void Display::swapBuffer()
{
	SDL_GL_SwapWindow(sdlWindow); //swap buffers
}

// Clears the display
void Display::clearDisplay(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear colour and depth buffer - set colour to colour defined in glClearColor
}

// Initialises the display
void Display::initDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);// set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	// Create game window
	sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL); // create window

	// If the window is a nullptr output error message
	if (sdlWindow == nullptr)
	{
		returnError("window failed to create");
	}

	// Assign gl context
	glContext = SDL_GL_CreateContext(sdlWindow);

	// If gl context assigned incorrectly return error message 
	if (glContext == nullptr)
	{
		returnError("SDL_GL context failed to create");
	}
	// Initialise Glew
	GLenum error = glewInit();

	// IF glew initialised incorrectly output error message
	if (error != GLEW_OK)
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); //enable z-buffering 
	glEnable(GL_CULL_FACE); //dont draw faces that are not pointing at the camera

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}