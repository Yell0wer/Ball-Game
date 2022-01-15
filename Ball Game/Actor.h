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
	Actor(class Game* game, int order = 100);
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
	
	int GetOrder() const { return mOrder; }
	class Game* GetGame() const { return mGame; }
	const b2Vec2& GetPos() const { return mPos; }
	float GetSca() const { return mSca; }
	float GetRot() const { return mRot; }
	virtual void SetPos(const b2Vec2& pos) { mPos = pos; mRecompute = 1; }
	virtual void SetSca(float sca) { mSca = sca; mRecompute = 1; }
	virtual void SetRot(float rot) { mRot = rot; mRecompute = 1; }

protected:
	Matrix4 mWorldTransform;
	b2Vec2 mPos;
	float mSca;
	float mRot;
	bool mRecompute;

	int mOrder;
	State mState;
	std::vector<class Component*> mComponents;
	class SpriteComponent* mSprite;
	class Game* mGame;
};

