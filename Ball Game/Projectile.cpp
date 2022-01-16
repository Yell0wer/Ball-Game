#include "stdafx.h"

Projectile::Projectile(class Game* game, b2Vec2 pos, b2Vec2 vel) :
	DynamicActor(game),
	mLifespan(3.f),
	mTimer(0.f)
{
	SetCircle(0.25f, 4.f, 1.f);
	mBody->GetFixtureList()->SetRestitution(0.8f);
	mBody->SetBullet(1);
	mBody->SetLinearVelocity(vel);
	SetPos(pos);
	LoadTex("Assets/projl.png");
	ComputeWorldTransform();
}

void Projectile::UpdateActor(float delta)
{
	UpdateTrans();
	mTimer += delta;
	if (mTimer > mLifespan)
	{
		mGame->GetWorld()->DestroyBody(mBody);
		delete this;
	}
}