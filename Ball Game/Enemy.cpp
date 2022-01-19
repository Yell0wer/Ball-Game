#include "stdafx.h"

Enemy::Enemy(class Game* game) :
	Character(game)
{
	SetCircle(0.5f, 1.f, 1.f);
	mBody->GetFixtureList()->SetRestitution(0.3f);

	mHealth = mBody->GetMass() * 127.3239518f; // funny constant

	// idle
	LoadAnim("enemy", "idle", 10, 4);
	// float
	LoadAnim("enemy", "float", 50, 1);
	// walk
	LoadAnim("enemy", "walk", 24, 7);
	// jump
	LoadAnim("enemy", "jump", 40, 6);
	// land
	LoadAnim("enemy", "land", 60, 5);

	AddComponent(new AIControllerComponent(this));
}


void Enemy::UpdateActor(float delta)
{
	Character::UpdateActor(delta);
}