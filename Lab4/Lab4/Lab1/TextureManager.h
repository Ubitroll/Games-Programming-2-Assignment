#pragma once
#include <string>
#include <GL\glew.h>

class TextureManager
{
public:
	TextureManager();

	void Bind(unsigned int unit); // bind upto 32 textures
	void init(const std::string& fileName);

	~TextureManager();

protected:
private:

	GLuint textureHandler;
};

