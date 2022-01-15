#pragma once

class StaticActor : public Actor
{
public:
	StaticActor(class Game* game);

	b2Body* GetBody() const { return mBody; }

	void SetBox(float w, float h, float f);
	void SetCircle(float r, float f);

protected:
	void UpdateTrans();
	b2Body* mBody;
};

