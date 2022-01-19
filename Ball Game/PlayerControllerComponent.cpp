#include "stdafx.h"

PlayerControllerComponent::PlayerControllerComponent(class Player* actor) :
	ControllerComponent(actor)
{
	SetJump(SDL_SCANCODE_W);
	SetLeft(SDL_SCANCODE_A);
	SetCrouch(SDL_SCANCODE_S);
	SetRight(SDL_SCANCODE_D);
	SetShoot(SDL_SCANCODE_SPACE);

	mShootPower = 30.f;
}

void PlayerControllerComponent::ProcessInput(const uint8_t* keyState)
{
	ComputeMousePos(keyState);
	memcpy(mCurrKeyboardState, keyState, SDL_NUM_SCANCODES);
}

void PlayerControllerComponent::Update(float delta) // todo encapsulate constants
{
	b2Body* body = mOwner->GetBody();
	mIsGrounded = mOwner->IsGrounded(0.2f, 0.5f);
	mJumpGrounded = mOwner->IsGrounded(0.5f, 0.6f);
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

	if (GetMouseButtonState(SDL_BUTTON_LEFT) == EPressed) Shoot(mToMouse);

	mWasGrounded = mIsGrounded;
	mPrevMouse = mCurrMouse;
	memcpy(mPrevKeyboardState, mCurrKeyboardState, SDL_NUM_SCANCODES);
}

void PlayerControllerComponent::ComputeMousePos(const uint8_t* keyState)
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
	printf("%f %f\n", mToMouse.x, mToMouse.y);
	mToMouse.Normalize();
}

ButtonState PlayerControllerComponent::GetKeyState(SDL_Scancode key) const
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

ButtonState PlayerControllerComponent::GetMouseButtonState(int button) const
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