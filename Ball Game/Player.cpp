#include "stdafx.h"

Player::Player(class Game* game) : 
	Actor(game)
{
	AddComponent(new MoveComponent(this));
	AddComponent(new ControllerComponent(this));
}

void Player::ActorInput(const uint8_t* keyState)
{

}

void Player::UpdateActor(float delta)
{
	if (mPos.y < 0.f) mPos.y = 0.f;
}