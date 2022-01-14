#include "stdafx.h"

Block::Block(class Game* game, float w, float h) :
	Actor(game),
	mWidth(w),
	mHeight(h)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(mPos.x, mPos.y);
	mBody = mGame->GetWorld()->CreateBody(&bodyDef);
	b2PolygonShape box;
	box.SetAsBox(w / 2, h / 2);
	mBody->CreateFixture(&box, 0.f);
	LoadTex("Assets/block.png");
}

void Block::UpdateActor(float delta)
{
	mBody->SetTransform(b2Vec2(mPos.x, mPos.y), mRot);
}