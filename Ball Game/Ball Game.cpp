/*
== Carl's Fantastic Ball Game ==
A project by Carl Zhang
Submission for IB MYP year 5 personal project
*/
#define SDL_MAIN_HANDLED
#include "stdafx.h"

int main()
{
	SDL_SetMainReady();
	Game game;
	if (game.Initialize()) game.RunLoop();
	else exit(-1);
	game.Shutdown();
	exit(0);
}