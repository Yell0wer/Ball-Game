#include "stdafx.h"

ControllerComponent::ControllerComponent(class Actor* actor) :
	Component(actor),
	mSpeedLim(200.f)
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
}

bool ControllerComponent::IsGrounded()
{
	return mOwner->GetPos().y <= 0; // temp
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