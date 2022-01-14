#pragma once

enum State
{
	EActive,
	EPaused,
	EDead
};

class Actor
{
public:
	Actor(class Game* game);
	virtual ~Actor();
	
	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	void Update(float delta);
	void UpdateComponents(float delta);
	virtual void UpdateActor(float delta);

	void Draw();

	void AddComponent(class Component* c);
	void RemoveComponent(class Component* c);

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	void LoadTex(const std::string& file);
	
	b2Body* GetBody() const { return mBody; }
	class Game* GetGame() const { return mGame; }
	const Vector2& GetPos() const { return mPos; }
	float GetSca() const { return mSca; }
	float GetRot() const { return mRot; }
	void SetPos(const Vector2& pos) { mPos = pos; mRecompute = 1; }
	void SetSca(float sca) { mSca = sca; mRecompute = 1; }
	void SetRot(float rot) { mRot = rot; mRecompute = 1; }

protected:
	b2Body* mBody; // TODO physics background and static actors

	Matrix4 mWorldTransform;
	Vector2 mPos;
	float mSca;
	float mRot;
	bool mRecompute;

	State mState;
	std::vector<class Component*> mComponents;
	class SpriteComponent* mSprite;
	class Game* mGame;
};

