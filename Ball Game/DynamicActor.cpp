#include "stdafx.h"

DynamicActor::DynamicActor(class Game* game) : 
	Actor(game)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(mPos.x, mPos.y);
	mBody = mGame->GetWorld()->CreateBody(&bodyDef);
}

void DynamicActor::UpdatePos()
{
	mPos.x = mBody->GetPosition().x;
	mPos.y = mBody->GetPosition().y;
	mRecompute = 1;
}

void DynamicActor::SetBox(float w, float h)
{
	b2PolygonShape box;
	box.SetAsBox(w / 2, h / 2);
	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.f;
	fixture.friction = 0.f;
	mBody->CreateFixture(&fixture);
}

void DynamicActor::SetCircle(float r)
{
	b2CircleShape circle;
	circle.m_radius = r;
	b2FixtureDef fixture;
	fixture.shape = &circle;
	fixture.density = 1.f;
	fixture.friction = 0.f;
	mBody->CreateFixture(&fixture);
}