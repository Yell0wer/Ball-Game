#pragma once
#include "stdafx.h"

class Game
{
public:
	Game();
	// game loop
	bool Initialize();
	void RunLoop();
	void Shutdown();

	class Shader* GetShader() const { return mShader; }
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
	class VertexArray* mSquare;
	bool mIsRunning;
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPending;
};
