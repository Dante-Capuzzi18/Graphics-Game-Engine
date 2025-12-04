#include "Program.h"

Program::Program() : isRunning(false), window(nullptr), glContext(nullptr), shaderProgram(), sceneObjects(), screenWidth(), screenHeight(), mainCamera(nullptr) {}

void Program::Initialize(const char* name, int screenWidth, int screenHeight, bool IsFullscreen, bool IsDebugging)
{
	int flags = SDL_WINDOW_OPENGL + SDL_WINDOW_RESIZABLE;

	if (IsFullscreen == true)
	{
		this->screenWidth = 1920;
		this->screenHeight = 1080;
	}
	else
	{
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;
	}

	if (!IsDebugging) ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised..." << std::endl;

		//creating the window, opengl context, and shader program
		window = SDL_CreateWindow("Program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screenWidth, this->screenHeight, flags);
		glContext = SDL_GL_CreateContext(window);
		gladLoadGL();
		glViewport(0, 0, this->screenWidth, this->screenHeight);
		glClearColor(0.9294f, 0.7078f, 0.4819f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		std::cout << "Window Created..." << std::endl;

		//creating the default shader program
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		shaderProgram.CreateShaderProgram("default.vert", "default.frag");

		std::cout << "Contexts Initialised..." << std::endl;

		//creating default camera
		delete mainCamera;
		mainCamera = new Camera(45.0f, 0.1f, 100.0f, this->screenHeight, this->screenWidth);
		mainCamera->SetPosition(0.0f, 0.0f, -10.0f);

		isRunning = true;
		std::cout << "Program Starting..." << std::endl;
	}
	else
	{
		isRunning = false;

		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
	}
}

void Program::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}

	switch (event.type) {

	case SDL_WINDOWEVENT:

		//for when window resize detected
		if (event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			int windowWidth, windowHeight;
			windowWidth = event.window.data1;
			windowHeight = event.window.data2;

			mainCamera->SetScreenDimensions(windowWidth, windowHeight);
			glViewport(0, 0, windowWidth, windowHeight);
		}
		break;

	default:
		break;
	}
}

void Program::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram.Use();

	for (auto& obj : sceneObjects)
	{
		obj->Draw(shaderProgram);
	}

	mainCamera->Draw(shaderProgram);

	SDL_GL_SwapWindow(window);
}

void Program::Clean()
{
	for (auto& obj : sceneObjects)
	{
		obj->Delete();
	}

	shaderProgram.~ShaderProgram();
	SDL_DestroyWindow(window);
	SDL_Quit();

	std::cout << "Program Cleaned and Closed" << std::endl;
}

//code what you want to happen on start here
void Program::Start()
{

}

//code what you want to happen on update here
void Program::Update()
{
	
}
