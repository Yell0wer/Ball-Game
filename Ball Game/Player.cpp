#include "stdafx.h"

Player::Player(class Game* game) : 
	Character(game)
{
	SetCircle(0.5f, 1.f, 1.f);
	mBody->GetFixtureList()->SetRestitution(0.3f);
	AddComponent(new PlayerControllerComponent(this));

	mHealth = mBody->GetMass() * 127.3239518f; // funny constant

	// idle
	LoadAnim("char", "idle", 10, 4);
	// float
	LoadAnim("char", "float", 50, 1);
	// walk
	LoadAnim("char", "walk", 24, 7);
	// jump
	LoadAnim("char", "jump", 40, 6);
	// land
	LoadAnim("char", "land", 60, 5);
}

void Player::UpdateActor(float delta)
{
	Character::UpdateActor(delta);
}
