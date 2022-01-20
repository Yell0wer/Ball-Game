#pragma once

enum AIState
{
	ERest,
	EChase,
	EAttack
};

class AIControllerComponent : public ControllerComponent
{
public:
	AIControllerComponent(class Enemy* actor);

	void Update(float delta) override;

private:
	AIState mState;
	bool mMoving;
};

