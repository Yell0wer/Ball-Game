#pragma once

class AIControllerComponent : public ControllerComponent
{
public:
	AIControllerComponent(class Enemy* actor);

	void Update(float delta) override;

private:

};

