#include "stdafx.h"

Player::Player(class Game* game) : 
	Character(game)
{
	SetCircle(0.5f, 1.f, 1.f);
	mBody->GetFixtureList()->SetRestitution(0.3f);
	AddComponent(new ControllerComponent(this));

	mHealth = mBody->GetMass() * 127.3239518f; // funny constant

	// idle
	LoadAnim("idle", 10, 4);
	// float
	LoadAnim("float", 50, 1);
	// walk
	LoadAnim("walk", 24, 7);
	// jump
	LoadAnim("jump", 40, 6);
	// land
	LoadAnim("land", 60, 5);
}

void Player::UpdateActor(float delta)
{
	Character::UpdateActor(delta);
	// if (mHealth <= 0.f) mState = EDead;
}
