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

	// blank
	Animation* blankR = new Animation(); // todo figure out reverse
	blankR->FPS = 1;
	Texture* t = new Texture();
	t->Load("Assets/char/char-r.png");
	blankR->Frames.push_back(t);
	mAnim->AddAnimation("", blankR);
	// idle
	Animation* idleR = new Animation();
	idleR->FPS = 10;
	for (int i = 0; i < 4; i++)
	{
		Texture* t = new Texture();
		t->Load("Assets/char/char-idle-r/" + std::to_string(i) + ".png");
		idleR->Frames.push_back(t);
	}
	mAnim->AddAnimation("idle-r", idleR);
	Animation* idleL = new Animation();
	idleL->FPS = 10;
	for (int i = 0; i < 4; i++)
	{
		Texture* t = new Texture();
		t->Load("Assets/char/char-idle-l/" + std::to_string(i) + ".png");
		idleL->Frames.push_back(t);
	}
	mAnim->AddAnimation("idle-l", idleL);
	// walk
	Animation* walkR = new Animation();
	walkR->FPS = 16;
	for (int i = 0; i < 7; i++)
	{
		Texture* t = new Texture();
		t->Load("Assets/char/char-walk-r/" + std::to_string(i) + ".png");
		walkR->Frames.push_back(t);
	}
	mAnim->AddAnimation("walk-r", walkR);
	Animation* walkL = new Animation();
	walkL->FPS = 16;
	for (int i = 0; i < 7; i++)
	{
		Texture* t = new Texture();
		t->Load("Assets/char/char-walk-l/" + std::to_string(i) + ".png");
		walkL->Frames.push_back(t);
	}
	mAnim->AddAnimation("walk-l", walkL);
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
		mHealth -= std::max(0.f, impact / 10.f - 10.f);
		printf("%f\n", mHealth);
	}
}