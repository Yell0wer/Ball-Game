#include "stdafx.h"

ControllerComponent::ControllerComponent(class Actor* actor) :
	Component(actor),
	mSpeedLim(4.f)
{
	SetJump(SDL_SCANCODE_W);
	SetLeft(SDL_SCANCODE_A);
	SetCrouch(SDL_SCANCODE_S);
	SetRight(SDL_SCANCODE_D);
	SetShoot(SDL_SCANCODE_SPACE);
	mUpdateOrder = 0;
}

void ControllerComponent::ProcessInput(const uint8_t* keyState)
{
	memcpy(mCurrState, keyState, SDL_NUM_SCANCODES);
}

void ControllerComponent::Update(float delta)
{
	/*Vector2 vel = mOwner->GetVel();
	if (mCurrState[mLeft]) vel.x -= 256.f * delta;
	else if (vel.x < 0)
		vel.x += 128.f * delta;
	if (mCurrState[mRight]) vel.x += 256.f * delta;
	else if (vel.x > 0) 
		vel.x -= 128.f * delta;
	if (abs(vel.x)<4.f) vel.x = 0.f;
	vel.x = std::max(-mSpeedLim, vel.x);
	vel.x = std::min(mSpeedLim, vel.x);
	mOwner->SetVel(vel);

	if (GetKeyState(mJump) == EPressed && IsGrounded())
		mOwner->SetVel(Vector2(mOwner->GetVel().x, 350.f));

	memcpy(mPrevState, mCurrState, SDL_NUM_SCANCODES);*/
	b2Body* body = mOwner->GetBody();
	if (mCurrState[mLeft])
		body->ApplyForceToCenter(b2Vec2(-8.f, 0.f), 1);
	else if (body->GetLinearVelocity().x < 0)
		body->ApplyForceToCenter(b2Vec2(8.f, 0.f), 1);
	if (mCurrState[mRight])
		body->ApplyForceToCenter(b2Vec2(8.f, 0.f), 1);
	else if (body->GetLinearVelocity().x > 0)
		body->ApplyForceToCenter(b2Vec2(-8.f, 0.f), 1);

	if (abs(body->GetLinearVelocity().x) < 0.1f) body->SetLinearVelocity(b2Vec2(0.f, body->GetLinearVelocity().y));
	if (body->GetLinearVelocity().x > mSpeedLim) body->SetLinearVelocity(b2Vec2(mSpeedLim, body->GetLinearVelocity().y));
	if (body->GetLinearVelocity().x < -mSpeedLim) body->SetLinearVelocity(b2Vec2(-mSpeedLim, body->GetLinearVelocity().y));

	if (GetKeyState(mJump) == EPressed && IsGrounded())
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 5.f));

	memcpy(mPrevState, mCurrState, SDL_NUM_SCANCODES);
}

bool ControllerComponent::IsGrounded()
{
	// return mOwner->GetPos().y <= 0; // temp
	return true;
}

ButtonState ControllerComponent::GetKeyState(SDL_Scancode key) const
{
	if (!mPrevState[key])
	{
		if (!mCurrState[key]) return ENone;
		else return EPressed;
	}
	else
	{
		if (!mCurrState[key]) return EReleased;
		else return EHeld;
	}
}