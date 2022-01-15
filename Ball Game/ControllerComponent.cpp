#include "stdafx.h"

ControllerComponent::ControllerComponent(class DynamicActor* actor) :
	Component(actor),
	mSpeedLim(4.f),
	mNumJumps(1)
{
	mOwner = actor;

	SetJump(SDL_SCANCODE_W);
	SetLeft(SDL_SCANCODE_A);
	SetCrouch(SDL_SCANCODE_S);
	SetRight(SDL_SCANCODE_D);
	SetShoot(SDL_SCANCODE_SPACE);
	mUpdateOrder = 0;
}

void ControllerComponent::ProcessInput(const uint8_t* keyState)
{
	// todo screenwidth
	int x, y;
	mCurrMouse = SDL_GetMouseState(&x, &y);
	mMouseX = static_cast<float>(x);
	mMouseY = static_cast<float>(y);
	mMouseX -= 512.f;
	mMouseX /= 64.f;
	mMouseY = 384.f - mMouseY;
	mMouseY /= 64.f;
	mToMouse = b2Vec2(mMouseX - mOwner->GetPos().x, mMouseY - mOwner->GetPos().y);
	mToMouse.Normalize();
	memcpy(mCurrState, keyState, SDL_NUM_SCANCODES);
}

void ControllerComponent::Update(float delta)
{
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

	if (IsGrounded()) mNumJumps = 1;
	if (GetKeyState(mJump) == EPressed && mNumJumps)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 5.f));
		mNumJumps--;
	}

	if (GetMouseButtonState(SDL_BUTTON_LEFT) == EPressed)
	{
		RayCastCallback rcc;
		b2Vec2 spawn = mOwner->GetPos();
		spawn += mToMouse;
		mOwner->GetGame()->GetWorld()->RayCast(&rcc, mOwner->GetPos(), spawn);
		spawn -= mToMouse;
		mToMouse *= 0.75f;
		spawn += mToMouse;
		if (!rcc.m_fixture)
		{
			mToMouse *= 15.f;
			Projectile* p = new Projectile(mOwner->GetGame(), spawn, mToMouse);
		}
	}

	mPrevMouse = mCurrMouse;
	memcpy(mPrevState, mCurrState, SDL_NUM_SCANCODES);
}

bool ControllerComponent::IsGrounded()
{
	RayCastCallback rcc;
	b2Vec2 p2 = mOwner->GetPos();
	p2 += b2Vec2(0.f, -0.6f);
	mOwner->GetGame()->GetWorld()->RayCast(&rcc, mOwner->GetPos(), p2);
	return rcc.m_fixture;
}

ButtonState ControllerComponent::GetKeyState(SDL_Scancode key) const
{
	if (mPrevState[key])
	{
		if (mCurrState[key]) return EHeld;
		else return EReleased;
	}
	else
	{
		if (mCurrState[key]) return EPressed;
		else return ENone;
	}
}

ButtonState ControllerComponent::GetMouseButtonState(int button) const
{
	if (mPrevMouse & SDL_BUTTON(button))
	{
		if (mCurrMouse & SDL_BUTTON(button)) return EHeld;
		else return EReleased;
	}
	else
	{
		if (mCurrMouse & SDL_BUTTON(button)) return EPressed;
		else return ENone;
	}
}