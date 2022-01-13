#include "stdafx.h"

Player::Player(class Game* game) : 
	Actor(game)
{
	AddComponent(new MoveComponent(this));
	AddComponent(new ControllerComponent(this));
	LoadTex("Assets/char.png");
}

void Player::UpdateActor(float delta)
{
	if (mPos.y < 0.f) mPos.y = 0.f; // temp
}