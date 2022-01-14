#pragma once

class Game
{
public:
	Game();
	// game loop
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* a);
	void RemoveActor(class Actor* a);

	class Shader* GetShader() const { return mShader; }
	b2World* GetWorld() const { return mWorld; }

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
	Uint32 mTickCount;
	class Shader* mShader;
	class VertexArray* mSquare;
	bool mIsRunning;
	std::vector<class Actor*> mActors;
	bool mActorsUpdating;
	std::vector<class Actor*> mPending;

	// physics
	b2World* mWorld;
	int32 mVelIter = 8;
	int32 mPosIter = 3;
};