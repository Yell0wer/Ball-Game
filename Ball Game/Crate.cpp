#include "stdafx.h"

Crate::Crate(class Game* game) :
	DynamicActor(game)
{
	SetBox(1.f, 1.f, 5.f, 1.f);
	LoadTex("Assets/crate3.png");
}

void Crate::UpdateActor(float delta)
{
	UpdateTrans(); // todo debug collision
}