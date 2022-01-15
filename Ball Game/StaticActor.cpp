#include "stdafx.h"

StaticActor::StaticActor(class Game* game) :
	Actor(game)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(mPos.x, mPos.y);
	mBody = mGame->GetWorld()->CreateBody(&bodyDef);
}

void StaticActor::UpdateTrans()
{
	mBody->SetTransform(b2Vec2(mPos.x, mPos.y), mRot);
}

void StaticActor::SetBox(float w, float h, float f)
{
	b2PolygonShape box;
	box.SetAsBox(w / 2, h / 2);
	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.friction = f;
	mBody->CreateFixture(&fixture);
}

void StaticActor::SetCircle(float r, float f)
{
	b2CircleShape circle;
	circle.m_radius = r;
	b2FixtureDef fixture;
	fixture.shape = &circle;
	fixture.friction = f;
	mBody->CreateFixture(&fixture);
}