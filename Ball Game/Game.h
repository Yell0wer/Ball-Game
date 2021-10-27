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
	bool LoadShaders();
	// game objects
	SDL_Window* mWindow;
	SDL_GLContext mContext;
	const Uint8* mKeyboardState;
	Uint8 mTickCount;
	class Shader* mShader;
	bool mIsRunning;
};
