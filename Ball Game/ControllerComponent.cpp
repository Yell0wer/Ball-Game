#include "stdafx.h"

ControllerComponent::ControllerComponent(class DynamicActor* actor) :
	Component(actor),
	mSpeedLim(6.f),
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
	int x, y;
	mCurrMouse = SDL_GetMouseState(&x, &y);
	mMouseX = static_cast<float>(x);
	mMouseY = static_cast<float>(y);
	mMouseX -= static_cast<float>(mOwner->GetGame()->GetWindowWidth()) / 2.f;
	mMouseX /= 64.f;
	mMouseY = static_cast<float>(mOwner->GetGame()->GetWindowHeight()) / 2.f - mMouseY;
	mMouseY /= 64.f;
	mToMouse = b2Vec2(mMouseX - mOwner->GetPos().x, mMouseY - mOwner->GetPos().y);
	mToMouse.Normalize();
	memcpy(mCurrState, keyState, SDL_NUM_SCANCODES);
}

void ControllerComponent::Update(float delta)
{
	b2Body* body = mOwner->GetBody();
	b2Vec2 acc = b2Vec2(42.f, 0.f);
	if (mCurrState[mLeft])
	{
		body->GetFixtureList()->SetFriction(0.f);
		if (body->GetLinearVelocity().x > -mSpeedLim) body->ApplyForceToCenter(-acc, 1);
	}
	if (mCurrState[mRight])
	{
		body->GetFixtureList()->SetFriction(0.f);
		if (body->GetLinearVelocity().x < mSpeedLim) body->ApplyForceToCenter(acc, 1);
	}
	if (!mCurrState[mLeft] && !mCurrState[mRight] && IsGrounded()) {
		body->DestroyFixture(body->GetFixtureList());
		mOwner->SetCircle(0.5f, 1.f, 8.f);
	}

	if (IsGrounded()) mNumJumps = 1;
	if (GetKeyState(mJump) == EPressed && mNumJumps)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 6.f));
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
			new Projectile(mOwner->GetGame(), spawn, mToMouse);
		}
	}

	mPrevMouse = mCurrMouse;
	memcpy(mPrevState, mCurrState, SDL_NUM_SCANCODES);
}

bool ControllerComponent::IsGrounded()
{
	RayCastCallback rcc;
	b2Vec2 p2 = mOwner->GetPos();
	p2 += b2Vec2(0.f, -0.51f);
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