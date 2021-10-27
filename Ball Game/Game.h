#pragma once
#include "stdafx.h"

class Game {
public:
	Game();
	// game loop
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	// helper functions
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// member variables
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	const Uint8* mKeyboardState;
	Uint8 mTickCount;
	bool mIsRunning;
};
