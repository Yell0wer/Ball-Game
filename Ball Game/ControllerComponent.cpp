#include "stdafx.h"

ControllerComponent::ControllerComponent(class Actor* actor) :
	Component(actor)
{
	SetJump(SDL_SCANCODE_W);
	SetLeft(SDL_SCANCODE_A);
	SetCrouch(SDL_SCANCODE_S);
	SetRight(SDL_SCANCODE_D);
	SetShoot(SDL_SCANCODE_SPACE);
}

void ControllerComponent::ProcessInput(const uint8_t* keyState)
{
	if (keyState[mLeft]) mOwner->SetVel(mOwner->GetVel() - Vector2(.2f, 0.f));
	if (keyState[mRight]) mOwner->SetVel(mOwner->GetVel() + Vector2(.2f, 0.f));
	if (!keyState[mLeft] && !keyState[mRight]) mOwner->SetVel(Vector2(mOwner->GetVel().x * 0.9f, mOwner->GetVel().y)); // TODO: deltatime
	
	if(keyState[mJump]) mOwner->SetVel(Vector2(mOwner->GetVel().x, 10.f));
}