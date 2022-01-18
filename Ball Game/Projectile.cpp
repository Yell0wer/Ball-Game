#include "stdafx.h"

Projectile::Projectile(class Game* game, class Character* owner, b2Vec2 pos, b2Vec2 vel) :
	DynamicActor(game),
	mOwner(owner),
	mLifespan(3.f),
	mTimer(0.f)
{
	SetCircle(0.25f, 2.f, 1.f);
	mBody->GetFixtureList()->SetRestitution(0.8f);
	mBody->SetBullet(1);
	mBody->SetLinearVelocity(vel);
	SetPos(pos);
	if (dynamic_cast<Player*>(owner)) LoadTex("Assets/char/projl.png");
	if (dynamic_cast<Enemy*>(owner)) LoadTex("Assets/enemy/projl.png");
	ComputeWorldTransform();
}

void Projectile::UpdateActor(float delta)
{
	UpdateTrans();
	mTimer += delta;
	if (mTimer > mLifespan) mState = EDead;
}

void Projectile::OnCollision(float impact, uintptr_t ptr)
{
	int dmg = std::max(0.f, mBody->GetLinearVelocity().LengthSquared() * mBody->GetMass() / 10.f - 5.f);
	Character* obj = dynamic_cast<Character*>((Actor*)ptr);
	if (obj && dmg)
	{
		b2Vec2 toObj = obj->GetPos() - mPos;
		toObj *= 0.5f;
		if (dynamic_cast<Player*>(mOwner)) new Particle(mGame, "pop-r", 24, 5, mPos + toObj);
		if (dynamic_cast<Enemy*>(mOwner)) new Particle(mGame, "pop-p", 24, 5, mPos + toObj);
		mState = EDead;
	}
}