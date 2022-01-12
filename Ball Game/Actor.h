#pragma once
#include "stdafx.h"

class Actor
{
public:
	Actor(class Game* game); // TODO: Actor state?
	virtual ~Actor();

	void Update(float delta);
	void UpdateComponents(float delta);
	virtual void UpdateActor(float delta);

	void Draw();

	void AddComponent(class Component* c);
	void RemoveComponent(class Component* c);

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	Vector2 GetForward() const { return Vector2(Math::Cos(mRot), Math::Sin(mRot)); }

	class Game* GetGame() const { return mGame; }
	const Vector2& GetPos() const { return mPos; }
	void SetPos(const Vector2& pos) { mPos = pos; mRecompute = 1; }
	float GetSca() const { return mSca; }
	void SetSca(float sca) { mSca = sca; mRecompute = 1; }
	float GetRot() const { return mRot; }
	void SetRot(float rot) { mRot = rot; mRecompute = 1; }

protected:
	Matrix4 mWorldTransform;
	Vector2 mPos;
	float mSca;
	float mRot;
	bool mRecompute;

	std::vector<class Component*> mComponents;
	class SpriteComponent* mSprite;
	class Game* mGame;
};

