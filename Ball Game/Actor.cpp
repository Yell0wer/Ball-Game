#include "stdafx.h"

Actor::Actor(class Game* game) : 
	mGame(game),
	mPos(Vector2::Zero),
	mSca(4.f),
	mRot(0.f),
	mVel(Vector2(0.f, 0.f)),
	mSprite(new SpriteComponent(this)),
	mRecompute(1),
	mState(EActive)
{
	mGame->AddActor(this);
}

Actor::~Actor() 
{
	mGame->RemoveActor(this);
	delete mSprite;
	while (!mComponents.empty()) delete mComponents.back();
}

void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		for (auto c : mComponents) c->ProcessInput(keyState);
		ActorInput(keyState);
	}
}

void Actor::ActorInput(const uint8_t* keyState) {}

void Actor::Update(float delta)
{
	if (mState == EActive)
	{
		ComputeWorldTransform();
		UpdateComponents(delta);
		UpdateActor(delta);
		ComputeWorldTransform();
	}
	if (mState == EDead) delete this;
}

void Actor::UpdateComponents(float delta)
{
	for (auto c : mComponents) c->Update(delta);
}

void Actor::UpdateActor(float delta) {}

void Actor::Draw()
{
	mSprite->Draw(mGame->GetShader());
}

void Actor::ComputeWorldTransform()
{
	if (!mRecompute) return;
	mRecompute = 0;
	mWorldTransform = Matrix4::CreateScale(mSca) * Matrix4::CreateRotationZ(mRot) * Matrix4::CreateTranslation(Vector3(mPos.x, mPos.y, 0.f));
	// TODO: inform components
}

void Actor::LoadTex(const std::string& file)
{
	class Texture* tex = new Texture();
	tex->Load(file);
	mSprite->SetTexture(tex);
}

void Actor::AddComponent(class Component* c)
{
	auto i = mComponents.begin();
	for (; i != mComponents.end(); i++)
		if (c->GetUpdateOrder() > (*i)->GetUpdateOrder()) break;
	mComponents.insert(i, c);
}

void Actor::RemoveComponent(class Component* c)
{
	auto i = std::find(mComponents.begin(), mComponents.end(), c);
	if (i != mComponents.end()) mComponents.erase(i);
}