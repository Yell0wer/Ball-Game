#include "stdafx.h"

Player::Player(class Game* game) : 
	DynamicActor(game)
{
	mBody->SetFixedRotation(1);
	SetCircle(0.5f, 1.f, 1.f);
	mBody->GetFixtureList()->SetRestitution(0.3f);
	AddComponent(new ControllerComponent(this));
	LoadTex("Assets/cyblob-l.png");

	mHealth = mBody->GetMass() * 127.3239518f;
}

void Player::UpdateActor(float delta)
{
	UpdateTrans();
}

void Player::OnCollision(float impact, uintptr_t obj)
{
	DynamicActor* ptr = (DynamicActor*)obj;
	Projectile* proj = dynamic_cast<Projectile*>(ptr);
	if (proj)
	{
		mHealth -= std::max(0.f, impact / 10.f - 10.f);
		printf("%f %f\n", mHealth);
	}
}