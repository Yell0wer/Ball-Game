#include "Game.h"

Game::Game() {

}

bool Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		SDL_Log("Failed initializing SDL: %s\n", SDL_GetError());
		return 0;
	}
	mWindow = SDL_CreateWindow("Carl's Fantastic Ball Game", 0, 0, 1024, 768, 0);
	if (!mWindow) {
		SDL_Log("Failed creating window: %s\n", SDL_GetError());
		return 0;
	}
	mIsRunning = 1;
	return 1;
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput() {

}

void Game::UpdateGame() {

}

void Game::GenerateOutput() {

}