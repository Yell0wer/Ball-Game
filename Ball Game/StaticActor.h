#pragma once

class StaticActor : public Actor
{
public:
	StaticActor(class Game* game);

	b2Body* GetBody() const { return mBody; }

protected:
	void UpdateTrans();
	void SetBox(float w, float h, float f);
	void SetCircle(float r, float f);
	b2Body* mBody;
};

