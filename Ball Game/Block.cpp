#include "stdafx.h"

Block::Block(class Game* game, float w, float h, const std::string& tex) :
	StaticActor(game),
	mWidth(w),
	mHeight(h)
{
	SetBox(w, h, 1.f);
	LoadTex(tex);
}

void Block::UpdateActor(float delta)
{
	UpdateTrans();
}