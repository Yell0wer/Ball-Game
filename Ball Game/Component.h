#pragma once

class Component
{
public:
	Component(class Actor* actor, int order = 100);
	virtual ~Component();

	virtual void ProcessInput(const uint8_t* keyState);
	virtual void Update(float delta);

	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	class Actor* mOwner;
	int mUpdateOrder;
};

