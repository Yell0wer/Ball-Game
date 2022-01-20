#include "stdafx.h"

AIControllerComponent::AIControllerComponent(class Enemy* actor) :
	ControllerComponent(actor),
	mState(ERest)
{
	mCooldown = 3.f;

	mShootPower = 23.f;
	mSpeedLim = 3.f;
}

void AIControllerComponent::Update(float delta)
{
	mIsGrounded = mOwner->IsGrounded(0.2f, 0.5f);
	mJumpGrounded = mOwner->IsGrounded(0.5f, 0.6f);

	if (mIsGrounded) mOwner->GetAnim()->PlayAnimation("idle" + mOwner->GetFacing(), 0, 0);
	else mOwner->GetAnim()->PlayAnimation("float" + mOwner->GetFacing(), 0, 0);

	mShootTimer += delta;

	b2Vec2 toPlayerUnit = mOwner->GetGame()->GetPlayer()->GetPos() - mOwner->GetPos();
	b2Vec2 toPlayer = toPlayerUnit;
	toPlayerUnit.Normalize();

	RayCastCallback rcc;
	mOwner->GetGame()->GetWorld()->RayCast(&rcc, mOwner->GetPos(), mOwner->GetGame()->GetPlayer()->GetPos() - toPlayerUnit);

	if (mState == EAttack) mOwner->SetFacing(mOwner->GetGame()->GetPlayer()->GetPos().x < mOwner->GetPos().x);

	if (toPlayer.Length() <= 10.f && !rcc.m_fixture)
	{
		toPlayerUnit.y += 0.2f;
		Shoot(toPlayerUnit);
		mState = EAttack;
		mOwner->GetBody()->DestroyFixture(mOwner->GetBody()->GetFixtureList());
		mOwner->SetCircle(0.5f, 1.f, 1.f);
		mMoving = 0;
	}
	else if (mState == EAttack)
	{
		Move(mOwner->GetGame()->GetPlayer()->GetPos().x < mOwner->GetPos().x, mOwner->GetBody());
		if (mMoving && std::abs(mOwner->GetBody()->GetLinearVelocity().x) < 0.1f && mJumpGrounded)
		{
			mJumpTimer += delta;
			mOwner->GetAnim()->PlayAnimation("jump" + mOwner->GetFacing(), 1, 3);
			Jump(delta, mOwner->GetBody());
		}
		mMoving = 1;
	}
	else if (mIsGrounded)
	{
		mOwner->GetBody()->DestroyFixture(mOwner->GetBody()->GetFixtureList());
		mOwner->SetCircle(0.5f, 1.f, 1.f);
	}
}