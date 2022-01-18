#include "stdafx.h"

ControllerComponent::ControllerComponent(class Player* actor) :
	Component(actor),
	mSpeedLim(6.f),
	mNumJumps(1),
	mCooldown(0.5f),
	mTimer(0.f),
	mJumpTimer(0.f),
	mAcceleration(b2Vec2(42.f, 0.f))
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
	ComputeMousePos(keyState);
	memcpy(mCurrKeyboardState, keyState, SDL_NUM_SCANCODES);
}

void ControllerComponent::ComputeMousePos(const uint8_t* keyState)
{
	int x, y;
	mCurrMouse = SDL_GetMouseState(&x, &y);
	mMouseX = static_cast<float>(x);
	mMouseY = static_cast<float>(y);
	mMouseX -= static_cast<float>(mOwner->GetGame()->GetWindowWidth()) / 2.f;
	mMouseX /= 64.f;
	mMouseY = static_cast<float>(mOwner->GetGame()->GetWindowHeight()) / 2.f - mMouseY;
	mMouseY /= 64.f;
	mToMouse = b2Vec2(mMouseX, mMouseY) + mOwner->GetGame()->GetCamera()->GetPos() - mOwner->GetPos();
	mToMouse.Normalize();
}

void ControllerComponent::Move(bool l, b2Body* body)
{
	body->DestroyFixture(body->GetFixtureList());
	mOwner->SetCircle(0.5f, 1.f, 0.f);
	if (body->GetLinearVelocity().x >= -mSpeedLim && l) body->ApplyForceToCenter(-mAcceleration, 1);
	if (body->GetLinearVelocity().x <= mSpeedLim && !l) body->ApplyForceToCenter(mAcceleration, 1);
	if (body->GetLinearVelocity().x != 0) mOwner->SetFacing(body->GetLinearVelocity().x < 0);
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

void ControllerComponent::Shoot()
{
	RayCastCallback rcc;
	b2Vec2 spawn = mOwner->GetPos();
	spawn += mToMouse;
	mOwner->GetGame()->GetWorld()->RayCast(&rcc, mOwner->GetPos(), spawn);
	spawn -= mToMouse;
	mToMouse *= 0.9f;
	spawn += mToMouse;
	if (!rcc.m_fixture)
	{
		mToMouse *= 80.f;
		new Projectile(mOwner->GetGame(), spawn, mToMouse);
		mTimer = 0.f;
	}
}

void ControllerComponent::Update(float delta) // todo encapsulate logic
{
	b2Body* body = mOwner->GetBody();
	mIsGrounded = mOwner->IsGrounded(0.2f, 0.5f);
	mJumpGrounded = mOwner->IsGrounded(0.9f, 0.6f);
	mTimer += delta;

	if (mIsGrounded) mOwner->GetAnim()->PlayAnimation("idle" + mOwner->GetFacing(), 0, 0);
	else mOwner->GetAnim()->PlayAnimation("float" + mOwner->GetFacing(), 0, 0);

	if (mCurrKeyboardState[mLeft]) Move(1, body);
	if (mCurrKeyboardState[mRight]) Move(0, body);

	if (mIsGrounded && !mCurrKeyboardState[mRight] && !mCurrKeyboardState[mLeft])
	{
		body->DestroyFixture(body->GetFixtureList());
		mOwner->SetCircle(0.5f, 1.f, 1.f);
	}

	if (mIsGrounded) mNumJumps = 1;
	if (GetKeyState(mJump) == EPressed && mJumpGrounded/* && mNumJumps*/)
	{
		mJumpTimer += delta;
		mOwner->GetAnim()->PlayAnimation("jump" + mOwner->GetFacing(), 1, 3);
	}
	Jump(delta, body);
	
	//if (GetKeyState(mCrouch) == EPressed)
	//{
	//	body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -20.f));
	//}

	if (mIsGrounded && !mWasGrounded) mOwner->GetAnim()->PlayAnimation("land" + mOwner->GetFacing(), 1, 2);

	if (GetMouseButtonState(SDL_BUTTON_LEFT) == EPressed && mTimer > mCooldown) Shoot();

	mWasGrounded = mIsGrounded;
	mPrevMouse = mCurrMouse;
	memcpy(mPrevKeyboardState, mCurrKeyboardState, SDL_NUM_SCANCODES);
}

ButtonState ControllerComponent::GetKeyState(SDL_Scancode key) const
{
	if (mPrevKeyboardState[key])
	{
		if (mCurrKeyboardState[key]) return EHeld;
		else return EReleased;
	}
	else
	{
		if (mCurrKeyboardState[key]) return EPressed;
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