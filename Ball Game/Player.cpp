#include "stdafx.h"

Player::Player(class Game* game) : 
	DynamicActor(game)
{
	SetCircle(0.5f, 1.f, 0.f);
	AddComponent(new ControllerComponent(this));
	LoadTex("Assets/char.png");
}

void Player::UpdateActor(float delta)
{
	UpdateTrans();
}