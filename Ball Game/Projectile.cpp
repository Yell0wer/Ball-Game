#include "stdafx.h"

Projectile::Projectile(class Game* game, b2Vec2 pos, b2Vec2 vel) :
	DynamicActor(game)
{
	SetCircle(0.25f, 1.f, 1.f);
	mBody->SetBullet(1);
	mBody->SetLinearVelocity(vel);
	SetPos(pos);
	LoadTex("Assets/projl.png");
	ComputeWorldTransform();
}

void Projectile::UpdateActor(float delta)
{
	UpdateTrans(); // todo debug collision
}