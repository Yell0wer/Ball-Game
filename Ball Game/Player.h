#pragma once

class Player : public DynamicActor
{
public:
	Player(class Game* game);

	void UpdateActor(float delta) override;

	void OnCollision(float impact, uintptr_t obj) override;

private:
    float mHealth;
};
