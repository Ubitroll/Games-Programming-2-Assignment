#pragma once
#include <string>
#include <GL\glew.h>
#include "TransformManager.h"
#include "View.h"

class ShaderManager
{
public:
	ShaderManager();

	void Bind(); //Set gpu to use our shaders
	void Update(const TransformManager& transform, const View& camera);
	void init(const std::string& filename);

	std::string ShaderManager::LoadShader(const std::string& fileName);
	void ShaderManager::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint ShaderManager::CreateShader(const std::string& text, unsigned int type);

    ~ShaderManager();


protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
