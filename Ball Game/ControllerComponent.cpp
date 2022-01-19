#include "stdafx.h"

ControllerComponent::ControllerComponent(class Character* actor) :
	Component(actor),
	mSpeedLim(6.f),
	mShootPower(35.f),
	mNumJumps(1),
	mCooldown(0.5f),
	mTimer(0.f),
	mJumpTimer(0.f),
	mAcceleration(b2Vec2(42.f, 0.f))
{
	mOwner = actor;
}

void ControllerComponent::Move(bool l, b2Body* body)
{
	body->DestroyFixture(body->GetFixtureList());
	mOwner->SetCircle(0.5f, 1.f, 0.f);
	if (body->GetLinearVelocity().x >= -mSpeedLim && l) body->ApplyForceToCenter(-mAcceleration, 1);
	if (body->GetLinearVelocity().x <= mSpeedLim && !l) body->ApplyForceToCenter(mAcceleration, 1);
	if (body->GetLinearVelocity().x > -0.1f && !l) mOwner->SetFacing(l);
	if (body->GetLinearVelocity().x < 0.1f && l) mOwner->SetFacing(l);
	if (mIsGrounded) mOwner->GetAnim()->PlayAnimation("walk" + mOwner->GetFacing(), 1, 1);
}

void ControllerComponent::Jump(float delta, b2Body* body)
{
	if (mJumpTimer) mJumpTimer += delta;
	if (mJumpTimer > 0.15f)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 10.f));
		mNumJumps--;
		mJumpTimer = 0.f;
	}
}

void ControllerComponent::Shoot(b2Vec2 dir)
{
	if (mTimer > mCooldown)
	{
		RayCastCallback rcc;
		b2Vec2 spawn = mOwner->GetPos();
		mOwner->GetGame()->GetWorld()->RayCast(&rcc, mOwner->GetPos(), spawn + dir);
		dir *= 0.9f;
		spawn += dir;
		dir.Normalize();
		if (!rcc.m_fixture)
		{
			dir *= mShootPower;
			new Projectile(mOwner->GetGame(), mOwner, spawn, dir);
			mTimer = 0.f;
		}
	}
}