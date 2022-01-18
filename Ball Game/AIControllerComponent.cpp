#include "stdafx.h"

AIControllerComponent::AIControllerComponent(class Enemy* actor) :
	ControllerComponent(actor)
{
	mCooldown = 3.f;

	mShootPower = 25.f;
}

void AIControllerComponent::Update(float delta)
{
	mTimer += delta;
	b2Vec2 toPlayer = mOwner->GetGame()->GetPlayer()->GetPos() - mOwner->GetPos();
	if (toPlayer.Length() <= 10.f)
	{
		toPlayer.Normalize();
		toPlayer.y += 0.2f;
		Shoot(toPlayer);
	}
}