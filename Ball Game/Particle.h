#pragma once

class Particle : public Actor
{
public:
	Particle(class Game* game, const std::string& name, int fps, int frames, b2Vec2 pos);

	void UpdateActor(float delta) override;
	void Draw() override;

private:
	class AnimatedSpriteComponent* mAnim;

	float mTimer, mDuration;
};

