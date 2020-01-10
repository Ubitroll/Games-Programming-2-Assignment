#pragma once

#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class Audio
{
	// Set Up data Strut for audio buffer
	struct data {
		int sourceID, bufferID;
		char* buffer;
		std::string name;
		data(unsigned int sI, unsigned int bI, char* b, const char* n)
		{
			this->sourceID = sI;
			this->bufferID = bI;
			this->buffer = b;
			this->name = n;
		}

	};

	// Creates a point in 3D space with coordinates x, y, z
	struct Vector3
	{
		float x, y, z;
	};

	// Loads OpenAL
	std::vector<data> datas;
	ALCcontext* context; //used to set up context
	ALCdevice *device;
	bool isBigEndian();
	int convertToInt(char* buffer, int length);
	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size);

public:
	Audio();
	~Audio();
	unsigned int loadSound(const char* filename); // Method to laod sound
	void deleteSound(unsigned int id); // Method to delete sound
	void playSound(unsigned int id); // Method to play sounds
	void playSound(unsigned int id, glm::vec3& pos); // Method to play sounds from a specific location
	void stopSound(unsigned int id); // Method to stop sound
	void setlistener(glm::vec3& pos, glm::vec3& camLookAt); // Method to set Listener

private:
	
};

