#include "stdafx.h"

Camera::Camera(class Game* game) :
	mGame(game),
	mPos(b2Vec2(0.f, -5.f))
{}

void Camera::Update(float delta)
{
	mPos = mGame->GetPlayer()->GetPos(); // temp
}