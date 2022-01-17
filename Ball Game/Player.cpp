#include "stdafx.h"

Player::Player(class Game* game) : 
	DynamicActor(game),
	mAnim(new AnimatedSpriteComponent(this)),
	mFacing(0)
{
	mBody->SetFixedRotation(1);
	SetCircle(0.5f, 1.f, 1.f);
	mBody->GetFixtureList()->SetRestitution(0.3f);
	AddComponent(new ControllerComponent(this));

	mHealth = mBody->GetMass() * 127.3239518f;

	// idle
	LoadAnim("idle", 10, 4);
	// float
	LoadAnim("float", 50, 1);
	// walk
	LoadAnim("walk", 24, 7);
	// jump
	LoadAnim("jump", 40, 6); // todo fix jump animation
	// land
	LoadAnim("land", 60, 5);
}

void Player::UpdateActor(float delta)
{
	mAnim->Update(delta);
	UpdateTrans();
}

void Player::Draw()
{
	mAnim->Draw(mGame->GetShader());
}

void Player::OnCollision(float impact, uintptr_t obj)
{
	DynamicActor* ptr = (DynamicActor*)obj;
	Projectile* proj = dynamic_cast<Projectile*>(ptr);
	if (proj)
	{
		mHealth -= std::max(0.f, impact / 10.f - 5.f);
		printf("%f\n", mHealth);
	}
}

void Player::LoadAnim(const std::string& name, int fps, int frames)
{
	Animation* a = new Animation();
	a->FPS = fps;
	for (int i = 0; i < frames; i++)
	{
		Texture* t = new Texture();
		t->Load("Assets/char/char-" + name + "-r/" + std::to_string(i) + ".png");
		a->Frames.push_back(t);
	}
	mAnim->AddAnimation(name + "-r", a);
	Animation* b = new Animation();
	b->FPS = fps;
	for (int i = 0; i < frames; i++)
	{
		Texture* t = new Texture();
		t->Load("Assets/char/char-" + name + "-l/" + std::to_string(i) + ".png");
		b->Frames.push_back(t);
	}
	mAnim->AddAnimation(name + "-l", b);
}
