#include "stdafx.h"

Block::Block(class Game* game, float w, float h) :
	StaticActor(game),
	mWidth(w),
	mHeight(h)
{
	SetBox(w, h);
	LoadTex("Assets/block.png");
}

void Block::UpdateActor(float delta)
{
	UpdatePos();
}