#include "stdafx.h"

Crate::Crate(class Game* game) :
	DynamicActor(game)
{
	SetBox(1.f, 1.f, 5.f, 0.f);
	LoadTex("Assets/crate2.png");
}

void Crate::UpdateActor(float delta)
{
	UpdateTrans(); // todo debug collision
}