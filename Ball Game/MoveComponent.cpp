#include "stdafx.h"

MoveComponent::MoveComponent(class Actor* actor) :
	Component(actor),
	mIsGravity(1)
{}

void MoveComponent::Update(float delta)
{
	if (mIsGravity) mOwner->SetVel(mOwner->GetVel() + Vector2(0.f, -0.4f) * delta);
	mOwner->SetPos(mOwner->GetPos() + mOwner->GetVel() * delta);
}