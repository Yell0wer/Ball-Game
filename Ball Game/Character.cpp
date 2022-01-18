#include "stdafx.h"

Character::Character(class Game* game) :
	DynamicActor(game),
	mAnim(new AnimatedSpriteComponent(this)),
	mFacing(0)
{
	mBody->SetFixedRotation(1);
}

void Character::UpdateActor(float delta)
{
	if (mHealth <= 0.f) mState = EDead;
	mAnim->Update(delta);
	UpdateTrans();
}

void Character::Draw()
{
	mAnim->Draw(mGame->GetShader());
}

void Character::OnCollision(float impact, uintptr_t obj)
{
	Actor* ptr = (Actor*)obj;
	DynamicActor* proj = dynamic_cast<DynamicActor*>(ptr);
	if (proj)
	{
		mHealth -= std::max(0.f, impact / 10.f - 5.f);
		printf("%f\n", mHealth);
	}
}

void Character::LoadAnim(const std::string& base, const std::string& name, int fps, int frames)
{
	Animation* a = new Animation();
	a->FPS = fps;
	for (int i = 0; i < frames; i++)
	{
		Texture* t = new Texture();
		t->Load("Assets/" + base + "/" + name + "-r/" + std::to_string(i) + ".png");
		a->Frames.push_back(t);
	}
	mAnim->AddAnimation(name + "-r", a);
	Animation* b = new Animation();
	b->FPS = fps;
	for (int i = 0; i < frames; i++)
	{
		Texture* t = new Texture();
		t->Load("Assets/" + base + "/" + name + "-l/" + std::to_string(i) + ".png");
		b->Frames.push_back(t);
	}
	mAnim->AddAnimation(name + "-l", b);
}
