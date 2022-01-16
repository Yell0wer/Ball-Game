#pragma once

class DynamicActor : public Actor
{
public:
	DynamicActor(class Game* game);

	b2Body* GetBody() const { return mBody; }

	void SetPos(const b2Vec2& pos) override { mBody->SetTransform(pos, mRot); UpdateTrans(); }

	void SetBox(float w, float h, float d, float f);
	void SetCircle(float r, float d, float f);

	virtual void OnCollision(float impact, uintptr_t obj);

protected:
	void UpdateTrans();
	b2Body* mBody;
};

