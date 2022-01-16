#include "stdafx.h"

DynamicActor::DynamicActor(class Game* game) : 
	Actor(game)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(mPos.x, mPos.y);
	bodyDef.userData.pointer = (uintptr_t)this;
	mBody = mGame->GetWorld()->CreateBody(&bodyDef);
}

void DynamicActor::UpdateTrans()
{
	mPos.x = mBody->GetPosition().x;
	mPos.y = mBody->GetPosition().y;
	mRot = mBody->GetAngle();
}

void DynamicActor::SetBox(float w, float h, float d, float f)
{
	b2PolygonShape box;
	box.SetAsBox(w / 2, h / 2, mPos, 0.f);
	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = d;
	fixture.friction = f;
	mBody->CreateFixture(&fixture);
}

void DynamicActor::SetCircle(float r, float d, float f)
{
	b2CircleShape circle;
	circle.m_radius = r;
	b2FixtureDef fixture;
	fixture.shape = &circle;
	fixture.density = d;
	fixture.friction = f;
	mBody->CreateFixture(&fixture);
}

void DynamicActor::OnCollision(float impact, uintptr_t obj) {}