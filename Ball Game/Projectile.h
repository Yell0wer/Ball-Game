#pragma once

class Projectile : public DynamicActor
{
public:
	Projectile(class Game* game, b2Vec2 pos, b2Vec2 vel);

	void UpdateActor(float delta) override; // todo encapsulate into dynamicactor

protected:
	float mTimer;
	float mLifespan;
};

