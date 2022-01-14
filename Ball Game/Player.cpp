#include "stdafx.h"

Player::Player(class Game* game) : 
	Actor(game)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(mPos.x, mPos.y);
	mBody = mGame->GetWorld()->CreateBody(&bodyDef);
	b2CircleShape circle;
	circle.m_radius = 0.5f;
	b2FixtureDef fixture;
	fixture.shape = &circle;
	fixture.density = 1.f;
	fixture.friction = 0.f;
	mBody->CreateFixture(&fixture);
	AddComponent(new ControllerComponent(this));
	LoadTex("Assets/char.png");
}

void Player::UpdateActor(float delta)
{
	mPos.x = mBody->GetPosition().x;
	mPos.y = mBody->GetPosition().y;
	mRecompute = 1;
}