#include "stdafx.h"

StaticActor::StaticActor(class Game* game) :
	Actor(game)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(mPos.x, mPos.y);
	mBody = mGame->GetWorld()->CreateBody(&bodyDef);
}

void StaticActor::UpdatePos()
{
	mBody->SetTransform(b2Vec2(mPos.x, mPos.y), mRot);
}

void StaticActor::SetBox(float w, float h)
{
	b2PolygonShape box;
	box.SetAsBox(w / 2, h / 2);
	mBody->CreateFixture(&box, 0.f);
}

void StaticActor::SetCircle(float r)
{
	b2CircleShape circle;
	circle.m_radius = r;
	mBody->CreateFixture(&circle, 0.f);
}