#include "stdafx.h"

Player::Player(class Game* game) : 
	DynamicActor(game)
{
	mBody->SetFixedRotation(1);
	SetCircle(0.5f, 1.f, 5.f);
	AddComponent(new ControllerComponent(this));
	LoadTex("Assets/cyblob.png");
}

void Player::UpdateActor(float delta)
{
	UpdateTrans();
}