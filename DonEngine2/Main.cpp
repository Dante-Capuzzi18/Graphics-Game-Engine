#include "Program.h"

Program* program = nullptr;

int main(int agrc, char* argv[])
{
	const int FPS = 60;

	const int FrameDelay = 1000 / FPS;
	Uint32 FrameStart;
	int FrameTime;

	//initializing then starting the program
	std::unique_ptr<Program> program = std::make_unique<Program>();
	program->Initialize("Program", 800, 650, false, true);
	program->Start();

	//the main while loop for the program
	while (program->IsRunning())
	{
		FrameStart = SDL_GetTicks();

		program->HandleEvents();
		program->Update();
		program->Render();

		FrameTime = SDL_GetTicks() - FrameStart;

		if (FrameDelay > FrameTime)
		{
			SDL_Delay(FrameDelay - FrameTime);
		}
	}

	program->Clean();
	return 0;
}