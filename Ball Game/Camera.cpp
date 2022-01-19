#include "stdafx.h"

Camera::Camera(class Game* game) :
	mGame(game),
	mPos(game->GetPlayer()->GetPos())
{}

void Camera::Update(float delta)
{
	mVelLim.x = std::max(6.f, mGame->GetPlayer()->GetBody()->GetLinearVelocity().x);
	mVelLim.y = std::max(9.f, mGame->GetPlayer()->GetBody()->GetLinearVelocity().y);
	b2Vec2 toPlayer = mGame->GetPlayer()->GetPos() - mPos;

	if (toPlayer.x > 3.f) mVel.x += 32.f * delta;
	if (toPlayer.x < -3.f) mVel.x -= 32.f * delta;
	if (toPlayer.x <= 2.f && toPlayer.x >= -2.f) mVel.x *= 0.95f;
	mVel.x = std::min(mVel.x, mVelLim.x);
	mVel.x = std::max(mVel.x, -mVelLim.x);

	/* bruh
	if (toPlayer.y > 5.f) mVel.y += 32.f * delta;
	if (toPlayer.y < -5.f) mVel.y -= 32.f * delta;
	if (toPlayer.y <= 3.f && toPlayer.y >= -3.f) mVel.y *= 0.95f;
	mVel.y = std::min(mVel.y, mVelLim.y);
	mVel.y = std::max(mVel.y, -mVelLim.y);
	*/ 

	mPos.x += mVel.x * delta;
	mPos.y += mVel.y * delta;
}