#include "stdafx.h"

Particle::Particle(class Game* game, const std::string& name, int fps, int frames, b2Vec2 pos) :
	Actor(game),
	mAnim(new AnimatedSpriteComponent(this)),
	mTimer(0.f),
	mDuration(static_cast<float>(frames) / static_cast<float>(fps))
{
	Animation* a = new Animation();
	a->FPS = fps;
	for (int i = 0; i < frames; i++)
	{
		Texture* t = new Texture();
		t->Load("Assets/particle/" + name + "/" + std::to_string(i) + ".png"); // todo encapsulate fps and frames into file
		a->Frames.push_back(t);
	}
	mAnim->AddAnimation(name, a);
	mAnim->PlayAnimation(name, 1, 0);
	mPos = pos;
	ComputeWorldTransform();
}

void Particle::UpdateActor(float delta)
{
	mAnim->Update(delta);
	if (mTimer > mDuration) mState = EDead;
	mTimer += delta;
}

void Particle::Draw()
{
	mAnim->Draw(mGame->GetShader());
}