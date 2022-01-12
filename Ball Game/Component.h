#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor* actor, int order = 100);
	virtual ~Component();

	virtual void Update(float delta);

	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	class Actor* mOwner;
	int mUpdateOrder;
};

