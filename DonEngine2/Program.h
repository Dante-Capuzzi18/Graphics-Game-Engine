#ifndef PROGRAM
#define PROGRAM

#include <glad/glad.h>
#include <glm/glm/glm.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <glm/glm/gtc/matrix_transform.hpp>

#include "ShaderProgram.h"
#include "SimObject.h"
#include "Camera.h"
#include "Model.h"

//The core of the project that uses methods to run in main
class Program
{
public:
	Program();

	void Initialize(const char* name, int screenWidth, int screenHeight, bool IsFullscreen, bool IsDebugging); //will initialize the window and program object

	void Start(); //will be called once after initializing the program

	void HandleEvents(); //will handle events like inputs
	void Update(); //will update things like positions/rotations/etc
	void Render(); //renders everything to the screen
	void Clean(); //cleans up unused things from memory and stuff like that

	bool IsRunning() { return isRunning; } //will tell whether or not the program is running to tell the window to close

private:
	bool isRunning;

	int screenWidth;
	int screenHeight;

	SDL_Window* window;
	SDL_GLContext glContext;
	ShaderProgram shaderProgram;

	//Scene Contents: SimObject Derivitives, Scripts, UI
	std::vector<SimObject*> sceneObjects;
	Camera* mainCamera;
};
#endif // PROGRAM