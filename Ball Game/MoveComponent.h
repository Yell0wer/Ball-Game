#pragma once

class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* actor);

	void Update(float delta) override;

private:
	bool mIsGravity;
};

