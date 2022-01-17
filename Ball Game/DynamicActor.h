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

	bool IsGrounded(float w, float h);

protected:
	void UpdateTrans();
	b2Body* mBody;
};

class QueryCallback : public b2QueryCallback
{
public:
	QueryCallback() {}

	int m_found = 0;

	bool ReportFixture(b2Fixture* fixture)
	{
		m_found++;
		return 1;
	}
};