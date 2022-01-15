#pragma once

class DynamicActor : public Actor
{
public:
	DynamicActor(class Game* game);

	b2Body* GetBody() const { return mBody; }

	void SetPos(const b2Vec2& pos) override { mBody->SetTransform(pos, mRot); UpdateTrans(); }

protected:
	void UpdateTrans();
	void SetBox(float w, float h, float d, float f);
	void SetCircle(float r, float d, float f);
	b2Body* mBody;
};

