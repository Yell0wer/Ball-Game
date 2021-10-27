#include "Game.h"

Game::Game() {

}

bool Game::Initialize() {
	// initialize sdl
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		SDL_Log("Failed initializing SDL: %s\n", SDL_GetError());
		return 0;
	}
	// create sdl window
	mWindow = SDL_CreateWindow("Carl's Fantastic Ball Game", 0, 50, 1024, 768, 0);
	if (!mWindow) {
		SDL_Log("Failed creating window: %s\n", SDL_GetError());
		return 0;
	}
	// initialize renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	mIsRunning = 1;
	return 1;
}

void Game::RunLoop() {
	// game loop
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown() {
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput() {
	// poll for events
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	// update keyboard state
	mKeyboardState = SDL_GetKeyboardState(NULL);
}

void Game::UpdateGame() {
	// get delta time
	float delta = (SDL_GetTicks() - mTickCount) / 1000.f;
	// update tick count
	mTickCount = SDL_GetTicks();
	// limit framerate (15 fps)
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 64));
	// clamp delta time value
	if (delta > 0.5f) delta = 0.5f;
}

void Game::GenerateOutput() {
	// set color
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	// clear buffer
	SDL_RenderClear(mRenderer);
	// swap buffers
	SDL_RenderPresent(mRenderer);
}