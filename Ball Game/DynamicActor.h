#pragma once

class DynamicActor : public Actor
{
public:
	DynamicActor(class Game* game);

	b2Body* GetBody() const { return mBody; }

protected:
	void UpdatePos();
	void SetBox(float w, float h);
	void SetCircle(float r);
	b2Body* mBody;
};

