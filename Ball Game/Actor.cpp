#include "Actor.h"

Actor::Actor(class Game* game) : 
	mGame(game),
	mPos(Vector2::Zero),
	mSca(1.f),
	mRot(0.f),
	mSprite(new SpriteComponent(this)),
	mRecompute(1)
{
	//mGame->AddActor(this); //TODO
}

Actor::~Actor() 
{
	//mGame->RemoveActor(this);
	while (!mComponents.empty()) delete mComponents.back();
}

void Actor::Update(float delta)
{
	ComputeWorldTransform();
	UpdateComponents(delta);
	UpdateActor(delta);
	ComputeWorldTransform();
}

void Actor::UpdateComponents(float delta)
{
	for (class Component* c : mComponents) c->Update(delta);
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