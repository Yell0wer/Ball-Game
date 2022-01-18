#pragma once

class Projectile : public DynamicActor
{
public:
	Projectile(class Game* game, class Character* owner, b2Vec2 pos, b2Vec2 vel);

	void UpdateActor(float delta) override; // todo encapsulate into dynamicactor

	void OnCollision(float impact, uintptr_t obj) override;

protected:
	class Character* mOwner;
	float mTimer, mLifespan;
};

