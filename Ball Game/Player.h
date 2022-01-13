#pragma once

class Player : public Actor
{
public:
	Player(class Game* game);

	void ActorInput(const uint8_t* keyState) override;
	void UpdateActor(float delta) override;

private:

};

