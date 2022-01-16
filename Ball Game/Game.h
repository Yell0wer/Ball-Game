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
	class Player* GetPlayer() const { return mPlayer; }
	class Camera* GetCamera() const { return mCamera; }
	int GetWindowWidth() const { return mWindowWidth; }
	int GetWindowHeight() const { return mWindowHeight; }
	int GetLevelWidth() const { return mWindowWidth; }
	int GetLevelHeight() const { return mWindowHeight; }

	std::string mLevel[500]; // todo make level private

private:
	// helper functions
	bool LoadLevel(const std::string& file);
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadShaders();
	// game objects
	class Camera* mCamera;
	class Player* mPlayer;
	SDL_Window* mWindow;
	int mWindowWidth, mWindowHeight;
	int mLevelWidth, mLevelHeight;
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