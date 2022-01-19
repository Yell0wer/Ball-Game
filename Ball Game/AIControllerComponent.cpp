#include "stdafx.h"

AIControllerComponent::AIControllerComponent(class Enemy* actor) :
	ControllerComponent(actor)
{
	mCooldown = 3.f;

	mShootPower = 25.f;
}

void AIControllerComponent::Update(float delta)
{
	mOwner->GetAnim()->PlayAnimation("idle" + mOwner->GetFacing(), 0, 0);
	mTimer += delta;
	b2Vec2 toPlayerUnit = mOwner->GetGame()->GetPlayer()->GetPos() - mOwner->GetPos();
	b2Vec2 toPlayer = toPlayerUnit;
	toPlayerUnit.Normalize();
	RayCastCallback rcc;
	mOwner->GetGame()->GetWorld()->RayCast(&rcc, mOwner->GetPos(), mOwner->GetGame()->GetPlayer()->GetPos() - toPlayerUnit);
	if (toPlayer.Length() <= 10.f && !rcc.m_fixture)
	{
		toPlayerUnit.y += 0.2f;
		Shoot(toPlayerUnit);
	}
}